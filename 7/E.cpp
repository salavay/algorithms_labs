#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll INF = 0;
vector<ll> tree;
vector<ll> a;

void build(int v, int l, int r) {
  if (r - l == 1) {
    tree[v] = a[l];
    return;
  }
  int m = (l + r) / 2;
  build(v * 2, l, m);
  build(v * 2 + 1, m, r);
  tree[v] = tree[v * 2] + tree[v * 2 + 1];
}

ll get(int v, int l, int r, int ql, int qr) {
  if (l >= qr || r <= ql) {
    return INF;
  }
  if (l >= ql && r <= qr) {
    return tree[v];
  }
  int m = (l + r) / 2;
  return get(2 * v, l, m, ql, qr) + get(2 * v + 1, m, r, ql, qr);
}

void update(int v, int coord, int value, int l, int r) {
  if (coord == l && r - l == 1) {
    tree[v] = value;
    return;
  }
  int m = (l + r) / 2;
  if (coord < m) {
    update(2 * v, coord, value, l, m);
  } else {
    update(2 * v + 1, coord, value, m, r);
  }
  tree[v] = tree[2 * v] + tree[2 * v + 1];
}

int main() {
#ifdef salavay
  freopen("test.in", "r", stdin);
#else
  ios_base::sync_with_stdio(false);
  cin.tie(0);
#endif
  int n;
  cin >> n;
  a.resize(n, 0);
  tree.resize(4 * n, INF);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  build(1, 0, n);
  string com;
  while (cin >> com) {
    int l, r;
    cin >> l >> r;
    if (com == "sum") {
      cout << get(1, 0, n, l - 1, r) << endl;
    } else {
      update(1, l - 1, r, 0, n);
    }
  }
  return 0;
}
