#include <bits/stdc++.h>

using namespace std;

vector<pair<int, int>> mnmx;
vector<int> is_d;
vector<pair<int, int>> p;
vector<int> rnk;
int shift = 0;

pair<int, int> parent(int v) {
  if (v != p[v].first) {
    int tmp = p[v].second;
    p[v] = parent(p[v].first);
    p[v].second ^= tmp;
  }
  return p[v];
}

void union_d(int a, int b) {
  pair<int, int> ap = parent(a);
  pair<int, int> bp = parent(b);
  if (ap.first == bp.first) {
    if (ap.second == bp.second)
      is_d[ap.first] = 0;
  } else {
    if (rnk[ap.first] < rnk[bp.first]) {
      swap(ap.first, bp.first);
    }
    p[bp.first] = {ap.first, ap.second ^ bp.second ^ 1};
    is_d[ap.first] &= is_d[bp.first];
    if (rnk[ap.first] == rnk[bp.first]) {
      rnk[ap.first]++;
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int n, m;
  cin >> n >> m;
  is_d.resize(n + 1);
  p.resize(n + 1);
  rnk.resize(n + 1);
  for (int i = 0; i < n; i++) {
    p[i] = {i, 0};
    is_d[i] = 1;
    rnk[i] = 0;
  }
  for (int i = 0; i < m; i++) {
    int t, a, b;
    cin >> t >> a >> b;
    a = (a + shift) % n;
    b = (b + shift) % n;
    if (t == 0) {
      union_d(a, b);
    } else {
      if (parent(a).second == parent(b).second) {
        shift = (shift + 1) % n;
        cout << "YES\n";
      } else {
        cout << "NO\n";
      }
    }
  }
  return 0;
}
