#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;
typedef vector<vi> vvi;

map< pair<int, string>, int> counter;

map<string, int> REF;

int n,k,q,w;
vector<string> A;


// O(n * k + n * n^0.5 + (sum w ) * log(n^0.5))

// todo replace vertices with n in someplaces then there should be a test case which should hopefully TLE
// rather just replace it in all places relevant

struct edge {
    int v;
    int w;
    string c;
    edge() {

    }
    edge(int _v, int _w, string _c) {
        v = _v;
        w = _w;
        c = _c;
    }
};

map<pair<int,string>, edge> edg;

// final stuff we really need
int vertices;
vector<vector<edge>> E;

struct SCC {
    vii ls;
    vvi edg, INV;
    vi hold;
    vector<bool> vis;
    int n;

    SCC(vvi _edg, int vertices) {
        n = vertices;
        edg = _edg;
    }

    void dfs(int at, int &num) {
        vis[at] = true;
        num++;
        for(auto a : edg[at]) if(!vis[a]) dfs(a, num);
        num++;
        ls.push_back(ii(num, at));
    }

    void dfs2(int at) {
        vis[at] = true;
        hold.push_back(at);
        for(auto a : INV[at]) if(!vis[a]) dfs2(a);
    }

    vector<vi> scc() {
        int num = 0;
        vis = vector<bool>(vertices, 0);
        INV = vector<vector<int>>(vertices, vector<int>());
        for(int i = 0; i < n; i++) if(!vis[i]) dfs(i, num);
        vis = vector<bool>(vertices, 0);
        sort(ls.rbegin(), ls.rend());
        for(int i = 0; i < n; i++) for(auto a : edg[i]) INV[a].push_back(i);

        vector<vi> scc;
        for(int i = 0; i < n; i++) {
            if(!vis[ls[i].second]) dfs2(ls[i].second);
            if(hold.size() != 0) {
                if(hold.size() == 1) {
                    for(auto a : edg[ls[i].second]) {
                        if(a == ls[i].second) {
                            scc.push_back(hold);
                        }
                    }
                } else  {
                    scc.push_back(hold);
                }
            }
            hold.clear();
        }
        return scc;
    }
};

struct union_find {
	vi p;
	union_find(int n) : p(n) { 
        for(int i = 0; i < n; i++) p[i] = i;
    }
	int find(int a) { return p[a] == a ? a : p[a] = find(p[a]); }
	bool joined(int a, int b) { return find(a) == find(b);}
	void unite(int a, int b) { p[find(a)] = find(b); }
};


// takes in legal edges, returns for each index i a pair ii(a,b)
//  where a = #length of it's longest path, if #lenght = INF, then length = 10^8(int)
// where b = the next vertex it should walk to for this longest path
int inf = 100000000;

ii dp(int at, vector<ii> &memo, vvi &_E) {
    if(memo[at].first != -1) return memo[at];

    int mx_length = 0;
    int to = -1;

    vector<ii> options;
    for(auto a : _E[at]) {
        options.push_back(dp(a, memo, _E));
    }

    for(int i = 0; i < _E[at].size(); i++) {
        if(options[i].first + 1 > mx_length) {
            mx_length = options[i].first + 1;
            to = _E[at][i];
        }
    }
    return memo[at] = ii(mx_length, to);
}

vector<ii> solve_special(vector<ii> legal_edges) {
    vector<vector<int>> _E = vector<vector<int>>(n, vector<int>());
    for(int i = 0; i < legal_edges.size(); i++) {
        _E[legal_edges[i].first].push_back(legal_edges[i].second);
    }
    vector<ii> ret = vector<ii>(n, ii(-1, -1));
    SCC a(_E, vertices);

    vector<vi> scc = a.scc();
    union_find un(vertices);
    for(int i = 0; i < scc.size(); i++) {
        for(int j = 0; j < (int)scc[i].size() - 1; j++) {
            un.unite(scc[i][j], scc[i][j+1]);
        }

        for(int j = 0; j < scc[i].size(); j++) {
            for(auto a : _E[scc[i][j]]) {
                if(un.find(a) == un.find(scc[i][j])) {
                    ret[scc[i][j]] = ii(inf, a);
                }
            }
        }
    }

    /*
    for(int i = 0; i < vertices; i++) {
        for(auto a : _E[i]) {
            cout << i << " -> " << a << endl; 
        }
    }

    for(int i = 0; i < vertices; i++) {
        cout << "i = " << ret[i].first << " " << ret[i].second << endl;
    }*/

    for(int i = 0; i < vertices; i++) {
        dp(i, ret, _E);
    }

    return ret;
}

