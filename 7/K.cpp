#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> p;
vector<int> height;
int n = 1;

size_t lg(int val) {
  if (val == 0) return 0;
  return ((int) (log(val) / log(2))) + 1;
}

int get_P(int a, size_t d) {
  if (p[a].size() <= d) {
    a = 1;
  } else {
    a = p[a][d];
  }
  return a;
}

int lca(int u, int v) {
  if (height[u] < height[v]) {
    swap(u, v);
  }
  int delta = height[u] - height[v];
  for (int k = lg(n); k >= 0; k--) {
    if (delta >= (1 << k)) {
      u = get_P(u, k);
      delta -= (1 << k);
    }
  }
  if (u == v) {
    return u;
  }
  for (int k = lg(n); k >= 0; k--) {
    int u1 = get_P(u, k);
    int v1 = get_P(v, k);
    if (u1 != v1) {
      u = u1;
      v = v1;
    }
  }
  return get_P(u, 0);
}

int main() {
#ifdef salavay
  freopen("test.in", "r", stdin);
#else
  ios_base::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
#endif
  p.resize(2);
  p[1].resize(3, 1);
  height.resize(2);
  height[1] = 0;
  int q;
  cin >> q;
  string command;
  for (int z = 0; z < q; z++) {
    cin >> command;
    int a, b;
    cin >> a >> b;
    if (command == "ADD") {
      n++;
      p.resize(b + 1);
      p[b].resize(lg(height[a]) + 2);
      height.push_back(height[a] + 1);
      int cur = a;
      for (size_t i = 0; i < p[b].size(); i++) {
        p[b][i] = cur;
        cur = get_P(cur, i);
      }
    } else {
      cout << lca(a, b) << '\n';
    }
  }
  return 0;
}
