#!/usr/bin/python3
import sys
import random
import lib

random.seed(int(sys.argv[-1]))
n = eval(sys.argv[1])
pdir = sys.argv[2]
q = eval(sys.argv[3])
w = eval(sys.argv[4])
wdist = sys.argv[5]

tokens = lib.tokens(n)

data = []
left = n
l = 1
while left > 0:
  take = min(left, l)
  data = tokens[-take:] + data
  left -= take
  l += 1

if pdir == 'right':
  pass
elif pdir == 'left':
  data = data[::-1]
else:
  assert False

tokens = list(set(data))
assert len(data) == n

sys.stdout.write("{} {}\n".format(n, 1))
sys.stdout.write("{}\n".format(' '.join(map(str, data))))
sys.stdout.write("{}\n".format(q))

qs = []
if wdist == 'even':
  for i in range(q):
    qs.append(w // q)
elif wdist == 'uniform':
  for i in range(q):
    cur = random.randint(1, w - (q-i))
    w -= cur
    qs.append(cur)
else:
  assert False

for curw in qs:
  start = [ random.choice(tokens) ]
  sys.stdout.write("{} {}\n".format(curw, ' '.join(start)))

