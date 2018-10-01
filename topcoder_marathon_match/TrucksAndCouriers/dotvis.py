#! /usr/bin/env python3

import os
import tkinter

b = 0
def draw():
    global b
    cv.delete('cv')
    for i in c:
        x, y = i[2:]
        cv.create_oval(x-1, y-1, x+1, y+1, tag = 'cv')  
    b = (b+1)%3



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
root.mainloop()








