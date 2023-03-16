#!/usr/bin/python3
import sys
import random
from bisect import bisect, insort

class UnionFind:
    def __init__(self, n):
        self.n = n
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

    def merge_edges(self, x, y):
        for z in self.adj[y]:
            self.adj[z].remove(y)
            self.adj[z].add(x)
            self.adj[x].add(z)
        self.adj[y].clear()

    def unite(self, x, y):
        xp = self.find(x)
        yp = self.find(y)
        if xp == yp:
            return
        if self.p[xp] > self.p[yp]:
            xp, yp = yp, xp

        # Merge edges
        self.merge_edges(xp, yp)

        self.p[xp] += self.p[yp]
        self.p[yp] = xp

    def size(self, x):
        return -self.p[self.find(x)]
    
    def is_bad_edge(self, a, b):
        return a == b or self.distrusts(a, b)

    def get_random_edge(self):
        a, b = 0, 0
        while self.is_bad_edge(a, b):
            a = random.randint(0, self.n-1)
            b = random.randint(0, self.n-1)
        return a, b

    def is_bad_query(self, a, b):
        if gen_type == "one_refuse" and refuses >= 1:
            return True
        return uf.united(a, b)

    def get_random_query(self):
        a, b = 0, 0
        while self.is_bad_query(a, b):
            a = random.randint(0, self.n-1)
            b = random.randint(0, self.n-1)
        return a, b

    def get_full_adj(self, x):
        return self.adj[self.find(x)]

def make_tree(edges, vis, ind, l, r):
    if r <= l:
        return
    m = (l+r)//2
    make_tree(edges, vis, ind, l, m)
    make_tree(edges, vis, ind, m+1, r)
    a = ind[random.randint(l, m)]
    b = ind[random.randint(m+1, r)]
    edges.append((a, b))
    assert(a != b)
    vis.add((min(a,b), max(a,b)))

random.seed(int(sys.argv[-1]))

min_n = eval(sys.argv[1])
max_n = eval(sys.argv[2])
min_m = eval(sys.argv[3])
max_m = eval(sys.argv[4])
min_q = eval(sys.argv[5])
max_q = eval(sys.argv[6])
gen_type = sys.argv[7]

assert gen_type in ["any", "one_refuse", "cliques"]

n = random.randint(min_n, max_n)
max_m = min(max_m, n*(n-1)//2)
m = random.randint(min_m, max_m)
q = random.randint(min_q, max_q)

uf = UnionFind(n)
U = {i for i in range(n)}
edges = []
queries = []
accepts = 0
refuses = 0

for i in range(m):
    a, b = uf.get_random_edge()
    uf.add_edge(a, b)
    edges.append((a, b))

random.shuffle(edges)
refuse_index = random.randint(0, q - 1)

if gen_type == "any":
    for i in range(q):
        if uf.size(0) == n:
            q = len(queries)
            break
        a, b = uf.get_random_query()
        if not uf.distrusts(a, b):
            uf.unite(a, b)
        else:
            refuses += 1
        queries.append((a, b))
else:
    tree_edges = []
    tree_vis = set()
    ind = [i for i in range(n)]
    random.shuffle(ind)
    make_tree(tree_edges, tree_vis, ind, 0, n-1)
    random.shuffle(tree_edges)
    for i in range(q):
        a, b = tree_edges[i] if i < len(tree_edges) else uf.get_random_query()
        if not uf.distrusts(a, b):
            uf.unite(a, b)
            queries.append((a, b))
        elif refuses < 1:
            queries.append((a, b))
            refuses += 1
    q = len(queries)

    
assert m == len(edges)
assert q == len(queries)
assert gen_type != "one_refuse" or refuses <= 1

sys.stdout.write("{} {} {}\n".format(n, m, q))
for a, b in edges:
    sys.stdout.write("{} {}\n".format(a+1, b+1))
for a, b in queries:
    sys.stdout.write("{} {}\n".format(a+1, b+1))

