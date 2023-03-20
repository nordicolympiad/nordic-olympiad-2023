#!/usr/bin/python3
import sys
import random
import lib

random.seed(int(sys.argv[-1]))
n = eval(sys.argv[1])
plen = eval(sys.argv[2])
wmax = eval(sys.argv[3])
q = eval(sys.argv[4])
w = eval(sys.argv[5])

tokens = lib.tokens(2*n+100000)

def next_token():
  return tokens.pop()

start = next_token()
data = [start]
fails = 100

while fails > 0:
  cur = []
  curl = random.randint(1, plen)
  curw = random.randint(2, wmax)
  path = [ next_token() for _ in range(curl) ]
  for i in range(curw):
    cur += path
    cur += [next_token()]
    cur += [start]
  if len(data) + len(cur) > n:
    fails -= 1
    continue
  data += cur

tokens = list(set(data))
assert len(data) <= n
n = len(data)

sys.stdout.write("{} {}\n".format(n, 1))
sys.stdout.write("{}\n".format(' '.join(map(str, data))))
sys.stdout.write("{}\n".format(q))

qs = []
for i in range(q):
  cur = random.randint(1, min(w - (q-i), plen))
  w -= cur
  qs.append(cur)

for curw in qs:
  sys.stdout.write("{} {}\n".format(curw, start))

