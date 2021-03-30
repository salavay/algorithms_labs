#include<bits/stdc++.h>

using namespace std;

long long cnt = 0;

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
      cnt += mdl - inda;
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

int n;
double a, ans = 0;

bool f(double m) {
  double last0 = m, last1 = a;
  for (int i = 2; i < n; i++) {
    double tmp = last0;
    last0 = 2 * last0 - last1 + 2;
    last1 = tmp;
    if (last0 <= 0) {
      return false;
    }
  }
  ans = last0;
  return true;
}

double binary_r(double l, double r) {
  while (r - l > 0.000000001) {
    double m = (r + l) / 2.0;
    if (f(m)) {
      r = m;
    } else {
      l = m;
    }
  }
  return r;
}

signed main() {
  cin >> n >> a;
  binary_r(0.0, 100000000000.0);
  printf("%.2f", ans);
  return 0;
}
