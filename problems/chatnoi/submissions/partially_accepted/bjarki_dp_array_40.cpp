#include <bits/stdc++.h>
using namespace std;

vector<vector<pair<int,int>>> adj;
int mem[5010][5010],
    nxt[5010][5010];

int dp(int at, int es) {
  if (es == 0) {
    return 1000000000;
  }
  if (mem[at][es] != -1) {
    return mem[at][es];
  }
  int mx = 0;
  for(auto it : adj[at]) {
    int cur = min(it.second, dp(it.first, es-1));
    if (cur > mx) {
      mx = cur;
      nxt[at][es] = it.first;
    }
  }
  return mem[at][es] = mx;
}

int main() {
  ios_base::sync_with_stdio(false);
  memset(mem,-1,sizeof(mem));
  int n, k;
  cin >> n >> k;
  deque<int> window;
  unordered_map<string, int> word_id;
  vector<string> id_word;
  map<vector<int>, int> kgram_id;
  vector<vector<int>> id_kgram;
  vector<map<int,int>> adj_map;
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
    if ((int)window.size() > k) {
      window.pop_front();
    }
    if ((int)window.size() == k) {
      vector<int> kgram_vector(window.begin(), window.end());
      if (kgram_id.find(kgram_vector) == kgram_id.end()) {
        kgram_id.insert(make_pair(kgram_vector, kgram_id.size()));
        id_kgram.push_back(kgram_vector);
        adj_map.push_back(map<int,int>());
      }
      int kgram = kgram_id[kgram_vector];
      if (last_kgram != -1) {
        adj_map[last_kgram][kgram]++;
      }
      last_kgram = kgram;
    }
  }
  for (auto entry : adj_map) {
    adj.emplace_back(entry.begin(), entry.end());
  }
  int qs;
  cin >> qs;
  for (int q = 0; q < qs; q++) {
    int w;
    cin >> w;
    vector<int> kgram_vec;
    for (int i = 0; i < k; i++) {
      string s;
      cin >> s;
      assert(word_id.find(s) != word_id.end());
      kgram_vec.push_back(word_id[s]);
    }
    if (kgram_id.find(kgram_vec) == kgram_id.end()) {
      for (int i = 0; i < w; i++) {
        cout << id_word[0] << " ";
      }
      cout << endl;
    } else {
      int kgram = kgram_id[kgram_vec];
      dp(kgram, w);
      int at = kgram;
      for (int i = 0; i < w; i++) {
        int cur = nxt[at][w-i];
        cout << id_word[*id_kgram[cur].rbegin()] << " ";
        at = cur;
      }
      cout << endl;
    }
  }
  return 0;
}
