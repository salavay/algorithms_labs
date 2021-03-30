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

int n, m, k;

bool checking_web(vector<vector<pair<int, int> > > comps) {
  int mask = (1 << n);
  int flag = 1;
  vector<int> a(n);
  for (int i = 0; i < mask; i++) {
    for (int i1 = 0; i1 < n; i1++) {
      a[i1] = 0;
    }
    fill_bits(a, i);
    for (int j = 0; j < int(comps.size()); j++) {
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
    return true;
  } else {
    return false;
  }
}

signed main() {
  vector<vector<pair<int, int> > > comps(10, vector<pair<int, int> >());
  int i = 0;
  m = 60;
  k = 10;
  for (int j = 0; j < 8; j++) {
    comps[i].push_back({j * 2, j * 2 + 1});
  }
  i = 1;
  for (int j = 0; j < 4; j++) {
    comps[i].push_back({j * 4, j * 4 + 2});
    comps[i].push_back({j * 4 + 1, j * 4 + 1 + 2});
  }
  i = 2;
  for (int j = 0; j < 4; j++) {
    comps[i].push_back({j, j + 4});
    comps[i].push_back({j + 8, j + 8 + 4});
  }
  i = 3;
  for (int j = 0; j < 8; j++) {
    comps[i].push_back({j, j + 8});
  }
  i = 4;
  comps[i].push_back({5, 10});
  comps[i].push_back({6, 9});
  comps[i].push_back({3, 12});
  comps[i].push_back({7, 11});
  comps[i].push_back({13, 14});
  comps[i].push_back({1, 2});
  comps[i].push_back({4, 8});
  i = 5;
  comps[i].push_back({1, 4});
  comps[i].push_back({7, 13});
  comps[i].push_back({2, 8});
  comps[i].push_back({11, 14});
  i = 6;
  comps[i].push_back({2, 4});
  comps[i].push_back({5, 6});
  comps[i].push_back({9, 10});
  comps[i].push_back({11, 13});
  comps[i].push_back({3, 8});
  comps[i].push_back({7, 12});
  i = 7;
  comps[i].push_back({6, 8});
  comps[i].push_back({3, 5});
  comps[i].push_back({7, 9});
  comps[i].push_back({10, 12});
  i = 8;
  comps[i].push_back({3, 4});
  comps[i].push_back({5, 6});
  comps[i].push_back({7, 8});
  comps[i].push_back({9, 10});
  comps[i].push_back({11, 12});
  i = 9;
  comps[i].push_back({8, 9});
  comps[i].push_back({6, 7});
  int n1;
  cin >> n1;
  n = n1;
  for (int j = 0; j < int(comps.size()); j++) {
    for (int z = 0; z < int(comps[j].size()); z++) {
      if (comps[j][z].second >= n1) {
        comps[j].erase(comps[j].begin() + z);
        z--;
        m--;
      }
    }
    if (int(comps[j].size()) == 0) k--;
  }
  cout << n1 << " " << m << " " << k << "\n";
  for (int j = 0; j < int(comps.size()); j++) {
    if (int(comps[j].size()) == 0) continue;
    cout << comps[j].size() << " ";
    for (int z = 0; z < int(comps[j].size()); z++) {
      cout << comps[j][z].first + 1 << " " << comps[j][z].second + 1 << " ";
    }
    cout << '\n';
  }
  return 0;
}
