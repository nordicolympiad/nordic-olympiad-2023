#!/usr/bin/python3
import sys
import random

# Specific generator for one of my solutions, that kills it getting to many points
# must have n >= (m-1) * 2
# and m = k

random.seed(int(sys.argv[-1]))
n = eval(sys.argv[1])
m_k = eval(sys.argv[2])




m = m_k
k = m



assert(n >= (m-1) * 2)

A = [x for x in range(1,m)]
left_n = n - len(A) *  2
choices = []
for x in A:
    choices.append(x)
for x in range(left_n):
    choices.append(m)
for x in A:
    choices.append(x)

sys.stdout.write("{} {} {}\n".format(n, m, k))
sys.stdout.write("{}\n".format("\n".join(str(x) for x in choices)))
