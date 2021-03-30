#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> g;
vector<int> p;
int highest;
int maxHeight = 0;

vector<int> classOfVertex;
vector<vector<int>> setOfClusters;
vector<vector<int>> listOfSonsClasses;

int used[100007];

void calcClusters(int v, int from) {
  for (int c : g[v]) {
    if (c != from) {
      calcClusters(c, v);
      listOfSonsClasses[v].push_back(classOfVertex[c]);
    }
  }
  sort(listOfSonsClasses[v].begin(), listOfSonsClasses[v].end());
  for (size_t i = 0; i < setOfClusters.size(); i++) {
    if (setOfClusters[i].size() != listOfSonsClasses[v].size()) continue;
    int flag = 1;
    for (size_t j = 0; j < listOfSonsClasses[v].size(); j++) {
      if (setOfClusters[i][j] != listOfSonsClasses[v][j]) {
        flag = 0;
        break;
      }
    }
    if (flag) {
      classOfVertex[v] = i;
      return;
    }
  }
  classOfVertex[v] = setOfClusters.size();
  setOfClusters.push_back(listOfSonsClasses[v]);
}

void dfs(int from, int v, int height) {
  p[v] = from;
  if (g[v].size() == 0 || (g[v][0] == from && g[v].size() == 1)) {
    if (maxHeight < height) {
      highest = v;
      maxHeight = height;
    }
  }
  for (int to : g[v]) {
    if (to != from) {
      dfs(v, to, height + 1);
    }
  }
}

int main() {
#ifdef salavay
  freopen("test", "r", stdin);
#else
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
#endif
  int n;
  cin >> n;
  g.resize(n + 10);
  p.resize(n + 10);
  listOfSonsClasses.resize(n + 10);
  classOfVertex.resize(n + 10);
  for (int i = 0; i < n - 1; i++) {
    int a, b;
    cin >> a >> b;
    g[a].push_back(b);
    g[b].push_back(a);
  }
  dfs(-1, 1, 0);
  int v1 = highest;
  maxHeight = 0;
  dfs(-1, v1, 0);
  if (maxHeight % 2 != 0) {
    cout << "NO";
    exit(0);
  }
  int i = maxHeight;
  while (i != (maxHeight / 2)) {
    highest = p[highest];
    i--;
  }
  if (g[highest].size() != 2) {
    cout << "NO";
    exit(0);
  }
  v1 = g[highest][0];
  int v2 = g[highest][1];
  calcClusters(v1, highest);
  calcClusters(v2, highest);
  classOfVertex[v1] == classOfVertex[v2] ? cout << "YES" : cout << "NO";
  return 0;
}
