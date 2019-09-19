#! /usr/bin/env python3
import os
import sys
import zipfile

class Option:
    def __init__(self):
        p = os.path.abspath(os.path.dirname(__file__)).replace('\\', '/') + '/'
        self.crdir = '' if p == '/' else p
        self.cmdc = {}
        self.cmdi = {}
        self.op = ''
        self.cls = ''
        self.source = ''
        self.getch = None
        self.maxthread = 1
        self.compare = 'greater'
        self.errtag = 'no'
        self.os = 'win'
        sp = ';'
        if len(sys.argv) > 1 : self.op = sys.argv[1].replace('\\', '/')
        if 'win' in sys.platform and 'darwin' != sys.platform:
            self.cls = 'cls'
            self.os = 'win'
            # self.getch = self.getch_win
        else:
            self.os = 'unix'
            self.cls = 'clear'
            # self.getch = self.getch_unix
            sp = ':'
        with open(self.crdir + 'setting.ini', encoding='UTF-8') as f:
            mode = ''
            for i in f.readlines():
                s = i.strip()
                if len(i) > 1 and i[:2] != '//':
                    if s[0] == '[':
                        mode = s
                    else:
                        s = s.replace('\\', '/')
                        if mode == '[source]':
                            self.source = s
                        if mode == '[path]':
                            os.environ['PATH'] = os.environ['PATH'] + sp + s
                        if mode == '[browser]':
                            self.browser = s
                        if mode == '[tle]':
                            self.timeout = int(s)
                        if mode == '[compile]':
                            lang, cmd = map(lambda x : x.strip(), s.split(':', 1))
                            self.cmdc[lang] = cmd.split()
                        if mode == '[interpreter]':
                            lang, cmd = map(lambda x : x.strip(), s.split(':', 1))
                            self.cmdi[lang] = cmd.split()
                        if mode == '[maxthread]':
                            self.maxthread = int(s)
                        if mode == '[compare]':
                            self.compare = s
                        if mode == '[errtag]':
                            self.errtag = s

dict_sh = {}
# [1:]  -\n
dict_sh['.cpp'] = '''
#!/bin/sh
g++ -std=gnu++11 -O3 /workdir/{0}.cpp -o /workdir/{0}
echo '/workdir/{0}' > /workdir/command.txt'''[1:]

dict_sh['.java'] = '''
#!/bin/sh
javac /workdir/{0}.java
echo 'java -cp /workdir {0}' > /workdir/command.txt'''[1:]

dict_sh['.py'] = '''
#!/bin/sh
echo 'python3.6 /workdir/{0}.py' > /workdir/command.txt'''[1:]

dict_sh['.cs'] = '''
#!/bin/sh
csc /workdir/{0}.cs /out:/workdir/{0}.exe
echo 'mono /workdir/{0}.exe' > /workdir/command.txt'''[1:]

def try_mkdir(dir):
    try:
        if not os.path.exists(dir) : os.mkdir(dir)
    except:
        pass

def to_zip(target_path = ''):
    op = Option()
    if target_path == '' : target_path = op.crdir + op.source
    name, ext = os.path.splitext(target_path)
    name = name.replace('\\', '/').split('/')[-1]
    
    # print(dict_sh[ext])
    dir_path = op.crdir + 'submit_zipfiles/'
    try_mkdir(dir_path)
    zip_cnt = 1
    
    for i in os.listdir(dir_path):
        if os.path.splitext(dir_path + i)[1] == '.zip' : zip_cnt += 1
    zip_path = dir_path + str(zip_cnt) +'.zip'
    
    if os.path.exists(target_path):
        zf = zipfile.ZipFile(zip_path, 'w', zipfile.ZIP_STORED)
        # zf.writestr('solution.sh' , dict_sh[ext].format(name))
        with open(target_path, 'r') as f:
            zf.writestr(name + ext , f.read())
        print('create', zip_path)
    else:
        print('not found', target_path)
    
if __name__ == '__main__':
    if len(sys.argv) > 1:# target file
        to_zip(sys.argv[1])
    else:
        to_zip()