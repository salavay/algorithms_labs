#include "bits/stdc++.h"

using namespace std;

size_t const ALPHABET = 26;

class vertex {
 public:
  bool is_term;
  vector<int> edges;
  int sufflink;
  vector<int> ids;
  vertex() : is_term(false), edges(ALPHABET, -1), sufflink(-1), ids() {}
};

void add(vector<vertex> &tree, string &s, int &id) {
  int cur = 0;
  for (auto i : s) {
    int c = static_cast<int>(i - 'a');
    if (tree[cur].edges[c] == -1) {
      tree[cur].edges[c] = tree.size();
      cur = tree.size();
      tree.emplace_back();
    } else {
      cur = tree[cur].edges[c];
    }
  }
  tree[cur].ids.emplace_back(id);
  tree[cur].is_term = true;
}

void create_sufflinks(vector<vertex> &tree) {
  tree.emplace_back();
  tree[0].sufflink = static_cast<int>(tree.size()) - 1;
  for (size_t i = 0; i < ALPHABET; i++) {
    tree.back().edges[i] = 0;
  }
  queue<size_t> q;
  q.push(0);
  while (!q.empty()) {
    size_t cur = q.front();
    q.pop();
    for (size_t i = 0; i < ALPHABET; i++) {
      if (tree[cur].edges[i] == -1) {
        tree[cur].edges[i] = tree[tree[cur].sufflink].edges[i];
      } else {
        q.push(tree[cur].edges[i]);
        tree[tree[cur].edges[i]].sufflink = tree[tree[cur].sufflink].edges[i];
      }
    }
  }
}

int main() {
#ifdef salavay
  freopen("test", "r", stdin);
#else
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
#endif
  vector<vertex> tree(1);

  vector<string> strings;
  int k;
  cin >> k;
  strings.resize(k);
  for (int i = 0; i < k; i++) {
    cin >> strings[i];
    add(tree, strings[i], i);
  }
  create_sufflinks(tree);
  string text;
  cin >> text;
  vector<int> ans(k, 0);
  int cur = 0;
  for (auto c : text) {
    int ch = c - 'a';
    cur = tree[cur].edges[ch];
    int find_vertex = cur;
    while (find_vertex != 0 && tree[find_vertex].sufflink != -1) {
      if (tree[find_vertex].is_term) {
        for (auto answers : tree[find_vertex].ids) {
          ans[answers] = 1;
        }
      }
      int tmp = find_vertex;
      find_vertex = tree[find_vertex].sufflink;
      tree[tmp].sufflink = -1;
    }
  }
  for (auto c : ans) {
    if (c == 1) {
      cout << "YES\n";
    } else {
      cout << "NO\n";
    }
  }
  return 0;
}
