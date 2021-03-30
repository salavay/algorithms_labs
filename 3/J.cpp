#include <bits/stdc++.h>

using namespace std;

vector<pair<int, int>> man;
vector<int> msg;
vector<int> cnt;

int p = 1000003;
int zerg = 0;


int parent(int v) {
  if (v == man[v].first) {
    return man[v].first;
  }
  int parent_v = parent(man[v].first);
  man[v].second += man[man[v].first].second;
  if (parent_v == man[v].first)
    man[v].second -= man[parent_v].second;
  man[v].first = parent_v;
  return parent_v;
}

void union_d(int a, int b) {
  a = parent(a);
  b = parent(b);
  if (a != b) {
    zerg = (zerg*13 + 11) % p;
    if (cnt[a] < cnt[b]) swap(a, b);
    cnt[a] += cnt[b];
    man[b].first = a;
    man[b].second -= man[a].second;
  }
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int n, m;
  cin >> n >> m;
  man.resize(n + 1);
  msg.resize(n + 1, 0);
  cnt.resize(n + 1, 1);
  for (int i = 0; i < n; i++) {
    man[i] = {i, 0};
  }
  for (int i = 0; i < m; i++) {
    int t;
    cin >> t;
    if (t == 1) {
      int a;
      cin >> a;
      a = (a + zerg) % n;
      a = parent(a);
      man[a].second++;
      zerg = (30*zerg + 239) % p;
    }
    if (t == 2) {
      int a, b;
      cin >> a >> b;
      a = (a + zerg) % n;
      b = (b + zerg) % n;
      union_d(a, b);
    }
    if (t == 3) {
      int a;
      cin >> a;
      a = (a + zerg) % n;
      int host = parent(a);
      int msgs_now = man[a].second;
      if (a != host) {
        msgs_now += man[host].second;
      }
      msgs_now -= msg[a];
      cout << msgs_now << "\n";
      msg[a] += msgs_now;
      zerg = int((100500ll*zerg + msgs_now)%p);
    }
  }
  return 0;
}


