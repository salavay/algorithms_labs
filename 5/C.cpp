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
  node(int x, int y, node *l, node *r, node *p) :
      x(x), y(y), l(l), r(r), p(p) {}
};

using treap = node *;
using ptt = pair<treap, treap>;

int Y(node *a) {
  if (a == nullptr) return 0;
  else return a->y;
}

treap fix(treap t) {
  if (!t) return t;
  t->y = 1 + Y(t->l) + Y(t->r);
  return t;
}

ptt split(treap t, int x) {
  if (!t) return {t, t};
  if (Y(t->l) >= x) {
    ptt z = split(t->l, x);
    t->l = z.second;
    return {z.first, fix(t)};
  } else {
    ptt z = split(t->r, x - Y(t->l) - 1);
    t->r = z.first;
    return {fix(t), z.second};
  }
}

treap merge(treap a, treap b) {
  if (!a) return b;
  if (!b) return a;
  if ((static_cast<int>(rng()) % (Y(a) + Y(b))) >= Y(a)) {
    b->l = merge(a, b->l);
    return fix(b);
  } else {
    a->r = merge(a->r, b);
    return fix(a);
  }
}

treap insert(treap t, int x, int y) {
  if (!t) return fix(new node(x, y, nullptr, nullptr, nullptr));
  if (y > Y(t)) {
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

void out(treap tree) {
  if (tree != nullptr) {
    out(tree->l);
    cout << tree->x << " ";
    out(tree->r);
  }
}

int main() {
#ifdef salavay
  freopen("test", "r", stdin);
#endif
  treap tree = nullptr;
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; i++) {
    tree = merge(tree, new node(i + 1, 1, nullptr, nullptr, nullptr));
  }
  for (int i = 0; i < m; i++) {
    int l, r;
    cin >> l >> r;
    ptt OLE = split(tree, l - 1);
    treap OL = OLE.first;
    treap LE = OLE.second;
    ptt LRE = split(LE, r - l + 1);
    treap LR = LRE.first;
    treap RE = LRE.second;
    tree = merge(LR, merge(OL, RE));
  }
  out(tree);
  return 0;
}
