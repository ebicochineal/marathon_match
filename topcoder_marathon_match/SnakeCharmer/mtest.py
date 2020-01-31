#! /usr/bin/env python3
import os
import sys
import time
import signal
import random
import shutil
import decimal
import threading
from collections import deque
from subprocess import Popen, PIPE

# start_index, test_queue, program_option

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
        self.errtag = 'no'
        self.os = 'win'
        
        self.start = 1
        self.testcnt = 100
        self.ops = []
        if len(sys.argv) > 1:
            self.start = int(sys.argv[1])
            self.testcnt = int(sys.argv[2])
        if len(sys.argv) > 3:
            self.ops = sys.argv[3:]
        
        sp = ';'
        if len(sys.argv) > 1 : self.op = sys.argv[1].replace('\\', '/')
        if 'win' in sys.platform and 'darwin' != sys.platform:
            self.cls = 'cls'
            self.os = 'win'
            # self.getch = self.getch_win
        else:
            self.os = 'unix'
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
                        if mode == '[errtag]':
                            self.errtag = s
                        if mode == '[visoption]':
                            self.ops += [s]
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
        self.fname, self.ext = os.path.splitext(op.source)
        self.ext = self.ext[1:]
        self.cmd = op.crdir + op.source
        exepath = ''
        if self.ext in op.cmdc:
            exepath = cpath + '/' + 'test.exe'
            print('Compile >>>', op.source)
            cmd_compile = ' '.join(op.cmdc[self.ext]).replace('[o]', exepath).replace('[i]', op.crdir + op.source).replace('[n]', self.fname).replace('[d]', './compile/')
            
            os.system(cmd_compile)
            self.cmd = exepath
        if self.ext in op.cmdi:
            if exepath:
                self.cmd = ' '.join(op.cmdi[self.ext]).replace('[o]', exepath).replace('[i]', op.crdir + op.source).replace('[n]', self.fname).replace('[d]', './compile/')
            else:
                self.cmd = ' '.join(op.cmdi[self.ext]).replace('[i]', op.crdir + op.source).replace('[n]', self.fname).replace('[d]', './compile/')
    def get_cmd(self):
        return self.cmd

class TopCoderTesterQueue(threading.Thread):
    def __init__(self, n, cmdpath, op):
        self.n = n
        self.cmdpath = cmdpath
        self.jarpath = op.crdir + 'tester.jar'
        self.result = ()
        self.op = op
        threading.Thread.__init__(self)
    def run(self):
        cmd = []
        cmd += ['java -jar ' + self.jarpath]
        # cmd += ['java -Xmx1024m -jar ' + self.jarpath]
        cmd += ['-exec ' + '\"' + self.cmdpath + '\"']
        cmd += ['-seed ' + str(self.n)]
        # オプションの中に-visとか-novisが含まれていなければ取りあえず-novis
        if not 'vis' in ''.join(self.op.ops) : cmd += ['-novis']
        cmd += self.op.ops
        # cmd += ['-vis']
        # cmd += ['-orig ./example-images/' + str(self.n % 10) + '.jpg']
        # cmd += ['-save ./images/' + str(self.n) + '.jpg']
        # cmd += ['-mark']
        cmd = ' '.join(cmd)
        cmd = cmd.replace('%', str(self.n % 10))
        cmd = cmd.replace('*', str(self.n))
        
        p = Popen(cmd, stdout=PIPE, shell=True)
        try:
            outerr = p.communicate(timeout=self.op.timeout)
            out = outerr[0].decode('utf-8').replace('\r\n', '\n').strip()
            #err = outerr[1].decode('utf-8').replace('\r\n', '\n').strip()
            
            cerr_s, cerr_e = '<cerr>', '</cerr>'
            cerrf_s, cerrf_e = '<cerrfile>', '</cerrfile>'
            sp, spsub = 'Score = ', 'Score: '
            
            if sp not in out and spsub in out : sp = spsub
            if sp in out:
                score = ''
                for i in out.split(sp)[1]:
                    if i.isdigit() or (score == '' and i == '-') or i.lower() == 'e' or i == '.':
                        score += i
                    else:
                        break
                cerr = out.replace(sp + score, '')
                errf = ''
                if self.op.errtag == 'yes':
                    err = ''
                    if cerr_s in cerr:
                        t = []
                        for i in cerr.split(cerr_s)[1:]:
                            if i.strip() : t += [i.split(cerr_e)[0]]
                        err = ':'.join(t)
                    
                    # file
                    if cerrf_s in cerr:
                        t = []
                        for i in cerr.split(cerrf_s)[1:]:
                            if i.strip() : t += [i.split(cerrf_e)[0]]
                        errf = '\n'.join(t)
                else:
                    err = cerr
                
                if errf:
                    di = self.op.crdir + 'outfiles'
                    try_mkdir(di)
                    with open(di + '/' + str(self.n) + '.txt', 'w') as f:
                        f.write(errf)
                    
                self.result = (self.n, decimal.Decimal(score), err, len(errf)>0)
            else:
                self.result = (self.n, decimal.Decimal(-1), '', False)
        except:
            tree_kill(p.pid)
            self.result = (self.n, decimal.Decimal(-1), '', False)

