#! /usr/bin/env python3

import os
import tkinter

def draw():
    for i in a:
        cv.create_line(*i, fill='red', tag = 'cv')


a = []
path = os.path.dirname(__file__).replace('\\', '/')
print(path)
with open(path + '/' + 'warehouse_minimum_steiner_tree.txt', 'r') as f:
    for i in f.readlines():
        if i.startswith('E'):
            a += [[int(x)//2 for x in i[2:].split()]]

# Tkinter
root = tkinter.Tk()
cv = tkinter.Canvas(root, width = 500, height = 500)
cv.pack()
draw()
root.mainloop()








