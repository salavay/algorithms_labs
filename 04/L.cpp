#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<vector<pair<int, ll>>> g;
vector<vector<ll>> f;

void dfsAlg(int from, int v) {
  for (int i = 0; i < int(g[v].size()); i++) {
    if (from != g[v][i].first) {
      dfsAlg(v, g[v][i].first);
      f[v][0] = max(f[v][0], f[g[v][i].first][1] + g[v][i].second - f[g[v][i].first][2]);
      f[v][1] += f[g[v][i].first][2];
    }
  }
  f[v][0] += f[v][1];
  f[v][2] = max(f[v][0], f[v][1]);
}

signed main() {
  freopen("matching.in", "r", stdin);
  freopen("matching.out", "w", stdout);
  int n;
  cin >> n;
  g.resize(n, vector<pair<int, ll>>());
  f.resize(n, vector<ll>(3, 0ll));
  for (int i = 0; i < n - 1; i++) {
    int x, to;
    ll w;
    cin >> x >> to >> w;
    x--;
    to--;
    g[x].push_back({to, w});
    g[to].push_back({x, w});
  }
  dfsAlg(-1, 0);
  cout << f[0][2];
  return 0;
}
