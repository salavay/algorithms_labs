#include<bits/stdc++.h>

using namespace std;

const int INF = 1e9;

const int MAXN = 410;

int d[MAXN][MAXN];

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int n, m;
  cin >> n >> m;
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= n; j++) {
      d[i][j] = INF;
      if (i == j) d[i][i] = 0;
    }
  }
  for (int i = 0; i < m; i++) {
    int a, b, w;
    cin >> a >> b >> w;
    d[a][b] = w;
  }
  for (int i = 1; i <= n; i++) {
    for (int u = 1; u <= n; u++) {
      for (int v = 1; v <= n; v++) {
        if (d[u][i] < INF && d[i][v] < INF) {
          d[u][v] = min(d[u][v], d[u][i] + d[i][v]);
        }
      }
    }
  }
  for (int u = 1; u <= n; u++) {
    for (int v = 1; v <= n; v++) {
      cout << d[u][v] << " ";
    }
    cout << '\n';
  }
  return 0;
}