void preprocess() {
    vector<int> ints;
    vector<string> c;

    int cnt = 0;

    for(int i = 0; i < n - k + 1; i++) {
        
        string st = "";
        for(int j = i; j < i + k; j++) {
            st += A[j];
            st += " ";
        }

        if(REF.find(st) == REF.end()) {
            REF[st] = cnt;
            cnt++;
        }

        ints.push_back(REF[st]);
        if(i + k != n) {
            c.push_back(A[i+k]);
        }
    }



    vertices = cnt;
    E = vector<vector<edge>>(cnt, vector<edge>());
    for(int i = 0; i < n - k; i++) {
        counter[pair<int,string>(ints[i], c[i])]++;
    }

    for(int i = 0; i < n - k; i++) {
        edge e(ints[i+1], counter[pair<int,string>(ints[i], c[i])], c[i]);
        edg[pair<int,string>(ints[i], c[i])] = e;
    }

    for(auto e : edg) {
        E[e.first.first].push_back(e.second);
    }

    /* // For printing out the graph that's created
    for(auto a : REF) {
        cout << a.first << " , " << a.second << endl;
    }

    for(int i = 0; i < vertices; i++) {
        for(auto e : E[i]) {
            cout << i << " -> " << " vertex : " << e.v << ", weight : " <<  e.w << ", string : " <<  e.c << endl; 
        }

    }*/
}

int main() {
    cin >> n >> k;
    A = vector<string>(n);
    for(int i = 0; i < n; i++) {
        cin >> A[i];
    }

    preprocess();

    // t be the highest count
    // vertices = O(n - t^2)
    set<int> ss_unique_ts;
    for(int i = 0; i < vertices; i++) {
        for(auto a : E[i]) {
            ss_unique_ts.insert(a.w);
        }
    }

    cin >> q;
    vector<int> w(q);
    vector<int> start_pos(q);
    vector<vector<string>> ans = vector<vector<string>>(q, vector<string>());
    for(int i = 0; i < q; i++) {
        cin >> w[i];

        string st = "";
        for(int j = 0; j < k; j++) {
            string h;
            cin >> h;
            ans[i].push_back(h);
            st += h;
            st += " ";
        }

        if(REF.find(st) == REF.end()) {
            start_pos[i] = -1;
        } else {
            start_pos[i] = REF[st];
        }

    }

    int un_ts = ss_unique_ts.size();

    vector<int> unique_ts;
    for(auto a : ss_unique_ts) {
        unique_ts.push_back(a);
    }

    vector<vector<ii>> longest_path = vector<vector<ii>>(un_ts, vector<ii>(vertices, ii(-1, -1)));
    for(int i = 0; i < unique_ts.size(); i++) {
        vector<ii> legal_edges;
        for(int j = 0; j < vertices; j++) {
            for(int z = 0; z < E[j].size(); z++) {
                if(E[j][z].w >= unique_ts[i]) {
                    legal_edges.push_back(ii(j, E[j][z].v));
                }
            }
        }
        longest_path[i] = solve_special(legal_edges);
    } 


    map<ii, int> HH;
    for(int i = 0; i < vertices; i++) {
        for(int j = 0; j < E[i].size(); j++) {
            HH[ii(i, E[i][j].v)] = j;
        }
    }


    string rnd = A[0];
    vector<int> int_ans(q);

    for(int i = 0; i < q; i++) {
        int lo = 0, hi = un_ts - 1;
        int bst = -1;
        if(start_pos[i] == -1) {
            hi = -1;
        }
        while(lo <= hi) {
            int mid = (lo+hi)/2;
            if(longest_path[mid][start_pos[i]].first >= w[i]) {
                bst = mid;
                lo = mid+1;
            } else {
                hi = mid-1;
            }
        }

        if(bst == -1) {
            for(int j = 0; j < w[i]; j++) {
                ans[i].push_back(rnd);
            }
            int_ans[i] = 0;
        } else {
            int_ans[i] = unique_ts[bst];
            int at = start_pos[i];
            int dist = w[i];
            while(dist != 0) {
                int nxt = longest_path[bst][at].second;
                int ind = HH[ii(at, nxt)];
                ans[i].push_back(E[at][ind].c);

                dist--;
                at = nxt;
            }
        }
    }

    // Let's just assume that everyone has it correct
    for(int i = 0; i < q; i++) {
        // cout << int_ans[i] << endl;
        for(int j = k; j < w[i]+k; j++) {
            cout << ans[i][j] << " ";
        }
        cout << endl;
    }
}
