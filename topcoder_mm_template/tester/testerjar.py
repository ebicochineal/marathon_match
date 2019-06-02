#! /usr/bin/env python3
import os
import sys

# testerjar.py dir path
cd = os.path.abspath(os.path.dirname(__file__)).replace('\\', '/') + '/'

# javapathを通す
javapath = ''
with open(cd + 'javapath.ini', 'r') as f:
    for i in f.readlines():
        if not i.startswith('//') : javapath = i
sp = ':;'['win' in sys.platform and 'darwin' != sys.platform]
if not javapath in os.environ['PATH'] : os.environ['PATH'] += sp + javapath



# javaファイル
target = ''
for i in os.listdir(cd):
    if 'Vis.java' in i:
        print(cd + i)
        target = cd + i

# classname main
classname = os.path.basename(target).split('.')[0]

# class file dir
dir = cd + 'build'

# manifest path
manifest = dir + 'manifest'

# tester.jar path
tester = cd + 'tester.jar'

# mkdir
if not os.path.exists(dir) : os.mkdir(dir)

# compile
cmd = 'javac -d ' + dir + ' ' + target
os.system(cmd)

# manifest
with open(manifest, 'w') as f : f.write('Main-Class: ' + classname + '\n')

# jar package
cmd = 'jar cvfm ' + tester + ' ' + manifest + ' -C ' + dir + ' .'
os.system(cmd)


