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
  vector<int> prefF(n, 0);
  for (int i = 1; i < n; i++) {
    int j = prefF[i - 1];
    while (j > 0 && p[i] != p[j]) {
      j = prefF[j - 1];
    }
    if (p[i] == p[j]) {
      j++;
    }
    prefF[i] = j;
  }

  size_t cur = prefF[n - 1];
  for (size_t i = prefF[n - 1]; (int) i >= (n + 1) / 2; i = prefF[cur - 1]) {
    if (n % (n - i) == 0) {
      cout << n - i;
      return 0;
    }
  }
  cout << n;
  return 0;
}
