#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int k = 262144 * 2;
const int offset = 2 * 1e5;

ll none = -1e9 - 2;
struct node {
  int data, ind;
  int upd_inc = 0;
};
struct four {
  int first, s, t, flag;
  four() {}
  four(int d, int b, int c, int e) {
    first = d;
    s = b;
    t = c;
    flag = e;
  }
};
struct trio {
  int value, x = offset, y = offset;
};
vector<node> t;
vector<four> req;
trio MAX;

void build() {
  t.resize(2 * k - 1);
  for (int i = 0; i < k; i++) {
    t[k - 1 + i].data = 0;
    t[k - 1 + i].ind = i;
  }
  for (int i = k - 2; i >= 0; i--) {
    t[i].data = 0;
    t[i].ind = t[2 * i + 1].ind;
  }
}

bool comp(four a, four b) {
  return a.first < b.first
      || (a.first == b.first &&
      (a.flag > b.flag ||
      (a.flag == b.flag &&
      (a.s < b.s || (a.s == b.s && a.t < b.t)))));
}

void push(int v, int l, int r) {
  if (r - l == 1) return;
  t[2 * v + 1].upd_inc += t[v].upd_inc;
  t[2 * v + 2].upd_inc += t[v].upd_inc;
  t[2 * v + 1].data += t[v].upd_inc;
  t[2 * v + 2].data += t[v].upd_inc;
  t[v].ind = t[2 * v + 1 + (t[2 * v + 1].data < t[2 * v + 2].data)].ind;
  t[v].upd_inc = 0;
}

void inc(int v, int l, int r, int a, int b, int x) {
  push(v, l, r);
  if (b <= l || a >= r) {
    return;
  }
  if (l >= a && r <= b) {
    t[v].upd_inc += x;
    t[v].data += x;
    return;
  }
  inc(2 * v + 1, l, (l + r) / 2, a, b, x);
  inc(2 * v + 2, (l + r) / 2, r, a, b, x);
  t[v].data = max(t[2 * v + 1].data, t[2 * v + 2].data);
  t[v].ind = t[2 * v + 1 + (t[2 * v + 1].data < t[2 * v + 2].data)].ind;
}

pair<int, int> max(int v, int l, int r, int a, int b) {
  push(v, l, r);
  if (a <= l && r <= b) {
    return make_pair(t[v].data, t[v].ind);
  }
  if (l >= b || r <= a) {
    return make_pair(none, none);
  }
  pair<int, int> ans1 = max(2 * v + 1, l, (l + r) / 2, a, b);
  pair<int, int> ans2 = max(2 * v + 2, (l + r) / 2, r, a, b);
  return ans1.first > ans2.first ? ans1 : ans2;
}

signed main() {
#ifdef salavay
  freopen("test.in", "r", stdin);
#else

#endif
  int n;
  cin >> n;
  req.resize(2 * n);
  int x1, y1, x2, y2;
  for (int i = 0; i < n; i++) {
    cin >> x1 >> y1 >> x2 >> y2;
    x1 += offset;
    y1 += offset;
    x2 += offset;
    y2 += offset;
    req[2 * i] = four(x1, y1, y2 + 1, 1);
    req[2 * i + 1] = four(x2, y1, y2 + 1, -1);
  }
  build();
  sort(req.begin(), req.end(), comp);
  for (auto &i : req) {
    inc(0, 0, k, i.s, i.t, i.flag);
    pair<int, int> cur_max = max(0, 0, k, 0, k);
    if (cur_max.first >= MAX.value) {
      MAX.value = cur_max.first;
      MAX.x = i.first;
      MAX.y = cur_max.second;
    }
  }
  cout << MAX.value << "\n" << MAX.x - offset << " " << MAX.y - offset << endl;
  return 0;
}
