#include<bits/stdc++.h>
#define int ll

using namespace std;

typedef long long ll;

const int INF = 1e11;

vector<pair<int, int> > g[100005];

int d[1000005], used[100005];

set<pair<int, int> > s;

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int n, m;
  cin >> n >> m;
  for (int i = 1; i < n; i++) {
    s.insert({INF, i});
    d[i] = INF;
  }
  for (int j = 0; j < m; j++) {
    int a, b, w;
    cin >> a >> b >> w;
    a--;
    b--;
    g[a].emplace_back(b, w);
    g[b].emplace_back(a, w);
  }
  s.insert({0, 0});
  d[0] = 0;
  while (!s.empty()) {
    int v = (*s.begin()).second;
    used[v] = 1;
    s.erase({d[v], v});
    for (size_t i = 0; i < g[v].size(); i++) {
      int to = g[v][i].first, w = g[v][i].second;
      if (d[to] > w + d[v]) {
        s.erase({d[to], to});
        s.insert({w + d[v], to});
        d[to] = w + d[v];
      }
    }
  }
  for (int i = 0; i < n; i++) {
    cout << d[i] << " ";
  }
  return 0;
}
