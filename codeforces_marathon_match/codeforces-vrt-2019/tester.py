#! /usr/bin/env python3
import os
import sys

def err(s):
    print('<cerr>' + s + '</cerr>', file=sys.stderr)

def tester(fin, fout):
    n = 0
    hx = 0
    hy = 0
    tworks = []
    with open(fin) as f:
        a, *b = f.read().split('\n')
        n = int(a)
        for i in range(n):
            x, y, d, p, l, h = map(int, b[i].split())
            if i < 1:
                hx = x
                hy = y
            tworks += [(x, y, d, p, l, h)]
    works = [(None, 0) for x in range(n)]
    
    wcredit = 0
    start = -1
    px = 0
    py = 0
    time = 0
    with open(fout) as f:
        for i in f.readlines():
            c, *s = i.split()
            v = list(map(int, s))
            if c == 'start':
                start = v[0]
                px = hx
                py = hy
                time = start
            if c == 'arrive':
                x, y, d, p, l, h = tworks[v[1]-1]
                if v[0] - time >= abs(x-px) + abs(y-py):
                    time = v[0]
                    px = x
                    py = y
                else:
                    err('arrive')
                    return -1
            if c == 'work':
                x, y, d, p, l, h = tworks[v[2]-1]
                if px == x and py == y and v[0] >= time and v[0] >= l and v[1] <= h and v[1] - v[0] == d:
                    wp, cnt = works[v[2]-1]
                    time = v[1]
                    if wp == None:
                        works[v[2]-1] = (v[0], 1)
                    else:
                        if wp != v[0]:
                            err('work1')
                            return -1
                        works[v[2]-1] = (wp, cnt + 1)
                else:
                    err('work2')
                    return -1
            if c == 'end':
                if px == hx and py == hy:
                    wcredit += time - start + 240
                else:
                    err('end')
                    return -1
    credit = 0
    for i in range(n):
        wp, cnt = works[i]
        if wp != None:
            x, y, d, p, l, h = tworks[i]
            if cnt == p:
                credit += d * p * (p + 5)
            else:
                err(str(cnt) + ' ' + str(p))
                return -1
    return credit - wcredit

if __name__ == '__main__':
    print('Score =', tester(sys.argv[1], sys.argv[2]))
    


