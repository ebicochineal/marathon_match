#! /usr/bin/env python3
import os
import sys
import xml.etree.ElementTree
import xml.etree.ElementTree as ET

class TopCoderMarathonUser:
    def __init__(self, rd, result):
        self.handle = result[1]
        self.cr = result[6]
        self.submission = []
        self.testcases = []
        self.rank = result[0]
        self.provisional_rank = result[2]
        self.lang = result[5]
        self.final_score = '%.2f' % float(result[4])
        self.provisional_score = '%.2f' % float(result[3])
        self.country = ''
        self.uniqs = 0
        self.bests = 0
        self.zeros = 0
        self.zeroseeds = []
        self.tles = 0
        self.was = 0
        self.arating = '-'
        self.mrating = '-'
        self.sumscore = 0
        self.codertype = 'Marathon'
        self.time = 0
        
        p = os.path.dirname(__file__).replace('\\', '/') + '/'
        p = '' if p == '/' else p
        n = rd + '/' + self.cr + '.xml'
        
        tree = ET.ElementTree(file = p + n)
        root = tree.getroot()
        for i in root.iter('handle') : self.name = i.text
        for i in root[3]:
            self.submission += [[x.text for x in i]]
        for i in root[4]:
            self.testcases += [[x.text for x in i]]
            # [testcase_id, score, time, fatal_error_ind]
        
        for i in self.testcases:
            if float(i[1]) < 0:
                self.zeros += 1
                self.zeroseeds += [i[0]]
            else:
                self.sumscore += float(i[1])
            if float(i[2]) < 0:
                self.tles += 1
            else:
                self.time += float(i[2])
        self.time /= len(self.testcases)
        self.time = int(self.time)
        self.was = self.zeros - self.tles
        
        with open(p + rd + '/' + 'b' + self.cr + '.txt', 'r') as f:
            t = f.read()
            self.arating, self.mrating = map(int, t.split('\n')[:2])
            self.country = t.split('\n')[2]
        if self.arating > self.mrating:
            self.codertype = 'Algorithm'
        if abs(self.arating - self.mrating) < 200 or (self.arating >= 1500 and self.mrating >= 1500):
            self.codertype = 'Algorithm And Marathon'
        self.arating, self.mrating = [[str(x), '-'][x == 0] for x in [self.arating, self.mrating]]
def get_results(rd):
    p = os.path.dirname(__file__).replace('\\', '/') + '/'
    p = '' if p == '/' else p
    r = []
    n = rd + '/html.txt'
    with open(p + n, 'r') as f:
        r = []
        text = f.read()
        text = text.replace('<tr class=\'light\'>', '<sp>')
        text = text.replace('<tr class=\'dark\'>', '<sp>')
        for i in text.split('<sp>')[1:]:
            t = i.split('</tr>')[0]
            u = []
            for j in t.split('>')[1:]:
                j = j.split('<')[0].strip()
                if j : u += [j]
            cr = t.split('cr=')[1].split('&')[0].split('\"')[0]
            r += [u[:6] + [cr]]
        r = sorted(r, key = lambda x : int(x[0]))
    return r

def rating_color_string(s, a):
    n = max([int(x) for x in a if x != '-'])
    t = '<font color=\"%s\" style=\"text-shadow:1px 1px 0px black\">' + '%s</font>'%s
    if n >= 2200 : return t%'#EF3A3A'
    if n >= 1500 : return t%'#FCD617'
    if n >= 1200 : return t%'#616BD5'
    if n >= 900 : return t%'#69C329'
    if n >= 1 : return t%'#9D9FA0'
    return s
p = os.path.dirname(__file__).replace('\\', '/') + '/'
p = '' if p == '/' else p
dirs = []
for i in os.listdir(p):
    if os.path.isdir(p + i):
        dirs += [i]

for rd in dirs:
    print(rd)
    a = []
    for i in get_results(rd):
        a += [TopCoderMarathonUser(rd, i)]

    scoretype = [0, 1][a[0].sumscore > a[-1].sumscore]

    for i in range(len(a[0].testcases)):
        bestscore = -1
        bestcnt = 0
        for j in a:
            score = float(j.testcases[i][1])
            if scoretype:
                if score > bestscore:
                    bestcnt = 1
                    bestscore = score
                elif score == bestscore:
                    bestcnt += 1
            else:
                if bestscore < 0 or 0 <= score < bestscore:
                    bestcnt = 1
                    bestscore = score
                elif score == bestscore:
                    bestcnt += 1
        for j in a:
            if float(j.testcases[i][1]) == bestscore : j.bests += 1
            if bestcnt == 1 and float(j.testcases[i][1]) == bestscore : j.uniqs += 1

    o = [['RANK', '', '', 'HANDLE', 'COUNTRY', 'LANG', 'MM', 'ALGO', 'SCORE', '', '', 'BESTS', 'UNIQS', 'ZEROS', 'TIME']]
    olens = [len(o[-1][x]) for x in range(len(o[-1]))]

    for i in a:
        o += [list(map(str, [i.rank, '<', i.provisional_rank, i.handle, i.country, i.lang, i.mrating, i.arating, i.final_score, '<', i.provisional_score, i.bests, i.uniqs, i.zeros, i.time]))]
        olens = [max(len(o[-1][x]), olens[x]) for x in range(len(o[-1]))]

    out = ''
    for i in range(len(o)):
        t = o[i]
        s = ''
        for j in range(len(t)):
            v = t[j]
            if 3 <= j <= 5:
                if i > 0 and j == 3:
                    s += rating_color_string(v.ljust(olens[j]), [a[i-1].mrating, a[i-1].arating, 0])
                else:
                    s += v.ljust(olens[j])
            else:
                if i > 0 and j == 6:
                    s += rating_color_string(v.rjust(olens[j]), [a[i-1].mrating, 0])
                elif i > 0 and j == 7:
                    s += rating_color_string(v.rjust(olens[j]), [a[i-1].arating, 0])
                else:
                    s += v.rjust(olens[j])
            s += ' '
        out += s + '\n'
    
    outpath = ''
    if len(dirs) > 1:
        outpath = p + rd + '/' + 'statistics.html'
    else:
        outpath = p + 'statistics.html'
    with open(outpath, 'w') as f:
        f.write('Statistics  \n<pre style=\"background-color:#f7f7f7\">\n' + out + '</pre>')
    # with open(p + 'README.md', 'w') as f:
    #     f.write('#### Statistics  \n<pre style=\"background-color:#f7f7f7\"><b>\n' + out + '</b></pre>')
    print(outpath)