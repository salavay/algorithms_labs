#include <bits/stdc++.h>
// #define int ll

using namespace std;

typedef long long ll;

int M = 999999937;

class mx {
 private:
  vector<vector<int>> arr;
  int n, m;

 public:
  mx(vector<int> arr_v) {
    n = 5;
    m = 1;
    arr.resize(5, vector<int>(5, 1));
    for (int i = 0; i < n; i++) {
      arr[i][0] = arr_v[i];
    }
  }

  mx(int n, int m) : n(n), m(m) {
    arr.resize(n, vector<int>(m));
  }

  mx(int n, int m, bool flag) : n(n), m(m) {
    arr.resize(n, vector<int>(m, 0));
    if (flag) {
      for (int i = 0; i < n; i++) {
        arr[i][i] = 1;
      }
    }
  }
  mx(bool flag) : n(5), m(5) {
    if (flag) {
      arr.resize(5, vector<int>(5, 1));
      for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
          if (i >= 3 && (j == 2 || j == 4)) {
            arr[i][j] = 0;
          }
        }
      }
    }
  }
  int GetN() const {
    return n;
  }

  int GetM() const {
    return m;
  }

  void set_val(int val, int i, int j) {
    arr[i][j] = val;
  }

  mx operator*(mx b) {
    int newN = GetN(), newM = b.GetM();
    mx tmp(newN, newM);
    int btw = GetM();
    for (int i = 0; i < newN; i++) {
      for (int j = 0; j < newM; j++) {
        tmp[i][j] = 0;
        for (int z = 0; z < btw; z++) {
          tmp.set_val((tmp[i][j] +
                          int((arr[i][z] * 1ll * b[z][j]) % M)) % M,
                      i, j);
        }
      }
    }
    return tmp;
  }

  vector<int> operator[](int ind) {
    return arr[ind];
  }

  friend ostream &operator<<(ostream &out, mx a);
};

ostream &operator<<(ostream &out, mx a) {
  int sum = 0;
  for (int i = 0; i < a.GetN(); i++) {
    for (int j = 0; j < a.GetM(); j++) {
      sum = (sum % M + a.arr[i][j] % M) % M;
    }
  }
  out << sum;
  return out;
}

mx bin_pow(mx a, ll n) {
  if (n == 0) {
    return mx(5, 5, true);
  }
  if (n == 1) {
    return a;
  }
  if (n % 2 == 0) {
    mx tmp = bin_pow(a, n / 2);
    return tmp * tmp;
  } else {
    return bin_pow(a, n - 1) * a;
  }
}

signed main() {
  freopen("sequences.in", "r", stdin);
  freopen("sequences.out", "w", stdout);
  mx a(true);
  long long n;
  mx fs(vector<int>{1, 1, 1, 1, 1});
  while (true) {
    cin >> n;
    if (n == 0) break;
    cout << bin_pow(a, n - 1) * fs << '\n';
  }
  return 0;
}
