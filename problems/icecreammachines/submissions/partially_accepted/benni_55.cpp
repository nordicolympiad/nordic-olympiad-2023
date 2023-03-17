#include <bits/stdc++.h>
using namespace std;

/*
 *
 *
 * O(n * n * k)
 * Ætti að Passa hóp 1,2,3,4 -> 55
 * mögulega 5 (en það myndi þurfa hærra time limit)
 * 
 *
 *
 */


int main() {
    int n,k,m;
    cin >> n >> m >> k;
    vector<int> A(n);
    for(int i = 0; i < n; i++) cin >> A[i];

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
                for(int z = i + 1; z < n; z++) {
                    if(Machine[j] == A[z]) {
                        far = z;
                        break;
                    }
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

