#include <bits/stdc++.h>
using namespace std;

const int VERTICES = 500000 + 100;
const int INF = 1000000000;

vector<vector<pair<int,int>>> adj;
int cur_idx;
int idx[VERTICES],
    low_link[VERTICES],
    longest_path[VERTICES],
    next_vertex[VERTICES];
bool on_stack[VERTICES];
stack<int> S;

void dfs(int v, int weight) {
  idx[v] = cur_idx;
  low_link[v] = cur_idx;
  cur_idx++;
  longest_path[v] = 0;
  next_vertex[v] = -1;
  S.push(v);
  on_stack[v] = true;

  for (auto edge : adj[v]) {
    if (edge.second < weight) continue;
    int w = edge.first;
    if (idx[w] == -1) {
      dfs(w, weight);
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
  for (int i = 0; i < (int)weights.size(); i++) {
    cur_idx = 0;
    memset(idx, -1, sizeof(idx));
    for (int j = 0; j < (int)adj.size(); j++) {
      if (idx[j] == -1) {
        dfs(j, weights[i]);
      }
    }
    longest_path_by_weight.emplace_back(longest_path, longest_path + adj.size());
    next_vertex_by_weight.emplace_back(next_vertex, next_vertex + adj.size());
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
          hi = (int)weights.size() - 1,
          res = -1;
      while (lo <= hi) {
        int mid = (lo+hi)/2;
        if (longest_path_by_weight[mid][kgram] >= w) {
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
          int cur = next_vertex_by_weight[res][at];
          cout << id_word[*id_kgram[cur].rbegin()] << " ";
          at = cur;
        }
        cout << endl;
      }
    }
  }
  return 0;
}
