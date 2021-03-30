#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int st[200107][20];
vector<int> a;
int u[2], v[2], r[2];

int request(int u1, int v1) {
  if (u1 > v1)
    swap(u1, v1);
  int len = (int) (log2(v1 - u1 + 1));
  return min(st[u1][len], st[v1 - (1 << len) + 1][len]);
}

signed main() {
#ifdef salavay
  freopen("test.in", "r", stdin);
#else

#endif
  int n, m;
  cin >> n >> m;
  a.resize(n + 1);
  cin >> a[0] >> u[0] >> v[0];
  for (int i = 1; i < n; i++) {
    a[i] = (23 * a[i - 1] + 21563) % 16714589;
  }
  for (int len = 0; len <= log2(n); len++) {
    for (int l = 0; l < n - len; l++) {
      st[l][len] = (len > 0) ? min(st[l][len - 1], st[l + (1 << (len - 1))][len - 1]) : a[l];
    }
  }
  for (int i = 1; i < m; i++) {
    r[(i - 1) % 2] = request(u[(i - 1) % 2] - 1, v[(i - 1) % 2] - 1);
    u[i % 2] = (17 * u[(i - 1) % 2] + 751 + r[(i - 1) % 2] + 2 * (i)) % n + 1;
    v[i % 2] = (13 * v[(i - 1) % 2] + 593 + r[(i - 1) % 2] + 5 * (i)) % n + 1;
  }
  cout << u[(m - 1) % 2] << " " <<
  v[(m - 1) % 2] << " " <<
  request(u[(m - 1) % 2] - 1, v[(m - 1) % 2] - 1);

  return 0;
}
