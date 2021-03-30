#include <bits/stdc++.h>

using namespace std;

char dp[10000 + 5][10000 + 5];
char undtask[10000 + 5];

int main() {
  string p, s;
  getline(cin, p);
  getline(cin, s);
  s = " " + s;
  p = " " + p;
  int n = s.length(), m = p.length();
  if (m == 0) {
    if (n == 0) {
      cout << "YES";
    } else {
      cout << "NO";
    }
    return 0;
  }
  if (n == 0) {
    if (p == "*" || p == "") {
      cout << "YES";
    } else {
      cout << "NO";
    }
    return 0;
  }
  // vector<vector<int>> dp(n + 1, vector<int>(m + 1));
  for (int i = 1; i <= n; i++) {
    dp[i][0] = 0;
  }
  for (int j = 1; j <= m; j++) {
    dp[0][j] = 0;
  }
  dp[0][0] = 1;
  // vector<int> undtask(m, 0);
  undtask[0] = 1;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (p[j - 1] == '?' || p[j - 1] == s[i - 1]) {
        dp[i][j] = dp[i - 1][j - 1];
        undtask[j] = max(undtask[j], dp[i][j]);
      } else if (p[j - 1] == '*') {
        dp[i][j] = max(undtask[j - 1], dp[i][j - 1]);
      }
    }
  }
  if (dp[n][m]) {
    cout << "YES";
  } else {
    cout << "NO";
  }
}

/*
?u*t*n
button
 */
