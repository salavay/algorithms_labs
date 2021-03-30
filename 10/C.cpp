#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> g;

vector<int> used;

set<int> A, B;
int m;

void dfs(int v) {
  if (used[v] == 1) return;
  used[v] = 1;
  for (auto c : g[v]) {
    dfs(c);
  }
  if (v < m) {
    A.erase(v);
  } else {
    B.insert(v - m);
  }
}

int main() {
#ifdef salavay
  freopen("test", "r", stdin);
#else
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
#endif
  int n;
  cin >> m >> n;
  g.resize(n + m, vector<int>());
  used.resize(n + m, 0);
  for (int i = 0; i < m; i++) {
    int k, b;
    cin >> k;
    for (int j = 0; j < k; j++) {
      cin >> b;
      b--;
      g[i].push_back(m + b);
    }
  }
  vector<int> lnotmatch;
  for (int i = 0; i < m; i++) {
    int l;
    cin >> l;
    A.insert(i);
    if (l == 0) {
      lnotmatch.push_back(i);
    } else {
      l--;
      g[m + l].push_back(i);
    }
  }
  for (auto v : lnotmatch) {
    dfs(v);
  }
  cout << A.size() + B.size() << '\n';
  cout << A.size() << " ";
  for (auto c : A) {
    cout << c + 1 << " ";
  }
  cout << '\n';
  cout << B.size() << " ";
  for (auto c : B) {
    cout << c + 1 << " ";
  }
  return 0;
}
