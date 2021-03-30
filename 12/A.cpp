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
  string p, t;
  cin >> p >> t;
  int pSize = p.length();
  char salt = '#';
  p = p + salt + t;
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
  vector<int> ans;
  for (int i = 0; i < n; i++) {
    if (prefF[i] == pSize) {
      ans.push_back(i - 2 * pSize + 1);
    }
  }
  cout << ans.size() << '\n';
  for (auto c : ans) {
    cout << c << " ";
  }
  return 0;
}
