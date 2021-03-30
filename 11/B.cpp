#include "bits/stdc++.h"

using namespace std;

struct edge {
  int from;
  int to;
  int c;
  int fl;
};

vector<vector<int>> g;
vector<edge> edges;
vector<int> q;
vector<int> d;
vector<int> ptr;

int n, m;
int s, t;
const int INF = 1e8;

int dfs(int v, int flow) {
  if (!flow) {
    return 0;
  }
  if (v == t) {
    return flow;
  }
  for (; ptr[v] < static_cast<int>(g[v].size()); ++ptr[v]) {
    edge edge = edges[g[v][ptr[v]]];
    int to = edge.to, cap = edge.c, fl = edge.fl;
    if (d[to] != d[v] + 1) {
      continue;
    }
    int push = dfs(to, min(flow, cap - fl));
    if (push) {
      edges[g[v][ptr[v]]].fl += push;
      edges[g[v][ptr[v]] ^ 1].fl -= push;
      return push;
    }
  }
  return 0;
}

bool bfs() {
  d.assign(n, -1);
  int qh = 0, qt = 0;
  q[qt++] = s;
  d[s] = 0;
  while (qh < qt && d[t] == -1) {
    int v = q[qh++];
    for (auto edgId : g[v]) {
      edge edge = edges[edgId];
      int to = edge.to, fl = edge.fl, cap = edge.c;
      if (d[to] == -1 && fl < cap) {
        q[qt++] = to;
        d[to] = d[v] + 1;
      }
    }
  }
  return d[t] != -1;
}

int maxFlowD() {
  int flow = 0;
  while (true) {
    if (!bfs()) {
      break;
    }
    ptr.assign(n, 0);
    while (int push = dfs(s, INF)) {
      flow += push;
    }
  }
  return flow;
}

int main() {
#ifdef salavay
  freopen("test", "r", stdin);
#else
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
#endif
  cin >> n >> m;
  s = 0;
  t = n - 1;
  g.resize(n, vector<int>());
  q.resize(n, 0);
  d.resize(n, 0);
  for (int i = 0; i < m; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    a--;
    b--;
    g[a].push_back(static_cast<int>(edges.size()));
    edges.push_back({a, b, c, 0});
    g[b].push_back(static_cast<int>(edges.size()));
    edges.push_back({b, a, 0, 0});
  }
  cout << maxFlowD();
  return 0;
}
