#include <bits/stdc++.h>

using namespace std;

int main() {
  freopen("knapsack.in", "r", stdin);
  freopen("knapsack.out", "w", stdout);
  int n, w;
  cin >> n >> w;
  vector<int> ws(n + 1);
  vector<int> c(n + 1);
  for (int i = 1; i <= n; i++) {
    cin >> ws[i];
  }
  for (int i = 1; i <= n; i++) {
    cin >> c[i];
  }
  vector<vector<int>> dp(n + 1, vector<int>(w + 1, 0));
  vector<vector<pair<int, pair<int, int>>> > ans
      (n + 1, vector<pair<int, pair<int, int>>>(w + 1, {0, {-1, -1}}));
  for (int wi = 0; wi <= w; wi++) {
    dp[0][wi] = 0;
  }
  for (int ni = 1; ni <= n; ni++) {
    for (int wi = 1; wi <= w; wi++) {
      if (wi >= ws[ni] && dp[ni - 1][wi] < dp[ni - 1][wi - ws[ni]] + c[ni]) {
        dp[ni][wi] = dp[ni - 1][wi - ws[ni]] + c[ni];
        ans[ni][wi].first = ni;
        ans[ni][wi].second = {ni - 1, wi - ws[ni]};
      } else {
        dp[ni][wi] = dp[ni - 1][wi];
        ans[ni][wi] = ans[ni - 1][wi];
      }
    }
  }
  vector<int> ansv;
  pair<int, int> indn = {n, w};
  while (ans[indn.first][indn.second].first != 0) {
    ansv.push_back(ans[indn.first][indn.second].first);
    indn = ans[indn.first][indn.second].second;
  }
  cout << ansv.size() << '\n';
  for (int i = int(ansv.size()) - 1; i >= 0; i--) {
    cout << ansv[i] << " ";
  }
  return 0;
}
