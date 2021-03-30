#include <bits/stdc++.h>

using namespace std;

long long const kek = 1000000000000000000;

int main() {
  long long x;
  long long m;
  cin >> x >> m;
  long long z;
  int cnt = 0;
  cout << "? 1" << endl;
  cnt++;
  long long tmp = 0;
  cin >> z;
  x = x - z + 1;
  if (x <= 0) {
    x += kek;
  }
  long long l = max(0ll, x - m - 1), r = min(x + 1ll, kek - m + 1ll);
  while (r - 1 > l && cnt < 10) {
    long long mid = (r + l) / 2;
    cout << "? " << mid << endl;
    cnt++;
    cin >> tmp;
    tmp = tmp - z + 1;
    if (tmp <= 0) {
      tmp += kek;
    }
    if (tmp == x) {
      cout << "! " << mid << endl;
      return 0;
    }
    if (tmp < x) {
      l = mid;
    } else {
      r = mid;
    }
  }
  if (tmp == x) {
    cout << "! " << r << endl;
    return 0;
  }
  cout << "! " << -1 << endl;
  return 0;
}
