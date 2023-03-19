#!/usr/bin/env python3
import sys
import re

line = sys.stdin.readline()
assert re.match('^(1|[1-9][0-9]*) (1|[1-9][0-9]*)\n$', line, re.MULTILINE)
n, k = map(int, line.strip().split())
assert 1 <= n <= 10**5
assert 1 <= k <= 10
assert k < n

line = sys.stdin.readline()
assert re.match('^[a-z]+( [a-z]+)*\n$', line, re.MULTILINE)
words = line.strip().split()
assert len(words) == n
for word in words:
  assert 1 <= len(word) <= 10

line = sys.stdin.readline()
assert re.match('^(1|[1-9][0-9]*)\n$', line, re.MULTILINE)
qs = int(line)
assert 1 <= qs <= 10**5

tokens = set(words)
wsum = 0
for q in range(qs):
  line = sys.stdin.readline()
  assert re.match('^(1|[1-9][0-9]*)( [a-z]+)+\n$', line, re.MULTILINE)
  arr = line.strip().split()
  w = int(arr[0])
  arr = arr[1:]
  assert len(arr) == k
  for word in arr:
    assert word in tokens

  assert 1 <= w <= 10**5
  wsum += w

assert wsum <= 10**5

assert not sys.stdin.read()
sys.exit(42)

