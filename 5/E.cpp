#include <bits/stdc++.h>
#include <random>
using namespace std;

mt19937 rng(time(NULL));

struct node {
  int in;
  int x;
  int y;
  node *l;
  node *r;
  node *p;
  node(int in, int x, int y, node *l, node *r, node *p) :
      in(in), x(x), y(y), l(l), r(r), p(p) {}
};

typedef node *treap;
typedef pair<treap, treap> ptt;

treap inp[10000000];
vector<treap> ans;
treap fix(treap t) {
  if (!t) return t;
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
  if (a->y < b->y) {
    a->r = merge(a->r, b);
    return fix(a);
  } else {
    b->l = merge(a, b->l);
    return fix(b);
  }
}

treap insert(treap t, int x, int y) {
  t = fix(t);
  if (!t) return fix(new node(0, x, y, nullptr, nullptr, nullptr));
  if (y > t->y) {
    ptt z = split(t, x);
    return fix(new node(0, x, y, z.first, z.second, nullptr));
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
treap build_treap(int l, int r) {
  if (l == r) {
    return inp[l];
  }
  int mid = (l + r) / 2;
  return merge(build_treap(l, mid), build_treap(mid + 1, r));
}

void dfs(treap t) {
  if (!t) return;
  ans.push_back(t);
  dfs(t->l);
  dfs(t->r);
}

int getin(treap t) {
  return t ? t->in : 0;
}

bool cmp2(treap a, treap b) {
  return a->in < b->in;
}

bool cmp1(treap a, treap b) {
  return a->x < b->x;
}
int main() {
#ifdef salavay
  freopen("test", "r", stdin);
#endif
  int n;
  cin >> n;
  treap t = nullptr;
  ans.reserve(10 * n);
  for (int i = 1; i <= n; i++) {
    int a;
    int b;
    cin >> a >> b;
    inp[i] = new node(i, a, b, nullptr, nullptr, nullptr);
  }
  sort(inp + 1, inp + n + 1, cmp1);
  t = build_treap(1, n);
  dfs(t);
  sort(ans.begin(), ans.end(), cmp2);
  cout << "YES" << endl;
  for (size_t i = 0; i < ans.size(); i++) {
    cout << getin(ans[i]->p) << ' ' << getin(ans[i]->l) << ' ' << getin(ans[i]->r) << endl;
  }

  return 0;
}
