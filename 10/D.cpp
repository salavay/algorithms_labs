#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> g;
vector<vector<int>> gr;

vector<int> used;
vector<int> p;
set<int> A, B;

int n, m;

bool dfs(int v) {
  if (used[v] == 1) return false;
  used[v] = 1;
  for (int to = 0; to < m; to++) {
    if (gr[v][to] == 1) {
      if (p[to] == -1 || dfs(p[to])) {
        p[to] = v;
        return true;
      }
    }
  }
  return false;
}

void dfsVer(int v) {
  if (used[v] == 1) return;
  used[v] = 1;
  for (auto c : g[v]) {
    dfsVer(c);
  }
  if (v < n) {
    A.insert(v);
  } else {
    B.erase(v);
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
  int k;
  cin >> k;
  for (int i = 0; i < k; i++) {
    cin >> n >> m;
    g.assign(m + n, vector<int>());
    gr.assign(n, vector<int>(m, 1));
    p.assign(m, -1);
    A.clear();
    B.clear();
    for (int j = 0; j < n; j++) {
      int x;
      while (cin >> x && x != 0) {
        x--;
        gr[j][x] = 0;
      }
    }
    for (int v = 0; v < n; v++) {
      used.assign(n, 0);
      dfs(v);
    }
    set<int> lnotmatch;
    for (int a = 0; a < n; a++) {
      lnotmatch.insert(a);
      for (int b = 0; b < m; b++) {
        if (gr[a][b] == 0) continue;
        if (p[b] == a) {
          g[n + b].push_back(a);
        } else {
          g[a].push_back(n + b);
        }
      }
    }
    for (int v = 0; v < m; v++) {
      B.insert(v + n);
      if (p[v] != -1) {
        lnotmatch.erase(p[v]);
      }
    }
    used.assign(n + m, 0);
    for (auto v : lnotmatch) {
      dfsVer(v);
    }
    cout << A.size() + B.size() << '\n';
    cout << A.size() << " " << B.size() << '\n';
    for (auto c : A) {
      cout << c + 1 << " ";
    }
    cout << '\n';
    for (auto c : B) {
      cout << c + 1 - n << " ";
    }
    cout << '\n';
  }
  return 0;
}
