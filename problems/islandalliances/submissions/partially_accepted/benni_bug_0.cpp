#include <bits/stdc++.h>
using namespace std;

struct union_find {
    vector<int> P;
    union_find(int n) {
        P = vector<int>(n, 0);
        for(int i = 0; i < n; i++) {
            P[i] = i;
        }
    }

    int find(int a) {
        if(P[a] == a) return a;
        return P[a] = find(P[a]);
    }

    void unite(int a, int b) {
        P[find(a)] = find(b);
    }

};

int main() {
    cin.sync_with_stdio(false);
    int n,m,q;
    cin >> n >> m >> q;

    vector<unordered_set<int>> E = vector<unordered_set<int>>(n, unordered_set<int>());

    union_find un(n);

    for(int i = 0; i < m; i++) {
        int u,v;
        cin >> u >> v;
        u--;v--;
        E[u].insert(v);
        E[v].insert(u);
    }

    for(int i = 0; i < q; i++) {
        int u,v;
        cin >> u >> v;
        u--;v--;

        u = un.find(u);
        v = un.find(v);
        assert(v != u);
        if(E[u].size() > E[v].size()) {
            swap(u, v);
        }

        if(E[u].find(v) == E[u].end()) {
            un.unite(u,v);
            int w = un.find(v);
            for(auto l : E[u]) {
                E[w].insert(l);
            }
            cout << "APPROVE" <<  endl;
        } else {
            cout << "REFUSE" << endl;
        }

    }

};
