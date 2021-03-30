#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int r1, n, m;
struct matrix {
  int a0, a1, a2, a3;
  matrix() {}
  matrix(int a, int b, int c, int d) {
    a0 = a;
    a1 = b;
    a2 = c;
    a3 = d;
  }
};
matrix Eps = matrix(1, 0, 0, 1);
vector<matrix> aV, t;

matrix multiply(matrix a, matrix b) {
  matrix mult;
  mult.a0 = ((a.a1 * b.a2) + (a.a0 * b.a0)) % r1;
  mult.a1 = ((a.a1 * b.a3) + (a.a0 * b.a1)) % r1;
  mult.a2 = ((a.a3 * b.a2) + (a.a2 * b.a0)) % r1;
  mult.a3 = ((a.a3 * b.a3) + (a.a2 * b.a1)) % r1;
  return mult;
}

void build(int i, int l, int r) {
  if (r - l == 1) {
    t[i] = aV[l];
    return;
  }
  build(2 * i + 2, (l + r) / 2, r);
  build(2 * i + 1, l, (l + r) / 2);
  t[i] = multiply(t[2 * i + 1], t[2 * i + 2]);
}

matrix mult(int v, int l, int r, int a, int b) {
  if (a <= l && r <= b) {
    return t[v];
  }
  if (l >= b || r <= a) {
    return Eps;
  }
  return multiply(mult(2 * v + 1, l, (l + r) / 2, a, b),
                  mult(2 * v + 2, (l + r) / 2, r, a, b));
}

void toStr(matrix a) {
  cout << a.a0 << " " << a.a1 << "\n" << a.a2 << " " << a.a3 << "\n\n";
}

signed main() {
#ifdef salavay
  freopen("test.in", "r", stdin);
#else
  ios_base::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
#endif
  cin >> r1 >> n >> m;
  aV.resize(n);
  t.resize(4 * n);
  for (int i = 0; i < n; i++) {
    cin >> aV[i].a0 >> aV[i].a1 >> aV[i].a2 >> aV[i].a3;
  }
  build(0, 0, n);
  int l_ind, r_ind;
  for (int i = 0; i < m; i++) {
    cin >> l_ind >> r_ind;
    toStr(mult(0, 0, n, l_ind - 1, r_ind));
  }
  return 0;
}
