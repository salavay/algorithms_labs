#include <bits/stdc++.h>

using namespace std;

const int MAXN = 3e4 + 10;

int d[MAXN];
int used[MAXN];

vector<vector<int>> g;

int main() {
  int n;
  cin >> n;
  g.resize(n, vector<int>());
  int m;
  cin >> m;
  for (int i = 0; i < m; i++) {
    int a, b;
    cin >> a >> b;
    a--;
    b--;
    g[a].push_back(b);
    g[b].push_back(a);
  }
  queue<int> q;
  q.push(0);
  used[0] = 1;
  while (!q.empty()) {
    auto v = q.front();
    q.pop();
    for (auto to : g[v]) {
      if (!used[to]) {
        used[to] = 1;
        d[to] = d[v] + 1;
        q.push(to);
      }
    }
  }
  for (int i = 0; i < n; i++) {
    cout << d[i] << " ";
  }
  return 0;
}
