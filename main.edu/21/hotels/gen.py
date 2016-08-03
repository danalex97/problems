#!/usr/bin/python

import random
import sys

n = int(sys.argv[1])


with open("test", "w") as f:
    f.write(str(n) + "\n")
    TT = [None] * (n + 1)
    for i in range(1, n + 1):
        TT[i] = random.randint(1, i)
        f.write(str(i) + " " + str(TT[i]) + "\n")
