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
  map<vector<string>, map<string,int>> cnt;
  for (int i = 0; i+k < n; i++) {
    vector<string> cur;
    for (int j = 0; j < k; j++) {
      cur.push_back(words[i+j]);
    }
    cnt[cur][words[i+k]]++;
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
    int mx = 0;
    string best = words[0];
    for (auto entry : cnt[pattern]) {
      if (entry.second > mx) {
        mx = entry.second;
        best = entry.first;
      }
    }
    cout << best << endl;
  }

  return 0;
}

