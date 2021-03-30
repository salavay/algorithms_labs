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

signed main() {
  int n, m, k;
  cin >> n >> m >> k;
  vector<int> a(n);
  vector<vector<pair<int, int> > > comps(k, vector<pair<int, int> >());
  for (int i = 0; i < k; i++) {
    int j;
    cin >> j;
    for (; j > 0; j--) {
      int x, y;
      cin >> x >> y;
      x--;
      y--;
      comps[i].push_back({min(x, y), max(x, y)});
    }
  }
  int mask = (1 << n);
  int flag = 1;
  for (int i = 0; i < mask; i++) {
    for (int i1 = 0; i1 < n; i1++) {
      a[i1] = 0;
    }
    fill_bits(a, i);
    for (int j = 0; j < k; j++) {
      for (int z = 0; z < int(comps[j].size()); z++) {
        int x = comps[j][z].first, y = comps[j][z].second;
        if (a[x] > a[y]) {
          swap(a[x], a[y]);
        }
      }
    }
    if (!isSorted(a)) {
      flag = false;
    }
  }
  if (flag) {
    cout << "Yes";
  } else {
    cout << "No";
  }
  return 0;
}
