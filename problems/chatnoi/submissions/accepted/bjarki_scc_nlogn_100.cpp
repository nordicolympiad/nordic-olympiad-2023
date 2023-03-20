#include <bits/stdc++.h>
using namespace std;

const int VERTICES = 100000 * 10 + 100;
const int INF = 1000000000;

vector<vector<pair<int,int>>> adj;
int cur_idx, start_idx;
int idx[VERTICES],
    low_link[VERTICES],
    longest_path[VERTICES],
    next_vertex[VERTICES];
bool on_stack[VERTICES];
stack<int> S;

void dfs(int v) {
  idx[v] = cur_idx;
  low_link[v] = cur_idx;
  cur_idx++;
  longest_path[v] = 0;
  next_vertex[v] = -1;
  S.push(v);
  on_stack[v] = true;

  for (auto edge : adj[v]) {
    int w = edge.first;
    if (idx[w] < start_idx) {
      dfs(w);
      low_link[v] = min(low_link[v], low_link[w]);
      if (low_link[w] <= idx[v]) {
        longest_path[v] = INF;
        next_vertex[v] = w;
      } else if (1 + longest_path[w] > longest_path[v]) {
        longest_path[v] = 1 + longest_path[w];
        next_vertex[v] = w;
      }
    } else if (on_stack[w]) {
      low_link[v] = min(low_link[v], idx[w]);
      longest_path[v] = INF;
      next_vertex[v] = w;
    } else {
      if (1 + longest_path[w] > longest_path[v]) {
        longest_path[v] = 1 + longest_path[w];
        next_vertex[v] = w;
      }
    }
  }

  if (low_link[v] == idx[v]) {
    while (true) {
      int w = S.top();
      S.pop();
      on_stack[w] = false;
      if (w == v) {
        break;
      }
    }
  }
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
  set<int> weight_set;
  for (auto entry : adj_map) {
    adj.emplace_back(entry.begin(), entry.end());
    for (auto edge : entry) {
      weight_set.insert(edge.second);
    }
  }
  vector<int> weights(weight_set.begin(), weight_set.end());
  vector<vector<int>> longest_path_by_weight;
  vector<vector<int>> next_vertex_by_weight;
  vector<vector<int>> pos_by_weight((int)adj.size());
  list<int> rem;
  for (int i = 0; i < (int)adj.size(); i++) {
    rem.push_back(i);
  }
  cur_idx = 0;
  memset(idx, -1, sizeof(idx));
  for (int i = 0; i < (int)weights.size(); i++) {
    for (auto it = rem.begin(); it != rem.end(); ) {
      for (int j = 0; j < (int)adj[*it].size(); ) {
        if (adj[*it][j].second < weights[i]) {
          swap(adj[*it][j], adj[*it].back());
          adj[*it].pop_back();
        } else {
          j++;
        }
      }
      if (adj[*it].empty()) {
        auto cur = it;
        ++it;
        rem.erase(cur);
      } else {
        ++it;
      }
    }
    start_idx = cur_idx;
    for (auto v : rem) {
      if (idx[v] < start_idx) {
        dfs(v);
      }
    }
    vector<int> cur_longest_path, cur_next_vertex;
    int at = 0;
    for (auto v : rem) {
      cur_longest_path.push_back(longest_path[v]);
      cur_next_vertex.push_back(next_vertex[v]);
      pos_by_weight[v].push_back(at);
      at++;
    }
    longest_path_by_weight.push_back(cur_longest_path);
    next_vertex_by_weight.push_back(cur_next_vertex);
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
      int lo = 0,
          hi = (int)pos_by_weight[kgram].size() - 1,
          res = -1;
      while (lo <= hi) {
        int mid = (lo+hi)/2;
        if (longest_path_by_weight[mid][pos_by_weight[kgram][mid]] >= w) {
          res = mid;
          lo = mid+1;
        } else {
          hi = mid-1;
        }
      }
      if (res == -1) {
        for (int i = 0; i < w; i++) {
          cout << id_word[0] << " ";
        }
        cout << endl;
      } else {
        int at = kgram;
        for (int i = 0; i < w; i++) {
          int cur = next_vertex_by_weight[res][pos_by_weight[at][res]];
          cout << id_word[*id_kgram[cur].rbegin()] << " ";
          at = cur;
        }
        cout << endl;
      }
    }
  }
  return 0;
}
