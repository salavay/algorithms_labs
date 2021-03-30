#include "bits/stdc++.h"

using namespace std;

int n, m;

vector<vector<int>> g, gr;

int used[20010], usedr[20010];

vector<int> firstOrd;
int compCnt = 1;

int ans[20010];

void dfs(int v) {
  used[v] = 1;
  for (auto c : g[v]) {
    if (!used[c]) {
      dfs(c);
    }
  }
  firstOrd.push_back(v);
}

void dfsr(int v) {
  usedr[v] = 1;
  ans[v] = compCnt;
  for (auto c : gr[v]) {
    if (!usedr[c]) {
      dfsr(c);
    }
  }
}

int main() {
  cin >> n >> m;
  g.resize(n, vector<int> ());
  gr.resize(n, vector<int> ());
  for (int i = 0; i < m;  i++) {
    int a, b;
    cin >> a >> b;
    a--;
    b--;
    g[a].push_back(b);
    gr[b].push_back(a);
  }
  for (int i = 0; i < n; i++) {
    if (!used[i]) {
      dfs(i);
    }
  }
  reverse(firstOrd.begin(), firstOrd.end());
  for (int i = 0; i < n; i++) {
    int v = firstOrd[i];
    if (!usedr[v]) {
      dfsr(v);
      compCnt++;
    }
  }
  cout << compCnt-1 << '\n';
  for (int i = 0; i < n; i++) {
    cout << ans[i] << " ";
  }
  return 0;
}
