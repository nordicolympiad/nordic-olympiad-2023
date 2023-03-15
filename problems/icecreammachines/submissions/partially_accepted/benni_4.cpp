#include <bits/stdc++.h>
using namespace std;

/*
 *
 * O(n * 2^m * m)
 * Á þetta að fá pass í 3. n <= 10^5, k <= 5, m <= 10?
 *
 * 
 */


int main() {
    cin >> n >> k >> m;
    A  = vector<int>(n, 0);
    memo = vector<vector<int>>(n+1, vector<int>((1<<m) +1, -1));
    for(int i = 0; i < n; i++) cin >> A[i];
    vector<int> prev((1<<m) + 1, 0);

    for(int i = n-1; i >= 0; i--) {
        vector<int> curr((1<<m) + 1, n);
        for(int j = 0; j < (1<<m); j++) {
            int cnt = 0;
            for(int z = 0; z < m; z++) if(j & (1<<z)) cnt++;

            int pos = A[i] - 1;
            if(cnt > k) continue;
            if(j & (1<<pos)) {
                curr[j] = prev[j];
            } else if(cnt < k) {
                curr[j] = prev[j | (1<<pos)] + 1;
            } else {
                for(int z = 0; z < m; z++) {
                    if(j & (1<<z)) {
                        curr[j] = min(curr[j], prev[j ^ (1<<z) ^ (1<<pos)] + 1);
                    }
                }
            }
        }
        prev = curr;
    }

    cout << prev[0] << endl;
}

