#include "bits/stdc++.h"

using namespace std;

const int MAXN = 100001;

int used[MAXN];
int dp[MAXN];

int st, ed;

vector<vector<int>> g;
vector<int> firstOrd;
vector<int> p;

bool dfs(int v) {
  used[v] = 1;
  for (int c : g[v]) {
    if (used[c] == 0) {
      p[c] = v;
      if (dfs(c)) return true;
    } else {
      if (used[c] == 1) {
        ed = v;
        st = c;
        return true;
      }
    }
  }
  used[v] = 2;
  return false;
}

int main() {
  int n, m;
  cin >> n >> m;
  g.resize(n, vector<int>());
  p.resize(n, -1);
  for (int i = 0; i < m; i++) {
    int a, b;
    cin >> a >> b;
    a--;
    b--;
    g[a].push_back(b);
  }
  bool isCycle = false;
  for (int i = 0; i < n; i++) {
    if (dfs(i)) {
      isCycle = true;
      break;
    }
  }
  if (!isCycle) {
    cout << "NO";
  } else {
    cout << "YES\n";
    vector<int> ans;
    ans.push_back(st);
    int ind = ed;
    while (ind != st) {
      ans.push_back(ind);
      ind = p[ind];
    }
    reverse(ans.begin(), ans.end());
    for (auto c : ans) {
      cout << c + 1 << ' ';
    }
  }
  return 0;
}
