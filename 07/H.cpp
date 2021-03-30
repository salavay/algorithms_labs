#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

signed main() {
#ifdef salavay
  freopen("test.in", "r", stdin);
#else
  ios_base::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
#endif
  int n, m;
  cin >> n >> m;
  set<int> park;
  for (int i = 1; i <= n; i++) {
    park.insert(i);
  }
  string command;
  int x;
  for (int i = 0; i < m; i++) {
    cin >> command >> x;
    if (command == "enter") {
      auto lowB = park.lower_bound(x);
      int newPlace = (lowB == park.end()) ? *park.begin() : *lowB;
      cout << newPlace << "\n";
      park.erase(newPlace);
    } else {
      park.insert(x);
    }
  }
  return 0;
}
