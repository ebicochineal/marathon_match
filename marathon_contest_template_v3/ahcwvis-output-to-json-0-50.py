#! /usr/bin/env python3
import os
import json
p = os.path.abspath(os.path.dirname(__file__)).replace('\\', '/') + '/out/'
d = {}
for i in range(0, 50):
    with open(p+str(i) + '.txt', 'r') as f:
        d[str(i)] = f.read()
with open(p+'output.json', 'w') as f:
    json.dump(d, f)