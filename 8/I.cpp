#include "bits/stdc++.h"

using namespace std;

const int MAXN = 2e4 + 10;

int used[MAXN];
int times[MAXN];
int up[MAXN];
int entryTime = 0;

vector<vector<int>> g;
set<int> ans;

void dfs(int v, int from) {
  used[v] = 1;
  entryTime++;
  times[v] = entryTime;
  up[v] = entryTime;
  int childs = 0;
  for (auto c : g[v]) {
    if (c == from) continue;
    if (used[c] == 1) {
      up[v] = min(up[v], times[c]);
    } else if (used[c] == 0) {
      dfs(c, v);
      up[v] = min(up[v], up[c]);
      if (times[v] <= up[c] && from != -1) {
        ans.insert(v);
      }
      childs++;
    }
  }
  if (childs > 1 && from == -1) {
    ans.insert(v);
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
  cout << ans.size() << '\n';
  for (auto c : ans) {
    cout << c + 1 << "\n";
  }
  return 0;
}
