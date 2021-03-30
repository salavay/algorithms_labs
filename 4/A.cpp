#include <bits/stdc++.h>

using namespace std;

int n;
string ans_s = "";
vector<vector<int>> ans;

void get_ans(int i, int j) {
  if (i != j) {
    ans_s += "(";
    get_ans(i, ans[i][j]);
    get_ans(ans[i][j] + 1, j);
    ans_s += ")";
  } else {
    ans_s += "A";
  }
}

int main() {
  freopen("matrix.in", "r", stdin);
  freopen("matrix.out", "w", stdout);
  cin >> n;
  n++;
  ans.resize(n, vector<int>(n));
  vector<int> a(n);
  for (int i = 1; i < n; i++) {
    int x, y;
    cin >> x >> y;
    if (i == 1) {
      a[i - 1] = x;
    }
    a[i] = y;
  }
  vector<vector<int>> dp(n, vector<int>(n));
  for (int i = 0; i < n; i++) {
    dp[i][i] = 0;
    ans[i][i] = 0;
  }
  for (int l = 1; l < n; l++) {
    for (int i = 0; i < n - l; i++) {
      int j = l + i;
      dp[i][j] = 2e9;
      for (int k = i; k < j; k++) {
        int tmp_v = dp[i][k] + dp[k + 1][j] + a[i] * a[k + 1] * a[j + 1];
        if (tmp_v < dp[i][j]) {
          dp[i][j] = tmp_v;
          ans[i][j] = k;
        }
      }
    }
  }
  get_ans(0, n - 2);
  cout << ans_s;
  return 0;
}

/*
 3
 10 100
 100 5
 5 50
 */
