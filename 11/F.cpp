#include "bits/stdc++.h"

using namespace std;

typedef long long ll;

struct edge {
  int from;
  int to;
  ll c;
  ll fl;
  int rev;
  int cl;
};

int n, m;
int s, t;
const ll INF = 1e14;
const int MAXN = 250;

vector<edge> g[MAXN];
int q[MAXN], d[MAXN], ptr[MAXN];

vector<pair<int, int>> ansEdg;

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

bool bfs() {
  memset(d, -1, (n + 2) * sizeof d[0]);
  int qh = 0, qt = 0;
  q[qt++] = s;
  d[s] = 0;
  while (qh < qt && d[t] == -1) {
    int v = q[qh++];
    for (auto edge : g[v]) {
      int to = edge.to;
      ll fl = edge.fl, cap = edge.c;
      if (d[to] == -1 && fl < cap) {
        q[qt++] = to;
        d[to] = d[v] + 1;
      }
    }
  }
  return d[t] != -1;
}

ll maxFlowD() {
  ll flow = 0;
  while (true) {
    if (!bfs()) {
      break;
    }
    memset(ptr, 0, (n + 2) * sizeof ptr[0]);
    while (ll push = dfs(s, INF)) {
      flow += push;
    }
  }
  return flow;
}

void createEdge(int a, int b, int cap, int cl, bool ref = false) {
  g[a].push_back({a, b, cap, 0, 0, cl});
  g[b].push_back({b, a, 0, 0, 0, 0});
  if (ref) {
    ansEdg.emplace_back(a, g[a].size() - 1);
  }
  g[a][g[a].size() - 1].rev = (int) g[b].size() - 1;
  g[b][g[b].size() - 1].rev = (int) g[a].size() - 1;
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
  t = n + 1;
  for (int i = 0; i < m; i++) {
    int a, b, cl, cr;
    cin >> a >> b >> cl >> cr;
    createEdge(s, b, cl, cl);
    createEdge(a, b, cr - cl, cl, true);
    createEdge(a, t, cl, cl);
  }
  maxFlowD();
  for (auto edg : g[s]) {
    if (edg.fl < edg.c) {
      cout << "NO";
      return 0;
    }
  }
  cout << "YES\n";
  for (auto edg : ansEdg) {
    cout << g[edg.first][edg.second].fl + g[edg.first][edg.second].cl << '\n';
  }
  return 0;
}
