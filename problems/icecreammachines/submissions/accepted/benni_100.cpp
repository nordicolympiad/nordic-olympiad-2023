#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;

/*
 *
 *
 * O(n * log(k))
 * 
 *
 *
 */

int n,k,m;
map<int, set<int>> LL;
vector<int> A;

int nxt(int at) {
    auto a = LL[A[at]].lower_bound(at+1);
    if(a == LL[A[at]].end()) return n;
    return *a;
}


int main() {
    cin >> n >> k >> m;
    A = vector<int>(n);

    for(int i = 0; i < n; i++) {
        cin >> A[i];
        LL[A[i]].insert(i);
    }

    map<int,int> NXT;
    set<ii> pos;

    int cnt = 0;
    for(int i = 0; i < n; i++) {
        int bst = -1;
        int farthest = 0;
        if(NXT.size() < k) {
            if(NXT.find(A[i]) == NXT.end()) {
                cnt++;
                int value = nxt(i);
                pos.insert(ii(-value, A[i]));

                NXT[A[i]] = value;
            } else {
                int value = NXT[A[i]];
                pos.erase(ii(-value, A[i]));
                value = nxt(i);
                pos.insert(ii(-value, A[i]));
                NXT[A[i]] = value;
            }
        } else {
            if(NXT.find(A[i]) != NXT.end()) {
                int value = NXT[A[i]];
                pos.erase(ii(-value, A[i]));
                value = nxt(i);
                pos.insert(ii(-value, A[i]));
                NXT[A[i]] = value;
            } else {
                auto a = pos.begin();
                NXT.erase((*a).second);
                pos.erase(a);

                cnt++;
                int value = nxt(i);
                pos.insert(ii(-value, A[i]));
                NXT[A[i]] = value;
            }
        }
    }

    cout << cnt << endl;
}

