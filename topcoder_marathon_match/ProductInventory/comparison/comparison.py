#! /usr/bin/env python3
import os
import sys


p = os.path.abspath(os.path.dirname(__file__)).replace('\\', '/') + '/'
l = []
for i in os.listdir(p):
    if not 'txt' in i : continue
    with open(p+i, 'r') as f:
        t = [int(x) for x in f.read().split()]
        l += [[t, 0, i]]
if l:
    w = len(l)
    h = len(l[0][0])
    for i in range(h):
        best = max([l[x][0][i] for x in range(w)])
        if best == 0 : continue
        for j in range(w):
            l[j][1] += (l[j][0][i] / best) * 100
    bestscore = 100 * h
    
    l = sorted(l, key=lambda x : x[1])[::-1]
    for i in range(w):
        print(l[i][2][:-4].rjust(24), str(int((l[i][1] / bestscore) * 1000000)).rjust(7))
input()