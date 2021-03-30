#include "bits/stdc++.h"

using namespace std;

typedef long long ll;

struct edge {
  int from;
  int to;
  ll c;
  ll fl;
  int rev;
  int id;
};

int n, m, l;
int s, t;
const ll INF = 1e14;
const int MAXN = 1510;

vector<edge> g[MAXN];
int q[MAXN], d[MAXN], ptr[MAXN];

ll dfs(int v, ll flow) {
  if (!flow) {
    return 0;
  }
  if (v == t) {
    return flow;
  }
  for (; ptr[v] < static_cast<int>(g[v].size()); ++ptr[v]) {
    edge edge = g[v][ptr[v]];
    int to = edge.to;
    ll cap = edge.c, fl = edge.fl;
    if (d[to] != d[v] + 1) {
      continue;
    }
    ll push = dfs(to, min(flow, cap - fl));
    if (push) {
      g[v][ptr[v]].fl += push;
      g[to][g[v][ptr[v]].rev].fl -= push;
      return push;
    }
  }
  return 0;
}

int main() {
#ifdef salavay
  freopen("test", "r", stdin);
#else
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
#endif
  cin >> n >> m >> l;
  for (int i = 0; i < n; i++) {
    cin >> d[i];
    if (d[i] == l) {
      t = i;
    }
    if (d[i] == 1) {
      s = i;
    }
  }
  for (int i = 0; i < m; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    a--;
    b--;
    g[a].push_back({a, b, c, 0, 0, i});
    g[b].push_back({b, a, 0, 0, 0, -1});
    g[a][g[a].size() - 1].rev = (int) g[b].size() - 1;
    g[b][g[b].size() - 1].rev = (int) g[a].size() - 1;
  }
  vector<ll> ans(m);
  while (dfs(s, INF) != 0) {}
  for (int i = 0; i < n; i++) {
    for (auto edg : g[i]) {
      if (edg.id != -1) {
        ans[edg.id] = edg.fl;
      }
    }
  }
  for (auto c : ans) {
    cout << c << " ";
  }
  return 0;
}
