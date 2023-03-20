#include <bits/stdc++.h>
using namespace std;

typedef vector<unordered_set<int>> vus;

struct unionFind {
	vector<int> p;
	unionFind(int n) : p(n, -1) {}
	int find(int x) {
		return p[x] < 0 ? x : p[x] = find(p[x]);
	}

	void unite(int x, int y) {
		int xp = find(x);
		int yp = find(y);
		if (p[xp] > p[yp]) {
			swap(xp, yp);
		}
		p[xp] = yp;
	}

};

int main() {
	int n, m, q;
	cin >> n >> m >> q;
	++n;

	vus distrusts = vus(n);
	unionFind states(n);

	for(size_t i = 0; i < m; ++i) {
		int u, v;
		cin >> u >> v;
		distrusts[u].insert(v);
		distrusts[v].insert(u);
	}

	for(size_t i = 0; i < q; ++i) {
		int a, b;
		cin >> a >> b;

		a = states.find(a);
		b = states.find(b);

		if (a > b) {
			swap(a, b);
		}

		if(distrusts[a].find(b) == distrusts[a].end()) {
			states.unite(a, b);
			int c = states.find(b);
			for (auto it = distrusts[a].begin(); it != distrusts[a].end(); ++it) {
				distrusts[c].insert(*it);
				distrusts[*it].insert(c);
			}
			cout << "APPROVE" << '\n';
			continue;
		}
		cout << "REFUSE" << '\n';

	}

};
