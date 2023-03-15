#!/usr/bin/python3
import sys
import random
import lib

random.seed(int(sys.argv[-1]))
n = eval(sys.argv[1])
t = eval(sys.argv[2])
k = eval(sys.argv[3])
q = eval(sys.argv[4])
w = eval(sys.argv[5])

tokens = lib.tokens(t)
data = [ random.choice(tokens) for _ in range(n)  ]

sys.stdout.write("{} {}\n".format(n, k))
sys.stdout.write("{}\n".format(' '.join(map(str, data))))
sys.stdout.write("{}\n".format(q))

qs = []
if random.randint(0,1) == 0:
  for i in range(q):
    qs.append(w // q)
else:
  for i in range(q):
    cur = random.randint(1, w - (q-i))
    w -= cur
    qs.append(cur)

for curw in qs:
  start = []
  if len(data) < k or random.randint(1, 10) == 1:
    start = [ random.choice(tokens) for _ in range(k) ]
  else:
    i = random.randint(0, len(data)-k-1)
    start = data[i:i+k]
  sys.stdout.write("{} {}\n".format(curw, ' '.join(start)))

