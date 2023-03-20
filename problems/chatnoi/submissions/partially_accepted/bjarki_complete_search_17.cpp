#include <bits/stdc++.h>
using namespace std;

map<vector<string>, map<string,int>> cnt;
set<string> words;

int best, k;
vector<string> best_sol;
vector<string> cur;

void bt(int mn, int m) {
  if (m == 0) {
    if (mn > best) {
      best = mn;
      best_sol = cur;
    }
    return;
  }

  vector<string> last(cur.begin() + (int)cur.size() - k, cur.end());
  for (auto w : words) {
    cur.push_back(w);
    bt(min(mn, cnt[last][w]), m-1);
    cur.pop_back();
  }
}

int main() {
  int n;
  cin >> n >> k;

  vector<string> doc;
  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;
    doc.push_back(s);
  }
  words = set<string>(doc.begin(), doc.end());
  for (int i = 0; i+k < n; i++) {
    vector<string> cur;
    for (int j = 0; j < k; j++) {
      cur.push_back(doc[i+j]);
    }
    cnt[cur][doc[i+k]]++;
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

    cur = pattern;
    best_sol = vector<string>(k+m, doc[0]);
    best = 0;

    bt(1000000000, m);

    for (int i = k; i < k+m; i++) {
      cout << best_sol[i] << " ";
    }
    cout << endl;
  }

  return 0;
}

