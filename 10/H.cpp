#include <bits/stdc++.h>

using namespace std;

typedef pair<short, short> pii;

map<pii, short> g;
vector<vector<int>> neighb;

int n, m;
int main() {
#ifdef salavay
  freopen("test", "r", stdin);
#else
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
#endif
  cin >> n >> m;
  neighb.resize(n, vector<int>());
  vector<int> oddV;
  for (int i = 0; i < m; i++) {
    int a, b;
    cin >> a >> b;
    a--;
    b--;
    g[{a, b}]++;
    g[{b, a}]++;
    neighb[a].push_back(b);
    neighb[b].push_back(a);
  }
  for (int i = 0; i < n; i++) {
    if (neighb[i].size() % 2 == 1) {
      oddV.push_back(i);
    }
  }
  map<pii, bool> addG;
  for (size_t i = 0; i < oddV.size(); i += 2) {
    int v = oddV[i], to = oddV[i + 1];
    g[{v, to}]++;
    g[{to, v}]++;
    neighb[v].push_back(to);
    neighb[to].push_back(v);
    addG[{v, to}] = true;
    addG[{to, v}] = true;
  }
  vector<int> ans;
  stack<int> st;
  int startV = oddV.empty() ? 0 : oddV.back();
  st.push(startV);
  while (!st.empty()) {
    int v = st.top();
    if (!neighb[v].empty()) {
      int to = neighb[v].back();
      if (g[{v, to}] == 0) {
        neighb[v].pop_back();
      } else {
        g[{v, to}]--;
        g[{to, v}]--;
        st.push(to);
      }
    }
    if (neighb[v].empty()) {
      ans.push_back(v);
      st.pop();
    }
  }
  reverse(ans.begin(), ans.end());
  if (oddV.empty()) {
    cout << 1;
  } else {
    cout << oddV.size() / 2;
  }
  cout << '\n';
  vector<int> ansP;
  for (size_t i = 0; i < ans.size(); i++) {
    int v = ans[i], to = (i + 1 == ans.size()) ? 0 : ans[i + 1];
    ansP.push_back(v);
    if (addG[{v, to}]) {
      if (ansP.size() >= 2) {
        for (auto c : ansP) {
          cout << c + 1 << " ";
        }
        cout << '\n';
      }
      ansP.clear();
      addG[{v, to}] = false;
      addG[{to, v}] = false;
    }
  }
  if (ansP.size() >= 2) {
    for (auto c : ansP) {
      cout << c + 1 << " ";
    }
    cout << '\n';
  }
  return 0;
}
