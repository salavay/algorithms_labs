#include "bits/stdc++.h"

using namespace std;

const int MAXN = 1e5 + 10;

int used[MAXN];
int color[MAXN];

vector<vector<int>> g;

void dfs(int v, int from) {
  used[v] = 1;
  if (from != -1) {
    color[v] = !static_cast<bool>(color[from]);
  }
  for (auto c : g[v]) {
    if (c == from) continue;
    if (used[c] == 0) {
      dfs(c, v);
    }
    if (color[c] == color[v]) {
      cout << "NO";
      exit(0);
    }
  }
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
    g[b].push_back(a);
  }
  for (int i = 0; i < n; i++) {
    if (used[i] == 0) {
      dfs(i, -1);
    }
  }
  cout << "YES";
  return 0;
}
