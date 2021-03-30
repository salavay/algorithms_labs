#include "bits/stdc++.h"

using namespace std;

const int MAXN = 1e6;

int used[MAXN];

vector<vector<int>> g;

int cnt = 0;

void dfs(int v) {
  used[v] = cnt;
  for (int c : g[v]) {
    if (used[c] == 0) {
      dfs(c);
    }
  }
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
    g[b].push_back(a);
  }
  for (int i = 0; i < n; i++) {
    if (used[i] == 0) {
      cnt++;
      dfs(i);
    }
  }
  cout << cnt << '\n';
  for (int i = 0; i < n; i++) {
    cout << used[i] << " ";
  }
  return 0;
}
