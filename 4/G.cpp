#include <bits/stdc++.h>
// #define int ll

typedef long long ll;

using namespace std;

const int INF = 2e9;

int n;

struct ver {
  int l;
  int r;
  int val;
};

signed main() {
  freopen("meetings.in", "r", stdin);
  freopen("meetings.out", "w", stdout);
  int k;
  cin >> n >> k;
  int nm = 1 << n;
  vector<vector<int>> mood(n, vector<int>(nm, -INF));
  vector<vector<int>> dp(n, vector<int>(nm, 0));
  vector<vector<ver>> g(n, vector<ver>(n));
  for (int i = 0; i < n; i++) {
    ver tmp;
    cin >> tmp.l >> tmp.r >> tmp.val;
    if (k >= tmp.l && k <= tmp.r) {
      dp[i][1 << i] = 1;
      mood[i][1 << i] = k + tmp.val;
    }
    for (int j = 0; j < n; j++) {
      if (i != j)
        g[j][i] = tmp;
    }
  }
  vector<vector<int>> prev(n, vector<int>(nm, -1));
  for (int mask = 1; mask < (1 << n); mask++) {
    for (int l = 0; l < n; l++) {
      if ((mask & (1 << l)) > 0) {
        for (int f = 0; f < n; f++) {
          int ml = (1 << l);
          if (f != l && mood[f][mask - ml] >= g[f][l].l && mood[f][mask - ml] <= g[f][l].r &&
              // mood[f][mask - ml] + g[f][l].val > mood[l][mask] &&
              dp[f][mask - ml] + 1 >= dp[l][mask]) {
            mood[l][mask] = mood[f][mask - ml] + g[f][l].val;
            prev[l][mask] = f;
            dp[l][mask] = dp[f][mask - ml] + 1;
          }
        }
      }
    }
  }
  int ans = 0, startm = 0, startv = 0;
  for (int i = 0; i < (1 << n); i++) {
    for (int j = 0; j < n; j++) {
      if (ans < dp[j][i]) {
        ans = max(ans, dp[j][i]);
        startm = i;
        startv = j;
      }
    }
  }
  cout << ans;
  if (ans == 0) return 0;
  cout << '\n';
  vector<int> ansv;
  while (true) {
    ansv.push_back(startv);
    if (prev[startv][startm] == -1) break;
    int nv = prev[startv][startm];
    startm = startm - (1 << startv);
    startv = nv;
  }
  reverse(ansv.begin(), ansv.end());
  for (auto c : ansv) {
    cout << c + 1 << ' ';
  }
  return 0;
}
