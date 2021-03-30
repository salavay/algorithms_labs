#include <bits/stdc++.h>

using namespace std;

int main() {
  freopen("lis.in", "r", stdin);
  freopen("lis.out", "w", stdout);
  int n;
  cin >> n;
  vector<int> a(n);
  vector<int> dp(n + 1, 1e9);
  vector<int> p(n + 1, -1);
  vector<int> par(n + 1, -1);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  dp[0] = -1e9;
  int ans = 0;
  for (int i = 0; i < n; i++) {
    int ind = upper_bound(dp.begin(), dp.end(), a[i]) - dp.begin();
    if (dp[ind - 1] < a[i] && a[i] < dp[ind]) {
      dp[ind] = a[i];
      p[ind] = i;
      par[i] = p[ind - 1];
      ans = max(ans, ind);
    }
  }
  int ind = p[ans];
  vector<int> ansv;
  while (ind != -1 && ind != par[ind]) {
    ansv.push_back(a[ind]);
    ind = par[ind];
  }
  cout << ans << "\n";
  for (int i = int(ansv.size()) - 1; i >= 0; i--) {
    cout << ansv[i] << " ";
  }
  return 0;
}
