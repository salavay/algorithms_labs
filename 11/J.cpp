#include "bits/stdc++.h"

using namespace std;

const int MAXN = 1e3 + 10;

struct edge {
  int to;
  int w;
};

int n;
vector<vector<edge>> g;
vector<int> used;
vector<int> p;

int ans = 0;

bool dfs(int v, int minW) {
  if (used[v] == 1) return false;
  used[v] = 1;
  for (auto c : g[v]) {
    if (c.w >= minW && (p[c.to] == -1 || (!used[p[c.to]] && dfs(p[c.to], minW)))) {
      p[c.to] = v;
      return true;
    }
  }
  return false;
}

bool check(int m) {
  p.assign(n, -1);
  ans = 0;
  for (int i = 0; i < n; i++) {
    used.assign(n, 0);
    if (dfs(i, m)) {
      ans++;
    }
  }
  return ans >= n;
}

int main() {
#ifdef salavay
  freopen("test", "r", stdin);
#else
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
#endif
  cin >> n;
  g.resize(n, vector<edge>());
  int l = -1, r = 1e6;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      int w;
      cin >> w;
      l = min(l, w);
      r = max(r, w);
      g[i].push_back({j, w});
    }
  }
  l--;
  r++;
  while (r - l > 1) {
    int m = (r + l) / 2;
    if (check(m)) {
      l = m;
    } else {
      r = m;
    }
  }
  cout << l;
  return 0;
}
