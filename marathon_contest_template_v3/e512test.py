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

class Option:
    def __init__(self):
        p = os.path.abspath(os.path.dirname(__file__)).replace('\\', '/') + '/'
        self.crdir = '' if p == '/' else p
        self.cmdc = {}
        self.cmdi = {}
        self.cls = ''
        self.source = ''
        self.getch = None
        self.maxthread = 1
        self.compare = 'greater'
        self.errtag = 'no'
        self.os = 'win'
        
        self.errscore = -1
        
        self.start = 1
        self.testcnt = 100
        self.ops = []
        
        self.testercmd = []
        self.gencmd = []
        self.score_keyword = []
        self.fullpath = []
        
        if len(sys.argv) > 1:
            self.start = int(sys.argv[1])
            self.testcnt = int(sys.argv[2])
        if len(sys.argv) > 3:
            self.ops = sys.argv[3:]
        
        yvis = '-vis' in self.ops
        if yvis : self.ops = [x for x in self.ops if x != '-vis']
        
        
        sp = ';'
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
                        if mode == '[testercmd]':
                            if yvis : s = s.replace(' -novis', '')
                            self.testercmd += [s]
                        if mode == '[gencmd]':
                            self.gencmd += [s]
                        if mode == '[score_keyword]':
                            self.score_keyword += [s]
                        if mode == '[fullpath]':
                            self.fullpath += [s]
                        if mode == '[errscore]':
                            self.errscore = int(s)
        tmp = []
        for i in self.ops:
            if '-maxthread' in i:
                self.maxthread = int(i[10:])
            elif '-mt' in i:
                self.maxthread = int(i[3:])
            elif '-sample' in i:
                self.source = 'sample.cpp'
            else:
                tmp += [i]
        self.ops = tmp
        


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
        self.result = ()
        self.op = op
        self.fin = self.op.crdir + 'in' + '/'
        self.fout = self.op.crdir + 'out' + '/'
        threading.Thread.__init__(self)
    
    def dstr(self, s) : return '\"' + s + '\"'
    def cmd_replace(self, s):
        fin = self.fin + str(self.n) + '.txt'
        fout = self.fout + str(self.n) + '.txt'
        d = {}
        
        for i in self.op.fullpath:
            d[i] = self.op.crdir + i
        for i in ['in.txt', 'in', 'input.txt']:
            d[i] = fin
        for i in ['out.txt', 'out', 'output.txt']:
            d[i] = fout
        for i in ['<seed>']:
            d[i] = str(self.n)
        for i in ['cmd', '<command>']:
            d[i] = self.cmdpath
            d[self.dstr(i)] = self.dstr(self.cmdpath)
        
        fop = True
        l = []
        for i in s.split():
            if i == 'option':
                l += self.op.ops
                fop = False
            else:
                if i in d : i = d[i]
                l += [i]
        if fop : l += self.op.ops
        return ' '.join(l)
    
    def get_result(self):
        result = ''
        for cmd in self.op.testercmd:
            cmd = self.cmd_replace(cmd)
            # print(cmd)
            p = Popen(cmd, stdout=PIPE, stderr=PIPE, shell=True)
            outerr = p.communicate()
            out = outerr[0].decode('utf-8').replace('\r\n', '\n').strip()
            err = outerr[1].decode('shift-jis').replace('\r\n', '\n').strip()
            result += out + err
        return result
        
    
    def run(self):
        try_mkdir(self.fout)
        try:
            out = self.get_result()
            
            # print(out)
            cerr_s, cerr_e = '<cerr>', '</cerr>'
            cerrf_s, cerrf_e = '<cerrfile>', '</cerrfile>'
            
            spstr = self.op.score_keyword
            
            # print(spstr)
            
            sp = ':'
            for i in spstr:
                if i in out : sp = i
            
            timecheck = ''
            
            if sp in out:
                score = ''
                for i in out.split(sp)[1].strip():
                    # if i.isdigit() or (score == '' and i == '-') or i.lower() == 'e' or i == '.':
                    if i.isdigit() or i == '-' or i.lower() == 'e' or i == '.':
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
                            if i.strip():
                                m = i.split(cerr_e)[0]
                                if '[time]' in m:
                                    m = m.replace('[time]', '')
                                    if int(m) >= 10000:
                                        timecheck = 'timeout ' + m
                                    else:
                                        t += ['time ' + m]
                                else:
                                    t += [m]
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
                    di = self.op.crdir + 'debug'
                    try_mkdir(di)
                    with open(di + '/' + str(self.n) + '.txt', 'w') as f:
                        f.write(errf)
                else:
                    di = self.op.crdir + 'debug'
                    try_mkdir(di)
                    with open(di + '/' + str(self.n) + '.txt', 'w') as f:
                        f.write(errf)
                
                if timecheck != '':
                    self.result = (self.n, decimal.Decimal(-1), timecheck, False)
                else:
                    self.result = (self.n, decimal.Decimal(score), err, len(errf)>0)
            else:
                self.result = (self.n, decimal.Decimal(-1), '', False)
        except:
            tree_kill(p.pid)
            self.result = (self.n, decimal.Decimal(-1), '', False)
    
