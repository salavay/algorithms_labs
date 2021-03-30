#include<bits/stdc++.h>

using namespace std;

mt19937 mg(time(0));

int partn(vector<int> &a, int l, int r, int rnd) {
  int v = a[rnd];
  int mid = (r + l) / 2;
  swap(a[l], a[rnd]);
  int i = l + 1;
  int j = r;
  while (i <= j) {
    while (i <= r && (a[i] < v || (a[i] <= v && i < mid))) {
      i++;
    }
    while (j >= l && (a[j] > v || (a[j] >= v && (j > mid)))) {
      j--;
    }
    if (i >= j)
      break;
    swap(a[i++], a[j--]);
  }
  swap(a[l], a[j]);
  return j;
}

int f_kth(vector<int> &a, int k) {
  int l = 0, r = int(a.size()) - 1;
  while (true) {
    int rnd;
    if (r == l)
      rnd = l;
    else
      rnd = mg() % (r - l) + l;
    // int rnd = (r + l) / 3;
    int m = partn(a, l, r, rnd);
    if (m == k) {
      return a[m];
    }
    if (k < m) {
      r = m;
    } else {
      l = m + 1;
    }
  }
}

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int n, k;
  cin >> n >> k;
  vector<int> a(n);
  int x, y, z;
  cin >> x >> y >> z >> a[0] >> a[1];
  for (int i = 2; i < n; i++) {
    a[i] = x * a[i - 2] + y * a[i - 1] + z;
  }
  cout << f_kth(a, k - 1);
  return 0;
}
