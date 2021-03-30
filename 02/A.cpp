#include<bits/stdc++.h>

using namespace std;

long long cnt = 0;

void merge(vector<unsigned> &a, unsigned l, unsigned r) {
  unsigned mdl = (l + r) / 2;
  unsigned inda = l, indb = mdl;
  vector<unsigned> tmp;
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
  for (unsigned i = l; i < r; i++) {
    a[i] = tmp[i - l];
  }
}

void mergeSort(vector<unsigned> &a, unsigned l, unsigned r) {
  unsigned m = (r + l) / 2;
  if (r - l <= 1) {
    return;
  } else {
    mergeSort(a, l, m);
    mergeSort(a, m, r);
    merge(a, l, r);
  }
}

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

int n;
mt19937 mg(time(0));

int partn(vector<int> &a, int l, int r, int rnd) {
  int mdl = a[rnd];
  while (l <= r) {
    while (a[l] < mdl) {
      l++;
    }
    while (a[r] > mdl) {
      r--;
    }
    if (r <= l) {
      break;
    }
    swap(a[l], a[r]);
    l++;
    r--;
  }
  return r;
}

void QSort(vector<int> &a, int l, int r) {
  if (r - l <= 0) {
    return;
  }
  int rnd = mg() % (r - l) + l;
  int p = partn(a, l, r, rnd);
  QSort(a, l, p);
  QSort(a, p + 1, r);
}

int f_kth(vector<int> &a, int k) {
  int l = 0, r = int(a.size());
  while (true) {
    int rnd = mg() % (r - l) + l;
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
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  QSort(a, 0, int(a.size()) - 1);
  for (int i = 0; i < n; i++) {
    cout << a[i] << " ";
  }
  return 0;
}
