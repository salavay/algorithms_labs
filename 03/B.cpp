#include <bits/stdc++.h>

using namespace std;

vector<pair<int, int>> mnmx;
vector<int> cnt;
vector<int> p;

int parent(int v) {
  if (v == p[v]) {
    return p[v];
  }
  return p[v] = parent(p[v]);
}

void union_d(int a, int b) {
  a = parent(a);
  b = parent(b);
  if (a != b)
    cnt[a] += cnt[b];
  mnmx[a] = {min(mnmx[a].first, mnmx[b].first), max(mnmx[a].second, mnmx[b].second)};
  p[b] = a;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int n;
  cin >> n;
  p.resize(n + 1);
  cnt.resize(n + 1);
  mnmx.resize(n + 1);
  for (int i = 0; i < n; i++) {
    mnmx[i].first = mnmx[i].second = i + 1;
    p[i] = i;
    cnt[i] = 1;
  }
  string command;
  while (cin >> command) {
    if (command == "union") {
      int x, y;
      cin >> x >> y;
      x--;
      y--;
      union_d(x, y);
    } else {
      int x;
      cin >> x;
      x--;
      x = parent(x);
      cout << mnmx[x].first << " "
           << mnmx[x].second << " " << cnt[x] << '\n';
    }
  }
  return 0;
}
