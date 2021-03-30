#include "bits/stdc++.h"

using namespace std;
typedef long long ll;

int P = 31;
vector<ll> M;

vector<vector<int>> pows;
vector<vector<int>> prefHashs;

string s;
size_t n;

int getHash(size_t l, size_t r, size_t m_number) {
  int hash =
      static_cast<int> ((prefHashs[m_number][r + 1] - prefHashs[m_number][l] * 1ll * pows[m_number][r - l + 1])
          % M[m_number]);
  if (hash < 0) {
    return hash + static_cast<int> (M[m_number]);
  }
  return hash;
}

int main() {
#ifdef salavay
  freopen("test", "r", stdin);
#else
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
#endif
  M.resize(2);
  M[0] = 1e9 + 7;
  M[1] = 1e7 + 37;
  cin >> s;
  n = s.length();
  pows.resize(2, vector<int>(n + 1));
  prefHashs.resize(2, vector<int>(n + 1));
  for (size_t mnumber = 0; mnumber <= 1; mnumber++) {
    pows[mnumber][0] = 1;
    prefHashs[mnumber][0] = 0;
    for (size_t i = 1; i <= n; i++) {
      prefHashs[mnumber][i] = static_cast<int> ((prefHashs[mnumber][i - 1] * 1ll * P + (s[i - 1] - 'a')) % M[mnumber]);
      pows[mnumber][i] = static_cast<int> ((P * 1ll * pows[mnumber][i - 1]) % M[mnumber]);
    }
  }

  int k;
  cin >> k;
  for (int i = 0; i < k; i++) {
    size_t a, b, c, d;
    cin >> a >> b >> c >> d;
    a--;
    b--;
    c--;
    d--;
    if (b - a != d - c) {
      cout << "No\n";
      continue;
    }
    if (a == c && b == d) {
      cout << "Yes\n";
      continue;
    }
    bool flag = true;
    for (int mn = 0; mn < 2; mn++) {
      flag = flag && (getHash(a, b, mn) == getHash(c, d, mn));
    }
    cout << (flag ? "Yes\n" : "No\n");
  }
  return 0;
}
