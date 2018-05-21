#! /usr/bin/env python3
import os
import sys

# javapathを通す 通ってるならコメントアウト
javapath = 'C:/Program Files (x86)/Java/jdk1.8.0_112/bin'
sp = ':;'['win' in sys.platform and 'darwin' != sys.platform]
if not javapath in os.environ['PATH'] : os.environ['PATH'] += sp + javapath

# testerjar.py dir path
cd = os.path.abspath(os.path.dirname(__file__)).replace('\\', '/')

# ***Vis.java
target = sys.argv[1]

# classname main
classname = os.path.basename(target).split('.')[0]

# class file dir
dir = cd + '/build'

# manifest path
manifest = dir + '/manifest'

# tester.jar path
tester = cd + '/tester.jar'

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


