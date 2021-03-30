#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> g;
vector<int> degs;

int n;
int main() {
#ifdef salavay
  freopen("test", "r", stdin);
#else
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
#endif
  int cntDeg = 0;
  cin >> n;
  g.resize(n, vector<int>(n, 0));
  degs.resize(n, 0);
  for (int i = 0; i < n; i++) {
    int k;
    cin >> k;
    cntDeg += k % 2;
    degs[i] += k;
    for (int j = 0; j < k; j++) {
      int a;
      cin >> a;
      a--;
      g[i][a] += 1;
    }
  }
  if (cntDeg != 2 && cntDeg != 0) {
    cout << -1;
    return 0;
  }
  vector<int> ans;
  stack<int> st;
  st.push(0);
  while (!st.empty()) {
    int v = st.top();
    if (degs[v] == 0) {
      ans.push_back(v);
      st.pop();
    } else {
      int to = -1;
      for (int i = 0; i < n; i++) {
        if (g[v][i] > 0) {
          to = i;
          break;
        }
      }
      g[v][to]--;
      g[to][v]--;
      degs[v]--;
      degs[to]--;
      st.push(to);
    }
  }
  cout << ans.size() - 1 << "\n";
  for (auto c : ans) {
    cout << c + 1 << " ";
  }
  return 0;
}
