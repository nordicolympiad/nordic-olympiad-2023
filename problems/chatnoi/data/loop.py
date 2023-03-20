#!/usr/bin/python3
import sys
import random
import lib

random.seed(int(sys.argv[-1]))
n = eval(sys.argv[1])
nloop = eval(sys.argv[2])
k = eval(sys.argv[3])
q = eval(sys.argv[4])
M = eval(sys.argv[5])

tokens = list(lib.tokens(nloop))
data = []
for i in range(n):
  data.append(tokens[i%len(tokens)])

sys.stdout.write("{} {}\n".format(n, k))
sys.stdout.write("{}\n".format(' '.join(map(str, data))))
sys.stdout.write("{}\n".format(q))

for i in range(q):
  t = random.randint(0, len(data)-k-1)
  start = data[t:t+k]
  sys.stdout.write("{} {}\n".format(M//q, ' '.join(start)))

