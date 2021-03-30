#include "bits/stdc++.h"

using namespace std;

int main() {
#ifdef salavay
  freopen("test", "r", stdin);
#else
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
#endif
  string p;
  cin >> p;
  int n = p.length();
  vector<int> zFunc(n, 0);
  int l = 0, r = 0;
  for (int i = 1; i < n; i++) {
    if (i <= r) {
      zFunc[i] = min(r - i + 1, zFunc[i - l]);
    }
    while (i + zFunc[i] < n && p[zFunc[i]] == p[i + zFunc[i]]) {
      zFunc[i]++;
    }
    if (i + zFunc[i] - 1 > r) {
      l = i;
      r = i + zFunc[i] - 1;
    }
  }
  for (size_t i = 1; i < zFunc.size(); i++) {
    cout << zFunc[i] << " ";
  }
  return 0;
}
