#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> g;

vector<int> used;
vector<int> p;

int ans;

bool dfs(int v) {
  if (used[v] == 1) return false;
  used[v] = 1;
  for (auto c : g[v]) {
    ans -= (p[c] == -1);
    if (p[c] == -1 || dfs(p[c])) {
      p[c] = v;
      return true;
    }
  }
  return false;
}

int main() {
#ifdef salavay
  freopen("test", "r", stdin);
#else
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
#endif
  int n, m;
  cin >> n >> m;
  ans = n;
  g.resize(n, vector<int>());
  p.resize(n, -1);
  for (int i = 0; i < m; i++) {
    int a, b;
    cin >> a >> b;
    a--;
    b--;
    g[a].push_back(b);
  }
  for (int i = 0; i < n; i++) {
    used.assign(n, 0);
    dfs(i);
  }
  cout << ans;
  return 0;
}
