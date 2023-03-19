#!/usr/bin/python3
from queue import PriorityQueue

n,m,k = [int(x) for x in input().split()]
A = []
for x in range(n):
    h = int(input())
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
have = set()
NXT = {}

for x in range(n):
    if A[x] in have:
        NXT[A[x]] = want[x]
        q.put((-NXT[A[x]], A[x]))
    else:
        while len(have) == k:
            next_item = q.get()
            a = next_item[0]
            b = next_item[1]


            if b in have:
                if -a == NXT[b]:
                    have.remove(b)
        cnt += 1
        
        NXT[A[x]] = want[x]
        have.add(A[x])
        q.put((-NXT[A[x]], A[x]))


print(cnt)