class Test:
    def __init__(self, op):
        sc = SourceCompile(op)
        self.cmdpath = sc.get_cmd()
        print(sc.get_cmd())
        self.op = op
        self.score_reads(self.op.start, self.op.testcnt)
        self.init_testqueue_indexs(self.op.start, self.op.testcnt)
        self.ecnt = 0
        self.gcnt = 0
        self.ycnt = 0
        self.p = 0
        self.pu = 0
        self.pd = 0
        self.testloop(self.op.start)
        self.result_sum_draw(self.op.start, self.op.testcnt)
        self.result_file_write(self.op.start, self.op.testcnt)
    
    def result_sum_draw(self, start_index, testcnt):
        score = 0
        readscore = 0
        for i, j, k, _ in self.results:
            if j >= 0 : score += j
        for i in self.reads : readscore += i
        print('test', start_index, testcnt)
        print('ScoreSum :', score, '    ReadScoreSum :', readscore)
        print('upcnt :', self.gcnt, '    downcnt :', self.ycnt, '    errcnt :', self.ecnt)
        print('all : {:.6f}%'.format(self.p / testcnt - 100), '    up : {:.6f}%'.format(self.pu / testcnt - 100), '    down : {:.6f}%'.format(self.pd / testcnt - 100))
        print('---')
        h = len(self.results)
        r = p = 0
        cnt = 0
        for i in range(h):
            best = -1
            if self.op.compare == 'less':
                best = min(self.results[i][1], self.reads[i])
                if self.results[i][1] >= 0 and self.reads[i] >= 0:
                    if self.results[i][1] > 0 and self.reads[i] > 0:
                        r += (best / self.results[i][1]) * 100
                        p += (best / self.reads[i]) * 100
                    elif self.results[i][1] == 0 and self.reads[i] > 0:
                        r += 100
                    elif self.results[i][1] > 0 and self.reads[i] == 0:
                        p += 100
                    else:
                        if self.results[i][1] == self.reads[i]:
                            r += 100
                            p += 100
                elif self.results[i][1] < 0 and self.reads[i] >= 0:
                    p += 100
                elif self.results[i][1] >= 0 and self.reads[i] < 0:
                    r += 100
            else:# greater
                best = max(self.results[i][1], self.reads[i])
                if self.results[i][1] >= 0 and self.reads[i] >= 0:
                    if best > 0:
                        r += (self.results[i][1] / best) * 100
                        p += (self.reads[i] / best) * 100
                    else:
                        if self.results[i][1] == self.reads[i]:
                            r += 100
                            p += 100
                        elif self.results[i][1] > self.reads[i]:
                            r += 100
                        else:
                            p += 100
                elif self.results[i][1] < 0 and self.reads[i] >= 0:
                    p += 100
                elif self.results[i][1] >= 0 and self.reads[i] < 0:
                    r += 100
                
            cnt += 1
        bestscore = 100 * h
        print('this program : ', str(int((r / bestscore) * 1000000)).rjust(7))
        print('read score   : ', str(int((p / bestscore) * 1000000)).rjust(7))
        
    def result_file_write(self, start_index, testcnt):
        with open(self.op.crdir + 'result' + str(start_index) + '_' + str(testcnt) + '.txt', 'w') as f:
            for i, j, k, _ in self.results:
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
        try_mkdir(self.op.crdir + 'scores')
        self.reads = [decimal.Decimal(-1)] * testcnt
        rp = self.op.crdir + '/scores/' + 'result' + str(start_index) + '_' + str(testcnt) + '.txt'
        if os.path.exists(rp) :
            with open(rp, 'r') as f:
                self.reads = [decimal.Decimal(x) for x in f.readlines()]
    
    def result_draw_line(self, result, start_index, draw_index):
        p = draw_index - start_index
        testindex = result[0]
        readscore = self.reads[p]
        progscore = result[1]
        cerr = result[2]
        isoutfile = result[3]
        # color
        if 'win' in sys.platform and 'darwin' != sys.platform : os.system('color')
        green = lambda x : '\033[42;30m' + x + '\033[0m'
        yellow = lambda x : '\033[43;30m' + x + '\033[0m'
        red = lambda x : '\033[41;30m' + x + '\033[0m'
        purple = lambda x : '\033[45;30m' + x + '\033[0m'
        
        # result (index, score, cerr)
        index = '{:4d}'.format(testindex)
        a = '{:16.4f}'.format(progscore)
        b = '{:16.4f}'.format(progscore - readscore)
        e = '-{:16.4f}'.format(readscore)
        t = progscore - readscore
        if progscore < 0:
            b = red(e)
            self.ecnt += 1
        else:
            if self.op.compare == 'less':
                if readscore < 0:
                    if progscore > -1:
                        b = green(a)
                        self.gcnt += 1
                else:
                    if t < 0:
                        b = green(b)
                        self.gcnt += 1
                    if t > 0:
                        b = yellow(b)
                        self.ycnt += 1
            else:
                if readscore < 0:
                    if progscore > -1:
                        b = green(a)
                        self.gcnt += 1
                else:
                    if t > 0:
                        b = green(b)
                        self.gcnt += 1
                    if t < 0:
                        b = yellow(b)
                        self.ycnt += 1
        
        s = ':'.join(cerr.split('\n')) if cerr else ''
        
        if readscore > -1:
            if isoutfile:
                print(purple('F'), index, ': Score', a, b, ':{:8.4f}%'.format((progscore / readscore)*100),':', s)
            else:
                print(index, ': Score', a, b, ':{:8.4f}%'.format((progscore / readscore)*100),':', s)
            self.p += (progscore / readscore)*100
            self.pu += (100 if (progscore / readscore)*100 < 100 else (progscore / readscore)*100)
            self.pd += (100 if (progscore / readscore)*100 > 100 else (progscore / readscore)*100)
        else:
            if isoutfile:
                print(purple('F'), index, ': Score', a, b, ':', s)
            else:
                print(index, ': Score', a, b, ':', s)
            self.p += 100
            self.pu += 100
            self.pd += 100
        
        if 'win' in sys.platform and 'darwin' != sys.platform : os.system('color')

def try_mkdir(dir):
    try:
        if not os.path.exists(dir) : os.mkdir(dir)
    except:
        pass
def tree_kill(pid):
    if 'win' in sys.platform and 'darwin' != sys.platform:
        Popen('taskkill /PID %s /T /F'%str(pid), stdout=PIPE, stderr=PIPE)
    else:
        p = Popen('ps --ppid ' + str(pid) + ' --no-heading', stdout=PIPE, stderr=PIPE, shell=True)
        outerr = p.communicate()
        out = outerr[0].decode('utf-8').replace('\r\n', '\n').strip()
        for i in out.split('\n'):
            try:
                cpid = i.split()[0]
                os.kill(int(cpid), signal.SIGTERM)
            except:
                pass
        os.kill(pid, signal.SIGTERM)

if __name__ == '__main__':
    def handler(signal, frame) : tree_kill(os.getpid())
    if 'win' in sys.platform and 'darwin' != sys.platform:
        signal.signal(signal.SIGBREAK, handler)
    signal.signal(signal.SIGINT, handler)
    
    op = Option()
    Test(op)

