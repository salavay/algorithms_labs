#include<bits/stdc++.h>

using namespace std;

void merge(vector<pair<double, int>> &a, int l, int r) {
  int mdl = (l + r) / 2;
  int inda = l, indb = mdl;
  vector<pair<double, int>> tmp;
  while (inda != mdl || indb != r) {
    if (indb == r) {
      tmp.push_back(a[inda++]);
    } else if (inda == mdl) {
      tmp.push_back(a[indb++]);
    } else if (a[inda] < a[indb]) {
      tmp.push_back(a[inda++]);
    } else {
      tmp.push_back(a[indb++]);
    }
  }
  for (int i = l; i < r; i++) {
    a[i] = tmp[i - l];
  }
}

void mergeSort(vector<pair<double, int>> &a, int l, int r) {
  int m = (r + l) / 2;
  if (r - l <= 1) {
    return;
  } else {
    mergeSort(a, l, m);
    mergeSort(a, m, r);
    merge(a, l, r);
  }
}

mt19937 mg(time(0));

int partn(vector<pair<double, int>> &a, int l, int r, int rnd) {
  double mdl = a[rnd].first;
  while (l <= r) {
    while (a[l].first < mdl) {
      l++;
    }
    while (a[r].first > mdl) {
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

void QSort(vector<pair<double, int>> &a, int l, int r) {
  if (r - l <= 0) {
    return;
  }
  int rnd = mg() % (r - l) + l;
  int p = partn(a, l, r, rnd);
  QSort(a, l, p);
  QSort(a, p + 1, r);
}

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int n, k;
  cin >> n >> k;
  vector<pair<int, int> > a(n);
  for (int i = 0; i < n; i++) {
    int x, y;
    cin >> x >> y;
    a[i] = {x, y};
  }
  vector<pair<double, int>> p(n);
  double l = 0, r = 1e8;
  while (r - l > 1e-6) {
    double m = (l + r) / 2;
    for (int i = 0; i < n; i++) {
      p[i] = {a[i].first - m * a[i].second, i + 1};
    }
    QSort(p, 0, int(p.size()) - 1);
    double sum = 0;
    for (int i = n - 1; i >= n - k; i--) {
      sum += p[i].first;
    }
    if (sum < 0) {
      r = m;
    } else {
      l = m;
    }
  }
  for (int i = n - 1; i >= n - k; i--) {
    cout << p[i].second << " ";
  }
  return 0;
}
