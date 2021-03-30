#include<bits/stdc++.h>

using namespace std;

void merge(vector<int> &a, int l, int r) {
  int mdl = (l + r) / 2;
  int inda = l, indb = mdl;
  vector<int> tmp;
  while (inda != mdl || indb != r) {
    if (indb == r) {
      tmp.push_back(a[inda++]);
    } else if (inda == mdl) {
      tmp.push_back(a[indb++]);
    } else if (a[inda] <= a[indb]) {
      tmp.push_back(a[inda++]);
    } else {
      tmp.push_back(a[indb++]);
    }
  }
  for (int i = l; i < r; i++) {
    a[i] = tmp[i - l];
  }
}

void mergeSort(vector<int> &a, int l, int r) {
  int m = (r + l) / 2;
  if (r - l <= 1) {
    return;
  } else {
    mergeSort(a, l, m);
    mergeSort(a, m, r);
    merge(a, l, r);
  }
}

/*int binary_l (vector<int> &a, int l, int r, int x) {
  while (r != l) {
    int m = (r + l)/2;
    if (a[m] >= x) {
      r = m;
    } else {
      l = m;
    }
  }
  if (a[r] == x) {
    return r;
  } else {
    return -1;
  }
}*/

int binary_r(vector<int> &a, int l, int r, int x) {
  while (r - l > 1) {
    int m = (r + l) / 2;
    if (a[m] > x) {
      r = m;
    } else {
      l = m;
    }
  }
  return r;
}

signed main() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  int k;
  cin >> k;
  for (int i = 0; i < k; i++) {
    int x;
    cin >> x;
    int l = binary_r(a, -1, n, x - 1),
        r = binary_r(a, -1, n, x);
    if (l != r)
      cout << l + 1 << " " << r << endl;
    else
      cout << "-1 -1\n";
  }
  return 0;
}
