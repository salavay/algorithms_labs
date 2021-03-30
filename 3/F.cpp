#include <bits/stdc++.h>

using namespace std;

vector<pair<int, int>> mnmx;
vector<int> cnt;
vector<int> p;

int parent(int v) {
  if (v == p[v]) {
    return p[v];
  }
  return p[v] = parent(p[v]);
}

void union_d(int a, int b) {
  a = parent(a);
  b = parent(b);
  if (a != b)
    cnt[a] += cnt[b];
  p[b] = a;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int n, m, k;
  cin >> n >> m >> k;
  p.resize(n + 1);
  cnt.resize(n + 1);
  for (int i = 0; i < n; i++) {
    p[i] = i;
    cnt[i] = 1;
  }
  for (int i = 0; i < m; i++) {
    int x, y;
    cin >> x >> y;
  }
  vector<pair<string, pair<int, int>>> g(k);
  for (int i = 0; i < k; i++) {
    cin >> g[i].first >> g[i].second.first >> g[i].second.second;
    g[i].second.first--;
    g[i].second.second--;
  }
  vector<string> ans;
  for (int i = k - 1; i >= 0; i--) {
    if (g[i].first == "ask") {
      if (parent(g[i].second.first) == parent(g[i].second.second)) {
        ans.push_back("YES");
      } else {
        ans.push_back("NO");
      }
    } else {
      union_d(g[i].second.first, g[i].second.second);
    }
  }
  reverse(ans.begin(), ans.end());
  for (auto c : ans) {
    cout << c << '\n';
  }
  return 0;
}
