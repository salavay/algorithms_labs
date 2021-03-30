#include <bits/stdc++.h>
#include <random>
using namespace std;

mt19937 rng(time(NULL));

struct node {
  long long x;
  long long y;
  node *l;
  node *r;
  node *p;
  long long cnt;
  long long sum;
  node(long long x, long long y, node *l, node *r, node *p) :
      x(x), y(y), l(l), r(r), p(p), sum(x) {}
};

typedef node *treap;
typedef pair<treap, treap> ptt;

long long getCnt(treap t) {
  return t ? t->cnt : 0;
}

long long get_Sum(treap t) {
  return t ? t->sum : 0;
}

treap fix(treap t) {
  if (!t) return t;
  t->cnt = 1 + getCnt(t->l) + getCnt(t->r);
  t->sum = t->x + get_Sum(t->l) + get_Sum(t->r);
  if (t->r) t->r->p = t;
  if (t->l) t->l->p = t;
  return t;
}

ptt split(treap t, long long x) {
  t = fix(t);
  if (!t) return {t, t};
  if (t->x < x) {
    ptt z = split(t->r, x);
    t->r = z.first;
    return {fix(t), z.second};
  } else {
    ptt z = split(t->l, x);
    t->l = z.second;
    return {z.first, fix(t)};
  }
}

treap merge(treap a, treap b) {
  a = fix(a);
  b = fix(b);
  if (!a) return b;
  if (!b) return a;
  if (a->y > b->y) {
    a->r = merge(a->r, b);
    return fix(a);
  } else {
    b->l = merge(a, b->l);
    return fix(b);
  }
}

treap insert(treap t, long long x, long long y) {
  t = fix(t);
  if (!t) return fix(new node(x, y, nullptr, nullptr, nullptr));
  if (y > t->y) {
    ptt z = split(t, x);
    return fix(new node(x, y, z.first, z.second, nullptr));
  }
  if (x < t->x)
    t->l = insert(t->l, x, y), t = fix(t);
  else
    t->r = insert(t->r, x, y), t = fix(t);
  return fix(t);
}

treap erase(treap t, long long x) {
  if (!t) return t;
  if (t->x == x) {
    treap l = t->l;
    treap r = t->r;
    delete t;
    return merge(l, r);
  }
  if (t->x < x)
    t->r = erase(t->r, x);
  else
    t->l = erase(t->l, x);
  return fix(t);
}

bool findKey(treap t, long long x) {
  if (!t) return false;
  if (t->x == x)
    return true;
  return findKey(x > t->x ? t->r : t->l, x);
}

treap add(treap t, long long x, long long y) {
  return !findKey(t, x) ? insert(t, x, y) : t;
}

long long getSum(treap t, long long a, long long b) {
  ptt z = split(t, a);
  ptt g = split(z.second, b + 1);
  long long ans = get_Sum(g.first);
  merge(z.first, merge(g.first, g.second));
  return ans;
}

int main() {
#ifdef salavay
  freopen("test", "r", stdin);
#endif
  long long n;
  cin >> n;
  treap t = nullptr;
  vector<long long> ans;
  bool flag = false;
  long long tmp = 0;
  for (long long i = 0; i < n; i++) {
    string s;
    long long a;
    cin >> s >> a;
    if (s == "+") {
      if (flag) a = (a + tmp) % 1000000000, flag = false;
      long long d = rng();
      t = add(t, a, d);
    }
    if (s == "?") {
      flag = true;
      long long b;
      cin >> b;
      tmp = getSum(t, a, b);
      ans.push_back(tmp);
    }
  }
  for (size_t i = 0; i < ans.size(); i++)
    cout << ans[i] << endl;
  return 0;
}
