#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<int> a;
ll eps = 1e18 + 2, none = -1e18 - 2;
size_t n, k;
struct node {
  ll data = 0;
  ll upd_set = none;
  ll upd_add = 0;
};
vector<node> t;

size_t nextPow(size_t n1) {
  size_t pow = 1;
  while (pow < n1) { pow *= 2; }
  return pow;
}

void build(vector<int> a1) {
  size_t n1 = a1.size();
  k = nextPow(n1);
  t.resize(2 * k - 1);
  for (size_t i = 0; i < n1; i++) {
    t[k - 1 + i].data = a1[i];
  }
  for (size_t i = n1; i < k; i++) {
    t[k - 1 + i].data = eps;
  }
  for (int i = k - 2; i >= 0; i--) {
    t[i].data = min(t[2 * i + 1].data, t[2 * i + 2].data);
  }
}

void push(size_t v, size_t l, size_t r) {
  if (r - l == 1) return;
  if (t[v].upd_set != none) {
    t[2 * v + 1].upd_set = t[v].upd_set;
    t[2 * v + 2].upd_set = t[v].upd_set;
    t[2 * v + 1].data = t[v].upd_set;
    t[2 * v + 2].data = t[v].upd_set;
    t[2 * v + 1].upd_add = 0;
    t[2 * v + 2].upd_add = 0;
    t[v].upd_set = none;
  }
  t[2 * v + 1].upd_add += t[v].upd_add;
  t[2 * v + 2].upd_add += t[v].upd_add;
  t[2 * v + 1].data += t[v].upd_add;
  t[2 * v + 2].data += t[v].upd_add;
  t[v].upd_add = 0;
}

void update(size_t v, int l, int r, int a1, int b, int x) {
  push(v, l, r);
  if (b <= l || a1 >= r) {
    return;
  }
  if (l >= a1 && r <= b) {
    t[v].upd_set = x;
    t[v].upd_add = 0;
    t[v].data = x;
    return;
  }
  update(2 * v + 1, l, (l + r) / 2, a1, b, x);
  update(2 * v + 2, (l + r) / 2, r, a1, b, x);
  t[v].data = min(t[2 * v + 1].data, t[2 * v + 2].data);
}

void add(int v, int l, int r, int a1, int b, int x) {
  push(v, l, r);
  if (b <= l || a1 >= r) {
    return;
  }
  if (l >= a1 && r <= b) {
    t[v].upd_add += x;
    t[v].data += x;
    return;
  }
  add(2 * v + 1, l, (l + r) / 2, a1, b, x);
  add(2 * v + 2, (l + r) / 2, r, a1, b, x);
  t[v].data = min(t[2 * v + 1].data, t[2 * v + 2].data);
}

ll min(size_t v, int l, int r, int a1, int b) {
  push(v, l, r);
  if (a1 <= l && r <= b) {
    return t[v].data;
  }
  if (l >= b || r <= a1) {
    return eps;
  }
  return min(min(2 * v + 1, l, (l + r) / 2, a1, b),
             min(2 * v + 2, (l + r) / 2, r, a1, b));
}

signed main() {
#ifdef salavay
  freopen("test.in", "r", stdin);
#else
  ios_base::sync_with_stdio(false);
  cin.tie(0);
#endif
  cin >> n;
  a.resize(n);
  for (size_t i = 0; i < n; i++) {
    cin >> a[i];
  }
  build(a);
  string op;
  while (cin >> op) {
    int l, r;
    cin >> l >> r;
    if (op == "min") {
      cout << min(0, 0, k, l - 1, r) << "\n";
    } else {
      int x;
      cin >> x;
      if (op == "set") {
        update(0, 0, k, l - 1, r, x);
      } else {
        add(0, 0, k, l - 1, r, x);
      }
    }
  }
  return 0;
}
