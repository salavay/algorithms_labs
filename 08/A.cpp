#include "bits/stdc++.h"

using namespace std;

const int MAXN = 1e6;

int used[MAXN];

vector<vector<int>> g;
vector<int> ans;

void dfs(int v) {
  used[v] = 1;
  for (int c : g[v]) {
    if (used[c] == 1) {
      cout << "-1";
      exit(0);
    }
    if (used[c] == 0) {
      dfs(c);
    }
  }
  ans.push_back(v);
  used[v] = 2;
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
  reverse(ans.begin(), ans.end());
  for (int c : ans) {
    cout << c + 1 << " ";
  }
  return 0;
}
