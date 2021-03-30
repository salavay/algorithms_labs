#include "bits/stdc++.h"

using namespace std;

const int MAXN = 100001;

int used[MAXN];
int dp[MAXN];

vector<vector<int>> g;
vector<int> firstOrd;

void dfs(int v) {
  used[v] = 1;
  if (g[v].empty()) {
    dp[v] = 1;
  }
  for (int c : g[v]) {
    if (used[c] == 0) {
      dfs(c);
    }
  }
  firstOrd.push_back(v);
}

int main() {
  int n, m;
  int s;
  cin >> n >> m >> s;
  s--;
  g.resize(MAXN, vector<int>());
  for (int i = 0; i < m; i++) {
    int a, b;
    cin >> a >> b;
    a--;
    b--;
    g[a].push_back(b);
  }
  dfs(s);
  for (auto v : firstOrd) {
    dp[v] = 1;
    for (auto c : g[v]) {
      if (dp[v] == 2) break;
      if (dp[c] == 1) {
        dp[v] = 2;
      }
    }
  }
  if (dp[s] == 2) {
    cout << "First player wins";
  } else {
    cout << "Second player wins";
  }
  return 0;
}
