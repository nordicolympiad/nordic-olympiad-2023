#!/usr/bin/python3
import sys
import random

random.seed(int(sys.argv[-1]))
min_n = eval(sys.argv[1])
max_n = eval(sys.argv[2])
min_m = eval(sys.argv[3])
max_m = eval(sys.argv[4])
min_k = eval(sys.argv[5])
max_k = eval(sys.argv[6])

n = random.randint(min_n, max_n)
m = random.randint(min_m, max_m)
k = random.randint(min_k, max_k)

choices = [random.randint(1, m) for _ in range(n)]

sys.stdout.write("{} {} {}\n".format(n, m, k))
sys.stdout.write("{}\n".format("\n".join(str(x) for x in choices)))
