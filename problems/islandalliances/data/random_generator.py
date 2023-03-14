#!/usr/bin/python3
import sys
import random
from bisect import insort

class UnionFind:
    def __init__(self, n):
        self.n = n
        self.p = [-1 for _ in range(n)]
        self.adj = [set() for _ in range(n)]
        self.bucket_size = int(n ** 0.5)
        self.bucket_count = (n + self.bucket_size - 1) // self.bucket_size
        self.roots = [[j for j in range(i * self.bucket_size, min((i+1)*self.bucket_size, n))] for i in range(self.bucket_count)]
        self.internals = [[] for i in range(self.bucket_count)]
        self.root_count = n
        self.internal_count = 0

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

    def merge_edges(self, x, y):
        for z in self.adj[y]:
            self.adj[z].remove(y)
            self.adj[z].add(x)
            self.adj[x].add(z)
        self.adj[y].clear()

    def internalize_node(self, y):
        self.roots[y // self.bucket_size].remove(y)
        self.root_count -= 1
        insort(self.internals[y // self.bucket_size], y)
        self.internal_count += 1

    def unite(self, x, y):
        xp = self.find(x)
        yp = self.find(y)
        if xp == yp:
            return
        if self.p[xp] > self.p[yp]:
            xp, yp = yp, xp

        # Merge edges
        self.merge_edges(xp, yp)
        self.internalize_node(yp)

        self.p[xp] += self.p[yp]
        self.p[yp] = xp

    def size(self, x):
        return -self.p[self.find(x)]

    def get_random_root(self):
        x = random.randint(0, self.root_count-1)
        for bucket in self.roots:
            if x < len(bucket):
                break
            x -= len(bucket)
        return bucket[x]

    def get_random_internal(self):
        x = random.randint(0, self.internal_count-1)
        for bucket in self.internals:
            if x < len(bucket):
                break
            x -= len(bucket)
        return bucket[x]


random.seed(int(sys.argv[-1]))

min_n = eval(sys.argv[1])
max_n = eval(sys.argv[2])
min_m = eval(sys.argv[3])
max_m = eval(sys.argv[4])
min_q = eval(sys.argv[5])
max_q = eval(sys.argv[6])

n = random.randint(min_n, max_n)

max_m = min(max_m, n*(n-1)//2)

m = random.randint(min_m, max_m)
q = random.randint(min_q, max_q)

uf = UnionFind(n)
edges = []

for i in range(m):
    a, b = 0, 0
    while True:
        a = random.randint(0, n-1)
        b = random.randint(0, n-1)
        if a != b and not uf.distrusts(a, b):
            break
    uf.add_edge(a, b)
    edges.append((a, b))

queries = []

for i in range(q):
    if uf.size(0) == n:
        q = len(queries)
        break
    a, b = 0, 0
    while uf.united(a, b):
        a = random.randint(0, n-1)
        b = random.randint(0, n-1)
    if not uf.distrusts(a, b):
        uf.unite(a, b)

    queries.append((a, b))
    
assert m == len(edges)
assert q == len(queries)

sys.stdout.write("{} {} {}\n".format(n, m, q))
for a, b in edges:
    sys.stdout.write("{} {}\n".format(a+1, b+1))
for a, b in queries:
    sys.stdout.write("{} {}\n".format(a+1, b+1))
