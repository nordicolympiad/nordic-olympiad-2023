#!/usr/bin/python3
import sys
import random

random.seed(int(sys.argv[-1]))
n = eval(sys.argv[1])
m = eval(sys.argv[2])
k = eval(sys.argv[3])

choices = [x%m + 1 for x in range(n)]

sys.stdout.write("{} {} {}\n".format(n, m, k))
sys.stdout.write("{}\n".format("\n".join(str(x) for x in choices)))
