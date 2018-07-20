#! /usr/bin/env python3
import os
import sys
import time
import random
import shutil
import decimal
import threading
from collections import deque
from subprocess import Popen, PIPE

class Option:
    def __init__(self):
        p = os.path.abspath(os.path.dirname(__file__)).replace('\\', '/') + '/'
        self.crdir = '' if p == '/' else p
        self.cmdc = {}
        self.cmdi = {}
        self.op = ''
        self.cls = ''
        self.source = ''
        self.getch = None
        self.maxthread = 1
        self.compare = 'greater'
        sp = ';'
        if len(sys.argv) > 1 : self.op = sys.argv[1].replace('\\', '/')
        if 'win' in sys.platform and 'darwin' != sys.platform:
            self.cls = 'cls'
            # self.getch = self.getch_win
        else:
            self.cls = 'clear'
            # self.getch = self.getch_unix
            sp = ':'
        with open(self.crdir + 'setting.ini', encoding='UTF-8') as f:
            mode = ''
            for i in f.readlines():
                s = i.strip()
                if len(i) > 1 and i[:2] != '//':
                    if s[0] == '[':
                        mode = s
                    else:
                        s = s.replace('\\', '/')
                        if mode == '[source]':
                            self.source = s
                        if mode == '[path]':
                            os.environ['PATH'] = os.environ['PATH'] + sp + s
                        if mode == '[browser]':
                            self.browser = s
                        if mode == '[tle]':
                            self.timeout = int(s)
                        if mode == '[compile]':
                            lang, cmd = map(lambda x : x.strip(), s.split(':', 1))
                            self.cmdc[lang] = cmd.split()
                        if mode == '[interpreter]':
                            lang, cmd = map(lambda x : x.strip(), s.split(':', 1))
                            self.cmdi[lang] = cmd.split()
                        if mode == '[maxthread]':
                            self.maxthread = int(s)
                        if mode == '[compare]':
                            self.compare = s
    # def getch_unix(self):
    #     import sys, tty, termios
    #     fd = sys.stdin.fileno()
    #     old = termios.tcgetattr(fd)
    #     try:
    #         tty.setraw(sys.stdin.fileno())
    #         ch = sys.stdin.read(1)
    #     finally:
    #         termios.tcsetattr(fd, termios.TCSADRAIN, old)
    #     return ch
    # def getch_win(self):
    #     import msvcrt
    #     try:
    #         return msvcrt.getch().decode('utf8')
    #     except:
    #         return ''

class SourceCompile:
    def __init__(self, op):
        cpath = op.crdir + 'compile'
        try_mkdir(cpath)
        _, self.ext = os.path.splitext(op.source)
        self.ext = self.ext[1:]
        self.path = op.crdir + op.source
        if self.ext in op.cmdc:
            exepath = cpath + '/' + 'test.exe'
            print('Compile >>>', op.source)
            cmd = ' '.join(op.cmdc[self.ext]).replace('[o]', exepath).replace('[i]', op.crdir + op.source)
            os.system(cmd)
            self.path = exepath
        if self.ext in op.cmdi:
            self.path = ' '.join(op.cmdi[self.ext]).replace('[i]', op.crdir + op.source)
    def get_cmd(self):
        return self.path

class TopCoderTesterQueue(threading.Thread):
    def __init__(self, n, cmdpath, op):
        self.n = n
        self.cmdpath = cmdpath
        self.jarpath = op.crdir + 'tester.jar'
        self.result = ()
        self.op = op
        
        threading.Thread.__init__(self)
    def run(self):
        cmd = 'java -jar ' + self.jarpath + ' -exec ' + self.cmdpath + ' -seed ' + str(self.n) + ' -novis'
        p = Popen(cmd.split(), stdout=PIPE, stdin=PIPE, stderr=PIPE)
        outerr = p.communicate(timeout=self.op.timeout)
        out = outerr[0].decode('utf-8').replace('\r\n', '\n').strip()
        err = outerr[1].decode('utf-8').replace('\r\n', '\n').strip()
        # print('----')
        # print('out', out)
        # print('err', err)
        
        sp = 'Score = '
        if sp in out:
            self.result = (self.n, decimal.Decimal(out.split(sp)[1]), out.split(sp)[0])
        else:
            self.result = (self.n, decimal.Decimal(0), '')

