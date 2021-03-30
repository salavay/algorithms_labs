#include <bits/stdc++.h>
// #define int ll

typedef long long ll;

using namespace std;

const int INF = 2e9;

int n, m;

vector<vector<int>> dp;
vector<vector<int>> g;

signed main() {
  freopen("salesman.in", "r", stdin);
  freopen("salesman.out", "w", stdout);
  cin >> n >> m;
  dp.resize(n, vector<int>((1 << n), INF));
  g.resize(n, vector<int>(n, INF));
  for (int i = 0; i < m; i++) {
    int f, to, w;
    cin >> f >> to >> w;
    f--;
    to--;
    g[f][to] = w;
    g[to][f] = w;
  }
  for (int i = 0; i < n; i++) {
    dp[i][1 << i] = 0;
  }
  for (int mask = 1; mask < (1 << n); mask++) {
    for (int l = 0; l < n; l++) {
      if ((mask & (1 << l)) > 0) {
        for (int f = 0; f < n; f++) {
          if (g[l][f] != INF && f != l && dp[l][mask] > dp[f][mask - (1 << l)] + g[l][f]) {
            dp[l][mask] = dp[f][mask - (1 << l)] + g[l][f];
          }
        }
      }
    }
  }
  int ans = INF;
  for (int i = 0; i < n; i++) {
    ans = min(ans, dp[i][(1 << n) - 1]);
  }
  if (ans != INF) {
    cout << ans;
  } else {
    cout << -1;
  }
  return 0;
}
