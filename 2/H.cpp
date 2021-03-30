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

unsigned a, b;

unsigned int cur = 0;
unsigned int nextRand24() {
  cur = cur * a + b;
  return cur >> 8;
}

signed main() {
  unsigned n, m;
  vector<unsigned> v;
  cin >> n >> m;
  cin >> a >> b;
  for (unsigned i = 0; i < n; i++) {
    v.push_back(nextRand24() % m);
  }
  mergeSort(v, 0, n);
  cout << cnt;
  return 0;
}
