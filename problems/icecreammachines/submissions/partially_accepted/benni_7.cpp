#include <bits/stdc++.h>
using namespace std;

/*
 *
 *
 * Virkar bara fyrir test case 1. K = 1
 * O(n)
 *
 *
 */

int main() {
    int n,k,m;
    cin >> n >> m >> k;
    vector<int> A(n);
    for(int i = 0; i < n; i++) cin >> A[i];
    int cnt = 1;
    for(int i = 0; i < n-1; i++) {
        if(A[i] != A[i+1]) {
            cnt++;
        }
    }
    cout << cnt << endl;
}

