#! /usr/bin/env python3

import os
import tkinter

b = 0
def draw():
    global b
    cv.delete('cv')
    if b == 0 or b == 1:
        for i in c:
            cv.create_line(*i, fill='red', tag = 'cv')
    if b == 0 or b == 2:
        for i in t:
            cv.create_line(*i, fill='blue', tag = 'cv', arrow=tkinter.LAST)
    b = (b+1)%3
def leftdown(e):
    draw()


t = []
c = []
path = os.path.dirname(__file__).replace('\\', '/')
print(path)
with open(path + '/' + 'visout.txt', 'r') as f:
    for i in f.readlines():
        if i.startswith('C,'):
            c += [[int(x)//2 for x in i[2:].split(',')[:4]]]
        if i.startswith('T,'):
            t += [[int(x)//2 for x in i[2:].split(',')[:4]]]

# Tkinter
root = tkinter.Tk()
cv = tkinter.Canvas(root, width = 500, height = 500)
cv.pack()
draw()
root.bind('<Button-1>', leftdown)
root.mainloop()








