#include <bits/stdc++.h>

using namespace std;

int main() {
  int n, m;
  cin >> n >> m;
  if (m <= 16) {
    for (int i = 0; i < m; i++)
      cout << "0 1 1\n";
    return 0;
  }
  int cnt = 0;
  int nk = int(sqrt(m));
  for (int i = 0; i < nk; i++) {
    cnt++;
    cout << "1 " << nk + 1 << " " << i + 1 << " " << '\n';
    if (cnt == m) return 0;
  }
  cout << "1 " << nk + 2 << " " << nk + 1 << " " << '\n';
  cnt++;
  if (cnt == m) return 0;
  for (int i = 0; i < nk; i += 2) {
    cout << 0 << " " << i + 2 << " " << i + 1 << '\n';
    cnt++;
    if (cnt == m) return 0;
  }
  while (cnt < m) {
    nk++;
    cout << 1 << " " << nk + 2 << " " << nk + 1 << '\n';
    cnt++;
    if (cnt == m) return 0;
    for (int i = 0; i < nk; i += 2) {
      cout << 0 << " " << i + 2 << " " << i + 1 << '\n';
      cnt++;
      if (cnt == m) return 0;
    }
  }
  return 0;
}
