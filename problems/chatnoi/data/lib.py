#!/usr/bin/python3
import random
import string

def tokens(n):
  ts = set()
  while len(ts) < n:
    l = random.randint(1,5)
    ts.add(''.join( random.choice(string.ascii_lowercase) for _ in range(l) ))
  return list(ts)

