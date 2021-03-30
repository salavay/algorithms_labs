#include "bits/stdc++.h"

using namespace std;

const int MAXN = 2e4 + 10;

int used[MAXN];
int times[MAXN];
int up[MAXN];
int entryTime = 0;

struct edge {
  int to;
  int ind;
};

vector<vector<edge>> g;
set<int> ans;

void dfs(int v, int from) {
  used[v] = 1;
  entryTime++;
  times[v] = entryTime;
  up[v] = entryTime;
  for (auto c : g[v]) {
    if (c.to == from) continue;
    if (used[c.to] == 1) {
      up[v] = min(up[v], times[c.to]);
    } else if (used[c.to] == 0) {
      dfs(c.to, v);
      up[v] = min(up[v], up[c.to]);
      if (times[v] < up[c.to]) {
        ans.insert(c.ind);
      }
    }
  }
  used[v] = 2;
}

int main() {
  int n, m;
  cin >> n >> m;
  g.resize(n, vector<edge>());
  for (int i = 0; i < m; i++) {
    int a, b;
    cin >> a >> b;
    a--;
    b--;
    g[a].push_back({b, i});
    g[b].push_back({a, i});
  }
  for (int i = 0; i < n; i++) {
    if (used[i] == 0) {
      dfs(i, -1);
    }
  }
  cout << ans.size() << '\n';
  for (auto c : ans) {
    cout << c + 1 << " ";
  }
  return 0;
}
