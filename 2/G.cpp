#include<bits/stdc++.h>

using namespace std;

unsigned int a[100007], b[100007];
int n, t;
int const z = (1 << 16);
int const DIGIT_SIZE = 65535 + 10;

int cl[DIGIT_SIZE];

void sort_a() {
  int cnt;
  for (int i = 0; i < DIGIT_SIZE; i++) {
    cl[i] = 0;
  }
  for (int i = 0; i < n; i++) {
    int ind = a[i] & ((z) - 1);
    cl[ind]++;
  }
  cnt = 0;
  for (int i = 0; i < DIGIT_SIZE; i++) {
    int tmp = cl[i];
    cl[i] = cnt;
    cnt += tmp;
  }
  for (int i = 0; i < n; i++) {
    int ind = a[i] & ((z) - 1);
    b[cl[ind]] = a[i];
    cl[ind]++;
  }
  // -----------
  for (int i = 0; i < DIGIT_SIZE; i++) {
    cl[i] = 0;
  }
  for (int i = 0; i < n; i++) {
    int ind = b[i] >> 16;
    cl[ind]++;
  }
  cnt = 0;
  for (int i = 0; i < DIGIT_SIZE; i++) {
    int tmp = cl[i];
    cl[i] = cnt;
    cnt += tmp;
  }
  for (int i = 0; i < n; i++) {
    int ind = b[i] >> 16;
    a[cl[ind]] = b[i];
    cl[ind]++;
  }
}
signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  unsigned int a1, b1, at, bt;
  unsigned int cur = 0;
  unsigned long long sum;
  cin >> t >> n;
  cin >> a1 >> b1;
  for (int i = 0; i < t; i++) {
    sum = 0;
    for (int j = 0; j < n; j++) {
      cur = (cur * a1 + b1);
      at = cur >> 8;
      cur = (cur * a1 + b1);
      bt = cur >> 8;
      a[j] = (at << 8) ^ bt;
    }
    sort_a();
    for (int j = 0; j < n; j++) {
      sum += (j + 1) * 1ull * a[j];
    }
    cout << sum << "\n";
  }
  // cout << "runtime = " << clock() / 1000.0 << endl;
  return 0;
}
