#! /usr/bin/env python3
import os
import tkinter

class pix:
    def __init__(self, cellsize, maxsize = 32):
        self.size = 32
        self.cvsize = (self.size) * cellsize
def background():
    s, e = 2, m + p.cvsize
    for x in range(p.size):
        cv.create_line(m + size * x, s, m + size * x, e, tag = 'bg')
    for y in range(p.size):
        cv.create_line(s, m + size * y, e, m + size * y, tag = 'bg')
    cv.create_rectangle(s, s, e, e, tag = 'bg')
def draw():
    cv.delete('cells')
    dy = [-2, -1, 1, 2, 2, 1, -1, -2]
    dx = [1, 2, 2, 1, -1, -2, -2, -1]
    cnt2= 0
    for x, y in po:
        px = x * size+m
        py = y * size+m
        cv.create_text(px + size//2, py + size//2, text = 'P', tag = 'cells')
    for x, y in l:
        cnt = 0
        for z in range(8):
            p = (x+dx[z], y+dy[z])
            if p in l or p in po:
                cnt += 1
        px = x * size+m
        py = y * size+m
        if cnt == 2:
            cv.create_rectangle(px, py, px + size, py + size, fill = '#AAAAFF',tag = 'cells')
            cv.create_text(px + size//2, py + size//2, text = cnt, tag = 'cells')
            cnt2 += 1
        elif cnt > 2:
            cv.create_rectangle(px, py, px + size, py + size, fill = '#FF0000',tag = 'cells')
            cv.create_text(px + size//2, py + size//2, text = cnt, tag = 'cells')
        else:
            cv.create_text(px + size//2, py + size//2, text = cnt, tag = 'cells')
    print(cnt2)
    
def leftdown(e):
    p = (e.x//size, e.y//size)
    if p in l : l.remove(p)
    if p in po : po.remove(p)
    l.add(p)
    draw()
def rightdown(e):
    p = (e.x//size, e.y//size)
    if p in l : l.remove(p)
    if p in po : po.remove(p)
    draw()
def middown(e):
    p = (e.x//size, e.y//size)
    if p in l : l.remove(p)
    if p in po : po.remove(p)
    po.add(p)
    draw()

l = set()
po = set()
size = 16
m = 2    # margin
root = tkinter.Tk()

p = pix(16)
cv = tkinter.Canvas(root, width = p.cvsize+1, height = p.cvsize+1)
cv.pack()
background()
root.bind('<Button-1>', leftdown)
root.bind('<Button-2>', middown)
root.bind('<Button-3>', rightdown)
root.mainloop()


'''
 P
 P
K K
K K
K K
K K
 P
 P


2      2
 222222
 222222
2      2

222
2 2
222

 KKK
K   K
K P K
K   K
 KKK

 2
  
2 2
2 2
2 2
2 2
  
 2


2  2222222222222  2
  222222222222222
 22             22

   2222222222222  
  222222222222222
  2             2
 22             22
                  
  222222222222222
  222222222222222
                  
 22             22
  2             2
  222222222222222
   2222222222222  
   
  22
 P 22
2  P22
22P  2
 22 P
  22



2222
222
22P
2
'''