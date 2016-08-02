#!/usr/bin/python

import sys
import random

n = int(sys.argv[1])

with open("test", "w") as f:
    sigma = ['j', 'p']
    s = "".join([random.choice(sigma) for _ in range(n)])
    f.write(str(n) + "\n")
    f.write(s + "\n")
