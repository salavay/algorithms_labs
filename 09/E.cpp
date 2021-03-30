#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll INF2 = 7 * 1e18;

struct edge {
  int from;
  int to;
  ll w;
};

edge e[5010];

ll d[2010];
int ban[2010];

vector<vector<int>> g;
int used[2010];

void dfs(int v, int from) {
  used[v] = 1;
  ban[v] = 1;
  for (auto c : g[v]) {
    if (!used[c] && c != from) {
      dfs(c, v);
    }
  }
}

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int n, m, s;
  cin >> n >> m >> s;
  g.resize(n, vector<int>());
  s--;
  for (int i = 0; i < n; i++) {
    d[i] = INF2;
  }
  for (int j = 0; j < m; j++) {
    int a, b;
    ll w;
    cin >> a >> b >> w;
    a--;
    b--;
    g[a].push_back(b);
    e[j] = {a, b, w};
  }
  d[s] = 0;
  for (int j = 0; j < n; j++) {
    for (int i = 0; i < m; i++) {
      edge edg = e[i];
      if (d[edg.from] < INF2) {
        if (ban[edg.from] || d[edg.to] < -INF2 || (j == n - 1 && d[edg.to] > d[edg.from] + edg.w)) {
          ban[edg.to] = 1;
        }
        if (d[edg.to] > d[edg.from] + edg.w && j != n - 1) {
          d[edg.to] = max(-INF2 - 10, d[edg.from] + edg.w);
        }
      }
    }
  }
  for (int i = 0; i < n; i++) {
    if (ban[i] && !used[i]) {
      dfs(i, -1);
    }
  }
  for (int i = 0; i < n; i++) {
    if (ban[i]) {
      cout << "-\n";
    } else if (d[i] == INF2) {
      cout << "*\n";
    } else {
      cout << d[i] << '\n';
    }
  }
  return 0;
}