class Test:
    def __init__(self, start_index, testcnt, op):
        sc = SourceCompile(op)
        self.cmdpath = sc.get_cmd()
        print(sc.get_cmd())
        self.op = op
        self.score_reads(start_index, testcnt)
        self.init_testqueue_indexs(start_index, testcnt)
        self.gcnt = 0
        self.ycnt = 0
        self.testloop(start_index)
        self.result_sum_draw()
        self.result_file_write(start_index, testcnt)
    
    def result_sum_draw(self):
        score = 0
        readscore = 0
        for i, j, k in self.results : score += j
        for i in self.reads : readscore += i
        print('Sum :', score, '    PrevSum :', readscore)
        print('up :', self.gcnt, '    down :', self.ycnt)
    
    def result_file_write(self, start_index, testcnt):
        with open('result' + str(start_index) + '_' + str(testcnt) + '.txt', 'w') as f:
            for i, j, k in self.results:
                f.write(str(j) + '\n')
    
    def testloop(self, start_index):
        self.results = []
        q = []
        draw_index = start_index
        self.add_next_testqueue(q)# 最初のキューを入れる
        while len(q) > 0:# キューがあるなら
            time.sleep(0.01)
            test_q = []
            end_q = []
            for i in q:# テスト中のキュー、テスト終了キューを分ける
                if i.is_alive():
                    test_q += [i]
                else:
                    end_q += [i]
            q = test_q
            if len(q) < op.maxthread:# スレッドが余っているなら次のキュー追加。４スレなら最初３ループしないと埋まらない
                self.add_next_testqueue(q)
            
            for i in end_q : self.results += [i.result]# テスト終了キューの結果を追加
            self.results.sort()
            
            for i in self.results:# draw_indexの位置の結果を表示、draw_indexの結果がまだなら次の結果は表示しない
                if i[0] == draw_index:
                    self.result_draw_line(i, start_index, draw_index)
                    draw_index += 1
    
    def add_next_testqueue(self, q):
        if len(self.testqueue_indexs) > 0:
            i = self.testqueue_indexs.popleft()
            t = TopCoderTesterQueue(i, self.cmdpath, self.op)
            t.start()
            q += [t]
    
    def init_testqueue_indexs(self, start_index, testcnt):
        self.testqueue_indexs = deque()
        for i in range(start_index, start_index + testcnt) : self.testqueue_indexs.append(i)
    
    def score_reads(self, start_index, testcnt):
        try_mkdir(op.crdir + 'best')
        self.reads = [decimal.Decimal(0)] * testcnt
        rp = op.crdir + '/best/' + 'result' + str(start_index) + '_' + str(testcnt) + '.txt'
        if os.path.exists(rp) :
            with open(rp, 'r') as f:
                self.reads = [decimal.Decimal(x) for x in f.readlines()]
    
    def result_draw_line(self, result, start_index, draw_index):
        p = draw_index - start_index
        # color
        if 'win' in sys.platform and 'darwin' != sys.platform : os.system('color')
        green = lambda x : '\033[42;30m' + x + '\033[0m'
        yellow = lambda x : '\033[43;30m' + x + '\033[0m'
        # result (index, score, cerr)
        index = '{0:4d}'.format(result[0])
        a = '{:14.4f}'.format(result[1])
        b = '{:14.4f}'.format(result[1] - self.reads[p])
        t = result[1] - self.reads[p]
        if self.op.compare == 'less':
            if t < 0:
                b = green(b)
                self.gcnt += 1
            if t > 0:
                b = yellow(b)
                self.ycnt += 1
        else:
            if t > 0:
                b = green(b)
                self.gcnt += 1
            if t < 0:
                b = yellow(b)
                self.ycnt += 1
        s = ':'.join(result[2].split('\n')) if result[2] else ''
        
        print(index, ': Score', a, b, ':', s)
        
        if 'win' in sys.platform and 'darwin' != sys.platform : os.system('color')

def try_mkdir(dir):
    try:
        if not os.path.exists(dir) : os.mkdir(dir)
    except:
        pass

if __name__ == '__main__':
    op = Option()
    if len(sys.argv) > 1:# start_index, test_queue, program_option
        Test(int(sys.argv[1]), int(sys.argv[2]), op)
    else:
        Test(1, 100, op)

