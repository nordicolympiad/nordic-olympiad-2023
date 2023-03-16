#include <bits/stdc++.h>
using namespace std;

vector<map<int,int> > adj;
map<pair<int,int>, int> mem;

int dp(int at, int es) {
  if (es == 0) {
    return 1000000000;
  }
  pair<int,int> state(at, es);
  if (mem.find(state) != mem.end()) {
    return mem[state];
  }
  int mx = 0;
  for(auto it : adj[at]) {
    mx = max(mx, min(it.second, dp(it.first, es-1)));
  }
  return mem[state] = mx;
}

int main() {
  ios_base::sync_with_stdio(false);
  int n, k;
  cin >> n >> k;
  deque<int> window;
  unordered_map<string, int> word_id;
  vector<string> id_word;
  map<vector<int>, int> kgram_id;
  vector<vector<int>> id_kgram;
  int last_kgram = -1;
  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;
    if (word_id.find(s) == word_id.end()) {
      word_id.insert(make_pair(s, word_id.size()));
      id_word.push_back(s);
    }
    int t = word_id[s];
    window.push_back(t);
    if (window.size() > k) {
      window.pop_front();
    }
    if (window.size() == k) {
      vector<int> kgram_vector(window.begin(), window.end());
      if (kgram_id.find(kgram_vector) == kgram_id.end()) {
        kgram_id.insert(make_pair(kgram_vector, kgram_id.size()));
        id_kgram.push_back(kgram_vector);
        adj.push_back(map<int,int>());
      }
      int kgram = kgram_id[kgram_vector];
      if (last_kgram != -1) {
        adj[last_kgram][kgram]++;
      }
      last_kgram = kgram;
    }
  }
  int qs;
  cin >> qs;
  for (int q = 0; q < qs; q++) {
    int w;
    cin >> w;
    bool ok = true;
    vector<int> kgram_vec;
    for (int i = 0; i < k; i++) {
      string s;
      cin >> s;
      if (word_id.find(s) == word_id.end()) {
        ok = false;
        continue;
      }
      kgram_vec.push_back(word_id[s]);
    }
    if (kgram_id.find(kgram_vec) == kgram_id.end()) {
      ok = false;
    }
    if (!ok) {
      cout << 0 << endl;
      continue;
    }
    int kgram = kgram_id[kgram_vec];
    cout << dp(kgram, w) << endl;
  }
  return 0;
}
