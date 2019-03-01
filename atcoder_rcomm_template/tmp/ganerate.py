#! /usr/bin/env python3
import os
import random
import shutil
import decimal
from subprocess import Popen, PIPE

class Test:
    def __init__(self):
        self.cd = os.path.abspath(os.path.dirname(__file__)).replace('\\', '/')
        self.fin = self.cd + '/in' + '/'
        self.set_java_env()
        self.check_dir(self.fin)
        for i in range(20):
            self.generate(i)
    def set_java_env(self):
        jenv = 'C:/Program Files (x86)/Java/jdk1.8.0_112/bin'
        if not jenv in os.environ['path'] : os.environ['path'] += ';' + jenv
    def generate(self, n):
        cmd = 'java Generator -seed' + str(n) + ' > ' + self.fin + str(n) + '.txt'
        print(cmd)
        os.system(cmd)
    def check_dir(self, dir):
        if not os.path.exists(dir) : os.mkdir(dir)

if __name__ == '__main__':
    Test()

