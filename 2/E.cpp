#include<bits/stdc++.h>

using namespace std;

int ind = 0, n, m;

void merge(vector<string> &a, int l, int r) {
  int mdl = (l + r) / 2;
  int inda = l, indb = mdl;
  vector<string> tmp;
  while (inda != mdl || indb != r) {
    if (indb == r) {
      tmp.push_back(a[inda++]);
    } else if (inda == mdl) {
      tmp.push_back(a[indb++]);
    } else if (a[inda][m - ind - 1] <= a[indb][m - ind - 1]) {
      tmp.push_back(a[inda++]);
    } else {
      tmp.push_back(a[indb++]);
    }
  }
  for (int i = l; i < r; i++) {
    a[i] = tmp[i - l];
  }
}

void mergeSort(vector<string> &a, int l, int r) {
  int m = (r + l) / 2;
  if (r - l <= 1) {
    return;
  } else {
    mergeSort(a, l, m);
    mergeSort(a, m, r);
    merge(a, l, r);
  }
}

bool comp(string a, string b) {
  return a[m - ind - 1] < b[m - ind - 1];
}

signed main() {
  int k;
  cin >> n >> m >> k;
  vector<string> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  for (int i = 0; i < k; i++) {
    mergeSort(a, 0, n);
    ind++;
  }
  for (int i = 0; i < n; i++) {
    cout << a[i] << "\n";
  }
  return 0;
}
