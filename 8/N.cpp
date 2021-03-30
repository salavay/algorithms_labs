#include "bits/stdc++.h"

using namespace std;

struct vertex {
  int v;
  int w;
};

int n, m;
const int MAXN = 1010;

vector<vector<vertex>> g, gr;

int used[MAXN], usedr[MAXN];

void dfs(int v, int m1) {
  used[v] = 1;
  for (auto c : g[v]) {
    if (c.w > m1) continue;
    if (!used[c.v]) {
      dfs(c.v, m1);
    }
  }
}

void dfsr(int v, int m1) {
  usedr[v] = 1;
  for (auto c : gr[v]) {
    if (c.w > m1) continue;
    if (!usedr[c.v]) {
      dfsr(c.v, m1);
    }
  }
}

int main() {
  cin >> n;
  g.resize(n, vector<vertex>());
  gr.resize(n, vector<vertex>());
  for (int a = 0; a < n; a++) {
    for (int b = 0; b < n; b++) {
      int w;
      cin >> w;
      if (a == b) continue;
      g[a].push_back({b, w});
      gr[b].push_back({a, w});
    }
  }
  int l = -1, r = 1e9 + 10;
  while (r - l > 1) {
    for (int i = 0; i < n; i++) {
      used[i] = 0;
      usedr[i] = 0;
    }
    int m1 = (r + l) / 2;
    dfs(0, m1);
    dfsr(0, m1);
    bool flag = true;
    for (int i = 0; i < n; i++) {
      if (used[i] == 0 || usedr[i] == 0) {
        flag = false;
      }
    }
    if (flag) {
      r = m1;
    } else {
      l = m1;
    }
  }
  cout << r;
  return 0;
}
