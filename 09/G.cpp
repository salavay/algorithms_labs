#include<bits/stdc++.h>
#define piii pair<int, pair<int, int>>

using namespace std;

typedef long long ll;

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
  int n;
  cin >> n;
  p.resize(n + 1);
  cnt.resize(n + 1);
  for (int i = 0; i < n; i++) {
    p[i] = i;
    cnt[i] = 1;
  }
  vector<pair<int, int>> dots;
  for (int i = 0; i < n; i++) {
    int x, y;
    cin >> x >> y;
    dots.emplace_back(x, y);
  }
  for (int a = 0; a < n; a++) {
    for (int b = a + 1; b < n; b++) {
      int x1 = dots[a].first,
          x2 = dots[b].first,
          y1 = dots[a].second,
          y2 = dots[b].second;
      int w = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
      g.push_back({w, {a, b}});
    }
  }
  double ans = 0.0;
  sort(g.begin(), g.end());
  for (auto &i : g) {
    int from = i.second.first,
        to = i.second.second,
        w = i.first;
    if (parent(from) != parent(to)) {
      ans += sqrt((double) w);
      union_d(from, to);
    }
  }
  cout << fixed << setprecision(20) << ans;
  return 0;
}
