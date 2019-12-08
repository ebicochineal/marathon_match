#! /usr/bin/env python3
import os
import random
import shutil
import decimal
from subprocess import Popen, PIPE

class Test:
    def __init__(self, name):
        self.cd = os.path.abspath(os.path.dirname(__file__)).replace('\\', '/')
        self.fin = self.cd + '/in' + '/'
        self.fout = self.cd + '/out' + '/'
        self.name = name
        self.testexe = self.cd + '/' + name + '.exe'
        self.copy = self.cd + '/' + name + '2.exe'
        self.set_java_env()
        self.check_dir(self.fin)
        self.check_dir(self.fout)
        self.execopy()
        sum_score = 0
        for i in range(10):
            self.score(i)
        
    def set_java_env(self):
        jenv = 'C:/Program Files (x86)/Java/jdk1.8.0_112/bin'
        if not jenv in os.environ['path'] : os.environ['path'] += ';' + jenv
    def sourcecopy(self, score):
        if score <= 0 : return
        t1 = self.cd + '/' + self.name + '.cpp'
        name = self.cd + '/b/' + self.name + str(score.quantize(decimal.Decimal('.0001'))).replace('.', '_')
        while os.path.exists(name + '.cpp') : name += 'a'
        shutil.copyfile(t1, name + '.cpp')
    def execopy(self):
        t1 = self.testexe
        t2 = self.copy
        shutil.copyfile(t1, t2)
    def score(self, n):
        fin = self.fin + str(n) + '.txt'
        fout = self.fout + str(n) + '.txt'
        print(self.copy + ' < ' + fin + ' > ' + fout)
        os.system(self.copy + ' < ' + fin + ' > ' + fout)
        
        cmd = 'java Judge ' + fin + ' ' + fout
        
        os.system(cmd)
        
        
        
        # cmd = 'java Tester -seed ' str(n) + ' -command ' + '"' + self.copy + '"'
        # print(cmd)
        # os.system(cmd)
        
        # p = Popen(cmd, stdout=PIPE, stdin=PIPE, stderr=PIPE)
        # outerr = p.communicate(timeout=1000)
        # out = outerr[0].decode('utf-8').replace('\r\n', '\n').strip()
        # err = outerr[1].decode('utf-8').replace('\r\n', '\n').strip()
        
        # sp = 'Score = '
        
        # if sp in out:
        #     print('---output---\n' + out.split(sp)[0])
        #     print(str(n) + ' score:' + str(decimal.Decimal(out.split(sp)[1])))
        #     # print(err)
        #     return decimal.Decimal(out.split(sp)[1])
        # else:
        #     print(str(n) + ' score:' + str(decimal.Decimal(0)))
        #     print(out)
        #     return decimal.Decimal(0)
    def check_dir(self, dir):
        if not os.path.exists(dir) : os.mkdir(dir)

if __name__ == '__main__':
    Test('a')