class Test:
    def __init__(self, start_index, testcnt, op):
        sc = SourceCompile(op)
        self.cmdpath = sc.get_cmd()
        print(sc.get_cmd())
        self.op = op
        self.score_reads(start_index, testcnt)
        self.init_testqueue_indexs(start_index, testcnt)
        self.ecnt = 0
        self.gcnt = 0
        self.ycnt = 0
        self.p = 0
        self.pu = 0
        self.pd = 0
        self.testloop(start_index)
        self.result_sum_draw(start_index, testcnt)
        self.result_file_write(start_index, testcnt)
    
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
        print('50case score : {:,}'.format(int((score / len(self.results)) * 50)))
        print('100case score : {:,}'.format(int((score / len(self.results)) * 100)))
        print('average score',(score / len(self.results)))
        
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
        self.reads = [decimal.Decimal(0)] * testcnt
        rp = self.op.crdir + '/scores/' + 'result' + str(start_index) + '_' + str(testcnt) + '.txt'
        if os.path.exists(rp) :
            with open(rp, 'r') as f:
                self.reads = [decimal.Decimal(x) for x in f.readlines()]
    
    def result_draw_line(self, result, start_index, draw_index):
        p = draw_index - start_index
        # color
        if 'win' in sys.platform and 'darwin' != sys.platform : os.system('color')
        green = lambda x : '\033[42;30m' + x + '\033[0m'
        yellow = lambda x : '\033[43;30m' + x + '\033[0m'
        red = lambda x : '\033[41;30m' + x + '\033[0m'
        purple = lambda x : '\033[45;30m' + x + '\033[0m'
        
        # result (index, score, cerr)
        index = '{:4d}'.format(result[0])
        a = '{:16.4f}'.format(result[1])
        b = '{:16.4f}'.format(result[1] - self.reads[p])
        e = '-{:16.4f}'.format(self.reads[p])
        t = result[1] - self.reads[p]
        if result[1] <= self.op.errscore:
            b = red(e)
            self.ecnt += 1
        else:
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
        
        if self.reads[p]:
            if result[3]:
                print(purple('F'), index, ': Score', a, b, ':{:8.4f}%'.format((result[1] / self.reads[p])*100),':', s)
            else:
                print(index, ': Score', a, b, ':{:8.4f}%'.format((result[1] / self.reads[p])*100),':', s)
            self.p += (result[1] / self.reads[p])*100
            self.pu += (100 if (result[1] / self.reads[p])*100 < 100 else (result[1] / self.reads[p])*100)
            self.pd += (100 if (result[1] / self.reads[p])*100 > 100 else (result[1] / self.reads[p])*100)
        else:
            if result[3]:
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
def cmd_replace(op, s, n, fin):
        nfin = fin + str(n) + '.txt'
        d = {}
        
        for i in ['in.txt', 'in', 'input.txt']:
            d[i] = nfin
        for i in op.fullpath:
            d[i] = op.crdir + i
        for i in ['seeds.txt']:
            d[i] = op.crdir + 'in/' + 'seeds.txt'
        for i in ['<seed>', 'seed']:
            d[i] = str(n)
        l = []
        for i in s.split():
            if i in d:
                i = d[i]
            elif i.endswith('.txt'):
                i = op.crdir + i
            l += [i]
        return ' '.join(l)
    
def input_file_generate(s, cnt, op):
    fin = op.crdir + 'in/'
    try_mkdir(fin)
    try:
        for i in range(s, s+cnt):
            filepath = fin + str(i) + '.txt'
            tmpcrdir = os.getcwd()
            os.chdir(op.crdir)
            if os.path.exists(filepath) : continue
            fin = op.crdir + 'in' + '/'
            
            seed = i
            for cmd in op.gencmd:
                if cmd == '<rename>':
                    os.rename(fin + '0000.txt', filepath)
                elif cmd == '<create seeds.txt>':
                    with open(fin + 'seeds.txt', 'w') as f : f.write(str(i))
                else:
                    cmd = cmd_replace(op, cmd, seed, fin)
                    # print(cmd)
                    os.system(cmd)
            os.chdir(tmpcrdir)
    except:
        print('generate error')

if __name__ == '__main__':
    def handler(signal, frame) : tree_kill(os.getpid())
    if 'win' in sys.platform and 'darwin' != sys.platform:
        signal.signal(signal.SIGBREAK, handler)
    signal.signal(signal.SIGINT, handler)
    
    op = Option()
    if len(sys.argv) > 1:# start_index, test_queue, program_option
        input_file_generate(int(sys.argv[1]), int(sys.argv[2]), op)
        Test(int(sys.argv[1]), int(sys.argv[2]), op)
    else:
        input_file_generate(1, 100, op)
        Test(1, 100, op)
        


