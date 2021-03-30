#include "bits/stdc++.h"

using namespace std;

const int INF = 1e9;
const int MAXN = 1e3 + 10;

int g[MAXN][MAXN];

vector<int> u, v, p, way;

int main() {
#ifdef salavay
  freopen("test", "r", stdin);
#else
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
#endif
  int n;
  cin >> n;
  u.assign(n + 1, 0);
  v.assign(n + 1, 0);
  p.assign(n + 1, 0);
  way.assign(n + 1, 0);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      cin >> g[i][j];
    }
  }
  for (int i = 1; i <= n; i++) {
    p[0] = i;
    int j0 = 0;
    vector<int> mins(n + 1, INF);
    vector<int> used(n + 1, 0);
    while (p[j0] != 0) {
      used[j0] = true;
      int i0 = p[j0], alph = INF, j1;
      for (int j = 1; j <= n; ++j)
        if (!used[j]) {
          int cur = g[i0][j] - u[i0] - v[j];
          if (cur < mins[j])
            mins[j] = cur, way[j] = j0;
          if (mins[j] < alph)
            alph = mins[j], j1 = j;
        }
      for (int j = 0; j <= n; ++j) {
        if (used[j]) {
          u[p[j]] += alph, v[j] -= alph;
        } else {
          mins[j] -= alph;
        }
      }
      j0 = j1;
    }
    while (j0) {
      int j1 = way[j0];
      p[j0] = p[j1];
      j0 = j1;
    }
  }
  vector<int> ans(n + 1);
  for (int j = 1; j <= n; ++j) {
    ans[p[j]] = j;
  }
  int sum = 0;
  for (int i = 1; i <= n; i++) {
    sum += g[i][ans[i]];
  }
  cout << sum << '\n';
  for (int i = 1; i <= n; i++) {
    cout << i << " " << ans[i] << "\n";
  }
  return 0;
}
