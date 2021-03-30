#include "bits/stdc++.h"

using namespace std;

const int MAXN = 100010;

int used[MAXN];

vector<vector<int>> g;

vector<int> firstOrd;

void dfs(int v) {
  used[v] = 1;
  for (int c : g[v]) {
    if (used[c] == 0) {
      dfs(c);
    }
  }
  firstOrd.push_back(v);
}

int main() {
  int n, m;
  cin >> n >> m;
  g.resize(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int a, b;
    cin >> a >> b;
    a--;
    b--;
    g[a].push_back(b);
  }
  for (int i = 0; i < n; i++) {
    if (!used[i]) {
      dfs(i);
    }
  }
  reverse(firstOrd.begin(), firstOrd.end());

  if (static_cast<int>(firstOrd.size()) != n) {
    cout << "NO";
    return 0;
  }
  for (size_t i = 0; i < firstOrd.size() - 1; i++) {
    bool flag = false;
    int a = firstOrd[i], b = firstOrd[i + 1];
    for (int c : g[a]) {
      if (c == b) {
        flag = true;
      }
    }
    if (!flag) {
      cout << "NO";
      return 0;
    }
  }
  cout << "YES";
  return 0;
}
