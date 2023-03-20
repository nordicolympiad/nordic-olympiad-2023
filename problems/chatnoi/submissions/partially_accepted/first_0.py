#!/usr/bin/python3
n, k = map(int, input())
doc = input()
q = int(input())
for i in range(q):
    a,*b = input().split()
    a = int(a)
    b = ' '.join(b)
    start_index = doc.find(b)
    end_index = start_index + len(b) + 1
    print(' '.join(doc[end_index:].split()[:a]))
