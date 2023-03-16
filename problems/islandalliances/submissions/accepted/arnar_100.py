#!/usr/bin/python3
import sys
import random

class UnionFind:
    def __init__(self, n):
        self.p = [-1 for _ in range(n)]
        self.adj = [set() for _ in range(n)]

    def find(self, x):
        while self.p[x] >= 0:
            x, self.p[x] = self.p[x], self.p[self.p[x]]
        return x

    def united(self, x, y):
        return self.find(x) == self.find(y)

    def add_edge(self, x, y):
        self.adj[x].add(y)
        self.adj[y].add(x)

    def distrusts(self, x, y):
        return self.find(y) in self.adj[self.find(x)]

    def unite(self, x, y):
        xp = self.find(x)
        yp = self.find(y)
        if xp == yp:
            return
        if self.p[xp] > self.p[yp]:
            xp, yp = yp, xp
        for z in self.adj[yp]:
            self.adj[z].remove(yp)
            self.adj[z].add(xp)
            self.adj[xp].add(z)
        self.adj[yp].clear()
        self.p[xp] += self.p[yp]
        self.p[yp] = xp

    def size(self, x):
        return -self.p[self.find(x)]

n, m, q = map(int, sys.stdin.readline().split())

uf = UnionFind(n)

for i in range(m):
    a, b = map(int, sys.stdin.readline().split())
    uf.add_edge(a - 1, b - 1)


for i in range(q):
    a, b = map(int, sys.stdin.readline().split())
    a, b = a - 1, b - 1
    if not uf.distrusts(a, b):
        uf.unite(a, b)
        print("APPROVE")
    else:
        print("REFUSE")
