#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 16777216;

vector<unsigned> vec(N + 10, 0);

unsigned int a, b;
unsigned int cur = 0;
unsigned int nextRand() {
  cur = cur * a + b;
  return cur >> 8;
}

int main() {
#ifdef salavay
  freopen("test.in", "r", stdin);
#else
  ios_base::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
#endif
  int m, q;
  cin >> m >> q;
  cin >> a >> b;
  for (int i = 0; i < m; i++) {
    auto add = nextRand();
    auto l = nextRand();
    auto r = nextRand();
    if (l > r) swap(l, r);
    vec[l] += add;
    vec[r + 1] -= add;
  }
  for (int i = 1; i < N; i++) {
    vec[i] += vec[i - 1];
  }
  for (int i = 1; i < N; i++) {
    vec[i] += vec[i - 1];
  }
  unsigned res = 0;
  for (int i = 0; i < q; i++) {
    auto l = nextRand();
    auto r = nextRand();
    if (l > r) swap(l, r);
    if (l == 0) {
      res += vec[r];
    } else {
      res += vec[r] - vec[l - 1];
    }
  }
  cout << res;
  return 0;
}
