#! /usr/bin/env python3

l = []

l += [['11']]
l += [['111']]
l += [['10','11']]
l += [['1111']]
l += [['11','11']]
l += [['010','111']]
l += [['110','011']]
l += [['011','110']]
l += [['100','111']]
l += [['001','111']]

def gene(a, b, i, j):
    h = len(a)
    w = len(a[0])
    
    # print(h, w)
    # for k in range(len(a)):
    #     print(a[k], b[k])
    # print()
    ta = ''.join(a)
    ta = ', '.join(ta)
    tb = ''.join(b)
    tb = ', '.join(tb)
    # print('this->polyominos[%d][%d]'%(i, j), '=', 'polyomino(vector<int>{' + ta + '}, vector<int>{' + tb + '}, %d, %d);'%(h, w))
    print('this->polyominos[%d][%d]'%(i, j), '=', 'polyomino({' + ta + '}, {' + tb + '}, %d, %d);'%(h, w))
    
    

def rot(n, v):
    a = v[:]
    b = []
    h = len(v)
    w = len(v[0])
    for i in range(h):
        t = ''
        for j in range(w):
            t += str(i*w+j)
        b += [t]
    
    for i in range(n):
        ra = []
        rb = []
        h = len(a)
        w = len(a[0])
        for i in range(w):
            ta = ''
            tb = ''
            x = i
            for j in range(h):
                y = h - j - 1
                ta += a[y][x]
                tb += b[y][x]
            ra += [ta]
            rb += [tb]
        a = ra[:]
        b = rb[:]
    return a, b

for i in range(len(l)):
    for j in range(4):
        gene(*rot(j, l[i]), i, j)
    # print('-----------')



