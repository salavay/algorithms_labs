#include "bits/stdc++.h"

using namespace std;

void make_pref_func(vector<size_t> &pref_f, string &p) {
  int n = p.length();
  pref_f.resize(n, 0);
  for (int i = 1; i < n; i++) {
    int j = pref_f[i - 1];
    while (j > 0 && p[i] != p[j]) {
      j = pref_f[j - 1];
    }
    if (p[i] == p[j]) {
      j++;
    }
    pref_f[i] = j;
  }
}

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
  size_t n = p.length();
  size_t sum = 0;
  string cur_string;
  for (size_t i = 0; i < n; i++) {
    cur_string += p[i];
    reverse(cur_string.begin(), cur_string.end());
    vector<size_t> pref_F;
    make_pref_func(pref_F, cur_string);
    reverse(cur_string.begin(), cur_string.end());
    size_t mx = 0;
    for (auto c : pref_F) {
      mx = max(c, mx);
    }
    sum += (cur_string.length() - mx);
    cout << sum << "\n";
  }
  return 0;
}
