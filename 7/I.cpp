#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct query {
  int l;
  int r;
  int ind;
  ll res;
};

int n, m, k;
vector<int> arr;
vector<ll> ans;
vector<int> tmp;
vector<query> q;
int K;

bool comp(query a, query b) {
  if (a.l / K != b.l / K) {
    return a.l < b.l;
  }
  return a.r < b.r;
}

bool ordered(query a, query b) {
  return a.ind < b.ind;
}

int a = 0, b = 0;

ll getV(ll x) {
  return x * (tmp[static_cast<size_t>(x)] * 2 - 1);
}

void proc() {
  sort(q.begin(), q.end(), comp);
  ll nowRes = 0;
  for (size_t i = 0; i < q.size(); i++) {
    int x;
    while (a > q[i].l) {
      x = arr[a - 1];
      a--;
      tmp[x]++;
      nowRes += getV(x);
    }
    while (b < q[i].r) {
      x = arr[b + 1];
      b++;
      tmp[x]++;
      nowRes += getV(x);
    }
    while (a < q[i].l) {
      x = arr[a];
      a++;
      nowRes -= getV(x);
      tmp[x]--;
    }
    while (b > q[i].r) {
      x = arr[b];
      b--;
      nowRes -= getV(x);
      tmp[x]--;
    }
    q[i].res = nowRes;
  }
  sort(q.begin(), q.end(), ordered);
}

int main() {
#ifdef salavay
  freopen("test.in", "r", stdin);
#else
  ios_base::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
#endif
  cin >> n >> m;
  tmp.resize(1000006, 0);
  ans.resize(m + 10);
  K = static_cast<int>(sqrt(n));
  arr.resize(n + 10);
  for (int i = 0; i < n; i++) {
    cin >> arr[i + 1];
  }
  q.resize(m);
  for (int i = 0; i < m; i++) {
    cin >> q[i].l >> q[i].r;
    q[i].ind = i;
  }
  proc();
  for (int i = 0; i < m; i++) {
    cout << q[i].res << "\n";
  }
  return 0;
}
