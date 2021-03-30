#include <bits/stdc++.h>

using namespace std;

int main() {
  while (true) {
    int n;
    cin >> n;
    if (n == 0) {
      break;
    }
    int cnt1 = 0, ind1 = n + 100;
    int flag = 1;
    vector<int> a(n);
    vector<pair<int, int>> comps;
    for (int i = 0; i < n; i++) {
      cin >> a[i];
      if (a[i] == 1) {
        cnt1++;
        ind1 = min(ind1, i);
        if (ind1 != i)
          comps.push_back({ind1, i});
      }
      if (i != 0 && a[i - 1] > a[i]) {
        flag = 0;
      }
    }
    for (int i = 0; i < n; i++) {
      if (n - i - 1 == ind1) continue;
      for (int j = 0; j < n - i - 1; j++) {
        if (j == ind1) continue;
        int add = (j + 1 == ind1);
        comps.push_back({j, j + 1 + add});
        j += add;
      }
    }
    ind1 = n - cnt1;
    for (int i = 0; i < n; i++) {
      if (n - i - 1 == ind1) continue;
      for (int j = 0; j < n - i - 1; j++) {
        if (j == ind1) continue;
        int add = (j + 1 == ind1);
        comps.push_back({j, j + 1 + add});
        j += add;
      }
    }
    if (flag) {
      cout << "-1\n";
      continue;
    }
    cout << comps.size() << "\n";
    for (auto i : comps) {
      cout << i.first + 1 << " " << i.second + 1 << '\n';
    }
  }
  return 0;
}
