#include "bits/stdc++.h"

using namespace std;
typedef long long ll;

int P = 31;
vector<ll> M;

vector<vector<int>> pows;

int getHash(vector<vector<int>> &prefHashs, size_t l, size_t r, size_t m_number) {
  int hash =
      static_cast<int> ((prefHashs[m_number][r + 1] - prefHashs[m_number][l] * 1ll * pows[m_number][r - l + 1])
          % M[m_number]);
  if (hash < 0) {
    return hash + static_cast<int> (M[m_number]);
  }
  return hash;
}

bool equals(vector<vector<int>> &prefHashs1, size_t l1, size_t r1,
            vector<vector<int>> &prefHashs2, size_t l2, size_t r2) {
  for (int mn = 0; mn < 2; mn++) {
    if (getHash(prefHashs1, l1, r1, mn) != getHash(prefHashs2, l2, r2, mn)) {
      return false;
    }
  }
  return true;
}

void calcHashs(string &s, vector<vector<int>> &prefHashs) {
  size_t n = s.length();
  prefHashs.resize(2, vector<int>(n + 1));
  for (size_t mnumber = 0; mnumber <= 1; mnumber++) {
    prefHashs[mnumber][0] = 0;
    for (size_t i = 1; i <= n; i++) {
      prefHashs[mnumber][i] = static_cast<int> ((prefHashs[mnumber][i - 1] * 1ll * P + (s[i - 1] - 'a')) % M[mnumber]);
    }
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
  M.resize(2);
  M[0] = 1e9 + 7;
  M[1] = 1e7 + 37;
  string p, text;
  cin >> p >> text;
  size_t m = p.length(), n = text.length();
  if (m > n) {
    cout << "0";
    return 0;
  }
  pows.resize(2, vector<int>(n + 1));
  for (size_t mnumber = 0; mnumber <= 1; mnumber++) {
    pows[mnumber][0] = 1;
    for (size_t i = 1; i <= n; i++) {
      pows[mnumber][i] = static_cast<int> ((P * 1ll * pows[mnumber][i - 1]) % M[mnumber]);
    }
  }
  vector<vector<int>> prefHashsP, prefHashsText;
  calcHashs(p, prefHashsP);
  calcHashs(text, prefHashsText);
  vector<int> ans;
  for (size_t i = 0; i <= n - m; i++) {
    int l = -1, r = m;
    while (r - l > 1) {
      int mid = (l + r) / 2;
      if (equals(
          prefHashsText, i, i + mid,
          prefHashsP, 0, mid
      )) {
        l = mid;
      } else {
        r = mid;
      }
    }
    l++;
    if (l == static_cast<int> (m) ||
        l == static_cast<int> (m - 1) ||
        equals(
            prefHashsText, i + l + 1, i + m - 1,
            prefHashsP, l + 1, m - 1
        )) {
      ans.push_back(i);
    }
  }
  cout << ans.size() << '\n';
  for (auto c : ans) {
    cout << c + 1 << ' ';
  }
  return 0;
}
