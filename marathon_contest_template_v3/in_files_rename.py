#! /usr/bin/env python3
import os
import sys

p = os.path.abspath(os.path.dirname(__file__)).replace('\\', '/') + '/'
cr = '' if p == '/' else p

for i in os.listdir('./in'):
    if not i.endswith('.txt') : continue
    t = ''.join(x for x in i if '0'<=x<='9')
    if t == '' : continue
    t = str(int(t))
    t += '.txt'
    if cr + 'in/' + i == cr + 'in/' + t : continue
    print(cr + 'in/' + i, '>', cr + 'in/' + t)
    os.rename(cr + 'in/' + i, cr + 'in/' + t)
    
    

