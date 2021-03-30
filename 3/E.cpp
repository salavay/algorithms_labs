#include <bits/stdc++.h>

using namespace std;

vector<int> cnt;
vector<int> p;
vector<int> p_d;

int parent(int v, vector<int> &p1) {
  if (v == p1[v]) {
    return p1[v];
  }
  return p1[v] = parent(p1[v], p1);
}

void union_d(int a, int b, vector<int> &p1) {
  if (a != b) {
    a = parent(a, p1);
    b = parent(b, p1);
    p1[a] = b;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  set<int> s;
  int n, m;
  cin >> n >> m;
  p.resize(n + 1);
  p_d.resize(n + 1);
  for (int i = 0; i < n; i++) {
    p[i] = i;
    p_d[i] = i;
    s.insert(i);
  }
  for (int i = 0; i < m; i++) {
    int t, a, b;
    cin >> t >> a >> b;
    a--;
    b--;
    if (t == 1) {
      if (a != b) {
        union_d(min(a, b), max(a, b), p);
      }
    }
    if (t == 3) {
      if (parent(a, p) == parent(b, p)) {
        cout << "YES\n";
      } else {
        cout << "NO\n";
      }
    }
    if (t == 2) {
      while (a < b) {
        a = parent(a, p_d);
        if (a >= b) break;
        union_d(a, a + 1, p_d);
        union_d(a, a + 1, p);
      }
    }
  }
  return 0;
}
