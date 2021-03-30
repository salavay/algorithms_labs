#include "bits/stdc++.h"

using namespace std;

struct vertex {
  int v;
  int w;
  int ind;
};

int n, m;
const int MAXN = 1010;
bool flag;

vector<vector<vertex>> g;

int used[MAXN];

void dfs(int v, int m1) {
  for (auto c : g[v]) {
    if (c.ind > m1) continue;
    if (used[c.v] == -1) {
      if (c.w == 1) {
        used[c.v] = used[v];
      } else {
        used[c.v] = (used[v] != 1);
      }
      dfs(c.v, m1);
    } else if ((c.w == 1 && used[c.v] != used[v]) ||
        (c.w == 0 && used[c.v] == used[v])) {
      flag = false;
      return;
    }
  }
}

int main() {
  cin >> n >> m;
  g.resize(n, vector<vertex>());
  for (int i = 0; i < m; i++) {
    int a, b;
    string s;
    cin >> a >> b >> s;
    a--;
    b--;
    g[a].push_back({b, s == "T", i});
    g[b].push_back({a, s == "T", i});
  }
  int l = -1, r = 1e4 + 10;
  while (r - l > 1) {
    flag = true;
    memset(used, -1, n * sizeof(int));
    int m1 = (l + r) / 2;
    for (int i = 0; i < n; i++) {
      if (used[i] == -1) {
        used[i] = 0;
        dfs(i, m1);
      }
    }
    if (flag) {
      l = m1;
    } else {
      r = m1;
    }
  }
  cout << min(r, m);
  return 0;
}
