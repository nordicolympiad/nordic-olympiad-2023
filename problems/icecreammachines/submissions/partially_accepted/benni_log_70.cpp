#include <bits/stdc++.h>
using namespace std;

/*
 *
 *
 * O(n * log(n) * k)
 * Should fit groups 1,2,3,4,5 with 65 points
 *
 *
 */


int main() {
    int n,k,m;
    cin >> n >> m >> k;
    vector<int> A(n);
    vector<set<int>> LL(300010);

    for(int i = 0; i < n; i++) {
        cin >> A[i];
        LL[A[i]].insert(i);
    }

    vector<int> Machine(k, -1);
    int ans = 0;
    for(int i = 0; i < n; i++) {
        int bst = -1;
        int farthest = 0;

        for(int j = 0; j < k; j++) {
            if(Machine[j] == -1) {
                bst = j;
                farthest = n;
            } else {
                // what is this?
                int far = n;
                auto a = LL[Machine[j]].lower_bound(i + 1);
                if(a != LL[Machine[j]].end()) {
                    far = *a;
                }

                if(far > farthest) {
                    farthest = far;
                    bst = j;
                }
            }
        }

        for(int j = 0; j < k; j++) {
            if(Machine[j] == A[i]) {
                bst = -1;
            }
        }

        if(bst == -1) {
            
        } else {
            ans++;
            Machine[bst] = A[i];
        }
    }

    cout << ans << endl;
}

