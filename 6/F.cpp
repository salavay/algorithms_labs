#include <bits/stdc++.h>

using namespace std;

int main() {
  int k;
  cin >> k;
  for (int i = 0; i < k; i++) {
    string s = "cBcBcBcBcBcBcBcBcBcBcB";
    for (int j = 0; j < 11; j++) {
      if (((1 << j) & i) > 0) {
        s[j * 2] = 'b';
        s[j * 2 + 1] = 'a';
      }
    }
    cout << s << '\n';
  }
  return 0;
}
