#include<bits/stdc++.h>

using namespace std;

struct rmq {
  int l;
  int r;
  int val;
  bool operator<(rmq a) {
    return ((val < a.val) ||
        ((val == a.val && (l < a.l || (l == a.l && r < a.r)))));
  }
};

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
  p[a] = b;
}

int main() {
  int n, m;
  cin >> n >> m;
  p.resize(n + 2);
  for (int i = 0; i <= n; i++) {
    p[i] = i;
  }
  vector<rmq> a(m);
  for (int i = 0; i < m; i++) {
    cin >> a[i].l >> a[i].r >> a[i].val;
  }
  sort(a.rbegin(), a.rend());
  vector<int> arr(n);
  for (auto c : a) {
    int val = c.val,
        l = c.l - 1, r = c.r;
    while (l < r) {
      l = parent(l);
      if (l >= r || l >= n) break;
      arr[l] = val;
      union_d(l, l + 1);
    }
  }
  for (auto c : arr) cout << c << " ";
  return 0;
}
