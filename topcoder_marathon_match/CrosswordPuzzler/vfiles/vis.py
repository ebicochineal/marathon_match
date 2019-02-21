#! /usr/bin/env python3
import os
import time
import tkinter

class visfile:
    def __init__(self, filepath, cv):
        self.cv = cv
        self.cv.delete('word')
        print(filepath)
        with open(filepath, 'r') as f:
            t = f.readlines()
            self.w, self.h = map(int, t[0].split())
            self.n = int(t[1])
            self.words = []
            self.lines = []
            self.wpds = []
            for i in range(self.n):
                self.words += [t[2+i].strip()]
                # print(t[2+i].strip())
            for i in range(self.h):
                self.lines += [t[2+self.n+i].strip()]
            
            for i in range(int(t[2+self.n+self.h])):
                self.wpds += [t[2+self.n+self.h+1+i].strip().split()]
            
            
            
        self.cv.config(width=max(self.w*12+2, 250)-2, height=max(self.h*12+2, 250)-2)
        cv.create_rectangle(2, 2, max(self.w*12+2, 250)-1, max(self.h*12+2, 250)-1, outline='black', tag = 'word')
        # for y in range(self.h):
        #     for x in range(self.w):
        #         cv.create_text(6+x*12, 6+y*12, text = self.lines[y][x], tag = 'word')
        
        for w, px, py, d in self.wpds:
            px = int(px)
            py = int(py)
            f = lambda v : ('00'+ hex(v)[2:])[-2:]
            r = max(min(int(174 * (1.0+(12.0-len(w))/4)), 255), 0)
            g = max(min(int( 43 * (1.0+(12.0-len(w))/4)), 255), 0)
            b = max(min(int( 82 * (1.0+(12.0-len(w))/4)), 255), 0)
            c = '#' + f(r) + f(g) + f(b)
            if d == '0':
                for i in range(len(w)):
                    cv.create_rectangle(2+(px)*12, 2+(py+i)*12, 2+(px)*12+11, 2+(py+i)*12+11, fill=c, outline=c, tag = 'word')
                    cv.create_text(2+5+(px)*12, 2+5+(py+i)*12, text = w[i], tag = 'word')
                    
            if d == '1':
                for i in range(len(w)):
                    cv.create_rectangle(2+(px+i)*12, 2+(py)*12, 2+(px+i)*12+11, 2+(py)*12+11, fill=c, outline=c, tag = 'word')
                    cv.create_text(2+5+(px+i)*12, 2+5+(py)*12, text = w[i], tag = 'word')
        
        # w = set(self.words)
        # for i in w:
        #     c = 0
        #     for j in w:
        #         if i in j:
        #             c += 1
        #     if c > 1 : print(c)
                
        
        
    def clear_cv(self):
        self.cv.delete('word')

def leftdown(e):
    global fileindex, vf
    vf.clear_cv()
    fileindex = (fileindex + len(files) + 1) % len(files)
    vf = visfile(files[fileindex], cv)
def rightdown(e):
    global fileindex, vf
    vf.clear_cv()
    fileindex = (fileindex + len(files) - 1) % len(files)
    vf = visfile(files[fileindex], cv)

fileindex = 0
vf = None
root = tkinter.Tk()
dirpath = os.path.dirname(__file__).replace('\\', '/')
files = []
for i in os.listdir(dirpath):
    if 'vis' in i and '.txt' in i:
        files += [i]
tmp = []
for i in sorted(files, key = lambda x : int(x.split('.')[0][3:])):
    tmp += [dirpath + '/' + i]
files = tmp
if files:
    cv = tkinter.Canvas(root, width = 80, height = 80)
    cv.pack()
    vf = visfile(files[fileindex], cv)
    
    
    # background(cv)
    root.bind('<Button-1>', leftdown)
    root.bind('<Button-3>', rightdown)
    root.mainloop()
else:
    print('notfile')