#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, k;
  cin >> n >> k;

  vector<string> words;
  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;
    words.push_back(s);
  }

  int qs;
  cin >> qs;

  for (int q = 0; q < qs; q++) {
    int m;
    cin >> m;
    vector<string> pattern(k);
    for (int i = 0; i < k; i++) {
      cin >> pattern[i];
    }
    map<string,int> found;
    for (int i = 0; i+k < n; i++) {
      bool ok = true;
      for (int j = 0; j < k; j++) {
        if (words[i+j] != pattern[j]) {
          ok = false;
          break;
        }
      }
      if (ok) {
        found[words[i+k]]++;
      }
    }
    int mx = 0;
    string best = words[0];
    for (auto entry : found) {
      if (entry.second > mx) {
        mx = entry.second;
        best = entry.first;
      }
    }
    cout << best << endl;
  }

  return 0;
}

