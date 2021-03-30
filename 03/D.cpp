#include <bits/stdc++.h>

using namespace std;

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
  p[b] = a;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int n;
  cin >> n;
  p.resize(n + 1);
  for (int i = 0; i < n; i++) {
    p[i] = i;
  }
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    x--;
    int p = parent(x);
    cout << p + 1 << " ";
    union_d((p + 1) % n, x);
  }
  return 0;
}
