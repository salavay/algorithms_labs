#include<bits/stdc++.h>
#define piii pair<int, pair<int, int>>

using namespace std;

typedef long long ll;

const int MAXN = 20010;

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

vector<piii> g;

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < m; i++) {
    int a, b, w;
    cin >> a >> b >> w;
    a--;
    b--;
    g.push_back({w, {a, b}});
  }
  sort(g.begin(), g.end());
  int ans = 2110000000;
  for (int m1 = m - 1; m1 >= 0; m1--) {
    int used = 0;
    int mn = 2e9, mx = -2e9;
    p.resize(n + 1);
    cnt.resize(n + 1);
    for (int i = 0; i < n; i++) {
      p[i] = i;
      cnt[i] = 1;
    }
    for (int i = m1; i < m; i++) {
      int from = g[i].second.first,
          to = g[i].second.second,
          w = g[i].first;
      if (parent(from) != parent(to)) {
        mn = min(w, mn), mx = max(mx, w);
        used++;
        union_d(from, to);
      }
    }
    if (used == n - 1 && cnt[parent(0)] == n) {
      ans = min(mx - mn, ans);
    }
  }
  if (ans == 2110000000) {
    cout << "NO";
  } else {
    cout << "YES\n" << ans;
  }
  return 0;
}
