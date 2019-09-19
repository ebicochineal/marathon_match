#! /usr/bin/env python3
import os
import sys
import time
import urllib.request, urllib.parse
import xml.etree.ElementTree
import xml.etree.ElementTree as ET

def get_topcoder_xml(rd, cr):
    url = 'http://www.topcoder.com/longcontest/stats/?module=IndividualResultsFeed' + '&rd=' + rd +'&cr=' + cr
    return urllib.request.urlopen(url).read().decode('utf-8')
def create_xml_file(rd, cr):
    p = os.path.dirname(__file__).replace('\\', '/') + '/'
    p = '' if p == '/' else p
    n = rd + '/' + cr + '.xml'
    try_mkdir(p + rd + '/')
    if os.path.exists(p + n) : return -1
    t = get_topcoder_xml(rd, cr)
    with open(p + n , 'w') as f : f.write(t)
def create_html_file(rd):
    url = 'https://community.topcoder.com/longcontest/stats/?module=ViewOverview&nr=1000&rd=' + rd
    t = urllib.request.urlopen(url).read().decode('utf-8')
    p = os.path.dirname(__file__).replace('\\', '/') + '/'
    p = '' if p == '/' else p
    n = rd + '/html.txt'
    try_mkdir(p + rd + '/')
    with open(p + n , 'w') as f : f.write(t)
def create_b_file(rd, cr, handle):
    p = os.path.dirname(__file__).replace('\\', '/') + '/'
    p = '' if p == '/' else p
    if os.path.exists(p + rd + '/' + 'b' + cr + '.txt') : return -1
    a = '0'
    m = '0'
    country = '-'
    url = 'http://api.topcoder.com/v2/users/' + handle +' /statistics/data/mms'
    t = urllib.request.urlopen(url).read().decode('utf-8')
    try:
        country = t.split('\"country\": \"')[1].split('\"')[0]
        a = t.split('Algorithm')[1].split('\"rating\": ')[1].split(',')[0]
        m = t.split('Marathon Match')[1].split('\"rating\": ')[1].split(',')[0]
    except:
        pass
    try_mkdir(p + rd + '/')
    with open(p + rd + '/' + 'b' + cr + '.txt' , 'w') as f : f.write(a + '\n' + m + '\n' + country)
    
def try_mkdir(dir):
    try:
        if not os.path.exists(dir) : os.mkdir(dir)
    except:
        pass
def get_cr_list(rd):
    url = 'https://community.topcoder.com/longcontest/stats/?module=ViewOverview&nr=1000&rd=' + rd
    text = urllib.request.urlopen(url).read().decode('utf-8')
    s = set()
    for i in text.split('<td class="value"><a href="http://www.topcoder.com/tc?module=MemberProfile')[1:]:
        cr = i.split('cr=')[1].split('&')[0].split('\"')[0]
        handle = i.split('>')[1].split('<')[0]
        s.add((cr, handle))
    return list(s)

rd = 0
if len(sys.argv) > 1:
    q =sys.argv[1]
else:
    q = input('rd=')
if 'rd=' in q:
    for i in q.split('&'):
        if 'rd=' in i:
            rd = i.split('rd=')[1]
else:
    rd = q
    
create_html_file(rd)
print('get html')
print('1')
for cr, handle in get_cr_list(rd):
    try:
        a = create_b_file(rd, cr, handle)
        if a < 0:
            print('pass', cr, handle)
            continue
        print('get', cr, handle)
        time.sleep(2)
    except:
        print('err', cr, handle)
print('2')
for cr, handle in get_cr_list(rd):
    try:
        a = create_xml_file(rd, cr)
        if a < 0:
            print('pass', cr, handle)
            continue
        print('get', cr, handle)
        time.sleep(10)
        
    except:
        print('err', cr, handle)
