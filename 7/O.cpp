#include <bits/stdc++.h>

using namespace std;

int n;
vector<int> d;
vector<vector<int>> p;
vector<vector<int>> mins;

int lg(int t) {
  return ((int) (log(t) / log(2))) + 1;
}

int lca(int u, int v) {
  if (d[v] > d[u]) {
    swap(u, v);
  }
  int ans = INT_MAX;

  for (int i = lg(n); i >= 0; i--) {
    if (d[u] - (1 << i) >= d[v]) {
      ans = min(ans, mins[u][i]);
      u = p[u][i];
    }
  }

  if (u == v) {
    return ans;
  }

  for (int i = lg(n); i >= 0; i--) {
    if (p[v][i] != p[u][i]) {
      ans = min(min(mins[v][i], mins[u][i]), ans);
      v = p[v][i];
      u = p[u][i];
    }
  }

  return min(min(mins[v][0], mins[u][0]), ans);
}

signed main() {
#ifdef salavay
  freopen("test.in", "r", stdin);
#else
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
#endif
  cin >> n;
  d.resize(n);
  p.resize(n);
  mins.resize(n);
  for (int i = 0; i < n; i++) {
    mins[i].resize(lg(n) + 1);
    p[i].resize(lg(n) + 1);
  }
  p[0][0] = 0;
  mins[0][0] = INT_MAX;
  for (int i = 1; i < n; i++) {
    int x, c;
    cin >> x >> c;
    p[i][0] = x - 1;
    d[i] = d[x - 1] + 1;
    mins[i][0] = c;
  }
  for (int j = 1; j < lg(n); j++) {
    for (int i = 0; i < n; i++) {
      p[i][j] = p[p[i][j - 1]][j - 1];
      mins[i][j] = min(mins[i][j - 1], mins[p[i][j - 1]][j - 1]);
    }
  }
  int m;
  cin >> m;
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    cout << lca(u - 1, v - 1) << '\n';
  }
  return 0;
}
