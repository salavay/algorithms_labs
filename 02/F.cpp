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

void fill_bits(vector<int> &a, int mask) {
  int i = int(a.size()) - 1;
  while (mask > 0) {
    if (mask & 1)
      a[i] = mask & 1;
    mask = mask >> 1;
    i--;
  }
}

bool isSorted(vector<int> &a) {
  for (int i = 0; i < int(a.size()) - 1; i++) {
    if (a[i] > a[i + 1]) {
      return false;
    }
  }
  return true;
}

void badQSort(vector<int> &a) {
  for (int i = 0; i < int(a.size()); i++) {
    swap(a[i], a[i / 2]);
  }
}

signed main() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    a[i] = i + 1;
  }
  badQSort(a);
  for (int i = 0; i < n; i++) {
    cout << a[i] << " ";
  }
  return 0;
}
