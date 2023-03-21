#include <climits>
#include <set>
#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include <deque>

#include "validate.h"
using namespace std;

int k;
map<vector<int>, int> likelihood;

int score(vector<int> sol) {
  int mn = 1000000000;
  deque<int> window;
  for (int i = 0; i < (int)sol.size(); i++) {
    window.push_back(sol[i]);
    if ((int)window.size() > k+1) {
      window.pop_front();
    }
    if ((int)window.size() == k+1) {
      mn = min(mn, likelihood[vector<int>(window.begin(), window.end())]);
    }
  }
  return mn;
}

int main(int argc, char **argv) {
  init_io(argc,argv);

  int n;
  judge_in >> n >> k;

  unordered_map<string,int> word_id;
  deque<int> window;
  for (int i = 0; i < n; i++) {
    string s;
    judge_in >> s;
    if (word_id.find(s) == word_id.end()) {
      word_id.insert(make_pair(s, (int)word_id.size()));
    }
    window.push_back(word_id[s]);
    if ((int)window.size() > k+1) {
      window.pop_front();
    }
    if ((int)window.size() == k+1) {
      likelihood[vector<int>(window.begin(), window.end())]++;
    }
  }

  int qs;
  judge_in >> qs;

  for (int q = 0; q < qs; q++) {
    int m;
    judge_in >> m;
    vector<int> judge_sol, author_sol;
    for (int i = 0; i < k; i++) {
      string s;
      judge_in >> s;
      judge_sol.push_back(word_id[s]);
      author_sol.push_back(word_id[s]);
    }
    for (int i = 0; i < m; i++) {
      string s;
      judge_ans >> s;
      judge_sol.push_back(word_id[s]);
    }
    for (int i = 0; i < m; i++) {
      string s;
      if (!(author_out >> s)) {
        wrong_answer("Wrong answer: missing output for query %d.\n", q+1);
      }
      if (word_id.find(s) == word_id.end()) {
        wrong_answer("Wrong answer: word number %d is invalid for query %d.\n", i+1, q+1);
      }
      author_sol.push_back(word_id[s]);
    }
    int judge_score = score(judge_sol),
        author_score = score(author_sol);
    if (author_score < judge_score) {
      wrong_answer("Wrong answer: author paragraph had lower score (%d) than judge (%d) for query %d.\n", author_score, judge_score, q+1);
    }
    /*
    if (author_score > judge_score) {
      // TODO: Disable during contest?
      judge_error("Judge error: author paragraph had higher score (%d) than judge (%d) for query %d.\n", author_score, judge_score, q+1);
    }
    */
  }

  string junk;
  if (author_out >> junk) {
    wrong_answer("Wrong answer: trailing output.\n");
  }

  accept();
}

