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
  p.resize(n + 1);
  cnt.resize(n + 1);
  for (int i = 0; i < n; i++) {
    p[i] = i;
    cnt[i] = 1;
  }
  for (int i = 0; i < m; i++) {
    int a, b, w;
    cin >> a >> b >> w;
    a--;
    b--;
    g.push_back({w, {a, b}});
  }
  int ans = 0;
  sort(g.begin(), g.end());
  for (int i = 0; i < m; i++) {
    int from = g[i].second.first,
        to = g[i].second.second,
        w = g[i].first;
    if (parent(from) != parent(to)) {
      ans += w;
      union_d(from, to);
    }
  }
  cout << ans;
  return 0;
}
