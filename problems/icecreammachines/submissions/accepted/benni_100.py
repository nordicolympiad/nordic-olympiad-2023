#!/usr/bin/python3
import sys
from queue import PriorityQueue

n,m,k = [int(x) for x in sys.stdin.readline().split()]
A = []
for x in range(n):
    h = int(sys.stdin.readline())
    A.append(h)

mp = {}
want = [0 for x in range(n)]
for x in range(n-1,-1,-1):
    if A[x] not in mp:
        want[x] = n
    else:
        want[x] = mp[A[x]]
    mp[A[x]] = x

cnt = 0
q = PriorityQueue()
have = [False for _ in range(m+1)]
havesz = 0
NXT = {}

for x in range(n):
    if have[A[x]]:
        NXT[A[x]] = want[x]
        q.put((-NXT[A[x]], A[x]))
    else:
        while havesz == k:
            next_item = q.get()
            a = next_item[0]
            b = next_item[1]


            if have[b]:
                if -a == NXT[b]:
                    have[b] = False
                    havesz -= 1
        cnt += 1
        
        NXT[A[x]] = want[x]
        have[A[x]] = True
        havesz += 1
        q.put((-NXT[A[x]], A[x]))


print(cnt)


