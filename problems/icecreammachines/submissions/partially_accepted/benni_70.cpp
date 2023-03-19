#include <bits/stdc++.h>
using namespace std;

/*
 *
 *
 * O(n * k + n * m)
 * Should fit groups 1,2,3,4,5,6 with 80 points
 *
 */


int main() {
    int n,k,m;
    cin >> n >> m >> k;
    vector<int> A(n);

    for(int i = 0; i < n; i++) {
        cin >> A[i];
    }

    vector<vector<int>> NXT = vector<vector<int>>(n, vector<int>(m+1, 0));
    vector<int> last(m+1, -1);
    for(int i = n-1; i >= 0; i--) {
        for(int j = 0; j <= m; j++) {
            NXT[i][j] = last[j];
        }

        last[A[i]] = i;
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
                if(NXT[i][Machine[j]] != -1) {
                    far = NXT[i][Machine[j]];
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

