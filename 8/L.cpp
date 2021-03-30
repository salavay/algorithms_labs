#include "bits/stdc++.h"

using namespace std;

const int MAXN = 2e6 + 10;

int used[MAXN];
int times[MAXN];
int up[MAXN];
int entryTime = 0;

struct edge {
  int to;
  int ind;
};

vector<vector<edge>> g;
set<int> ans;
stack<edge> s;
int color[MAXN];
int cntColor = 0;

void upCalc(int v, int from) {
  used[v] = 1;
  entryTime++;
  times[v] = entryTime;
  up[v] = entryTime;
  for (auto c : g[v]) {
    if (c.to == from) continue;
    if (used[c.to] == 1) {
      s.push(c);
      up[v] = min(up[v], times[c.to]);
    } else if (used[c.to] == 0) {
      size_t sz = s.size();
      s.push(c);
      upCalc(c.to, v);
      up[v] = min(up[v], up[c.to]);
      if (times[v] <= up[c.to]) {
        // c.to - bridge
        cntColor++;
        while (s.size() > sz) {
          edge ver = s.top();
          s.pop();
          color[ver.ind] = cntColor;
        }
      }
    }
  }
  used[v] = 2;
}

int main() {
  int n, m;
  cin >> n >> m;
  g.resize(n, vector<edge>());
  for (int i = 0; i < m; i++) {
    int a, b;
    cin >> a >> b;
    a--;
    b--;
    g[a].push_back({b, i});
    g[b].push_back({a, i});
  }
  for (int i = 0; i < n; i++) {
    if (used[i] == 0) {
      upCalc(i, -1);
    }
  }
  if (!s.empty()) {
    cntColor++;
    while (!s.empty()) {
      color[s.top().ind] = cntColor;
      s.pop();
    }
  }
  cout << cntColor << '\n';
  for (int i = 0; i < m; i++) {
    cout << color[i] << " ";
  }
  return 0;
}
