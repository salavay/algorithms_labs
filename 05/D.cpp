#include <bits/stdc++.h>
#include <random>
using namespace std;

mt19937 rng(time(nullptr));

struct node {
  int x;
  int y;
  node *l;
  node *r;
  node *p;
  int cnt{};
  node(int x, int y, node *l, node *r, node *p) :
      x(x), y(y), l(l), r(r), p(p) {}
};

using treap = node *;
using ptt = pair<treap, treap>;

int getCnt(treap t) {
  return t ? t->cnt : 0;
}

treap fix(treap t) {
  if (!t) return t;
  t->cnt = 1 + getCnt(t->l) + getCnt(t->r);
  if (t->r) t->r->p = t;
  if (t->l) t->l->p = t;
  return t;
}

ptt split(treap t, int x) {
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

treap insert(treap t, int x, int y) {
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

treap erase(treap t, int x) {
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

int search_max(treap t, int k) {
  treap c = t;
  int cnt = getCnt(t->r) + 1;
  while (cnt != k) {
    if (cnt > k) {
      c = c->r;
      cnt -= 1 + getCnt(c->l);
    } else {
      c = c->l;
      cnt += getCnt(c->r) + 1;
    }
  }

  return c->x;
}

int main() {
#ifdef salavay
  freopen("test", "r", stdin);
#endif
  int n;
  cin >> n;
  treap t = nullptr;
  vector<int> ans;
  for (int i = 0; i < n; i++) {
    int code;
    int a;
    cin >> code >> a;
    if (code == 1) {
      t = insert(t, a, static_cast<int>(rng()));
    }
    if (code == -1)
      t = erase(t, a);
    if (code == 0)
      ans.push_back(search_max(t, a));
  }
  for (size_t i = 0; i < ans.size(); i++)
    cout << ans[i] << endl;
  return 0;
}
