#include "bits/stdc++.h"

using namespace std;

int n;

vector<set<int>> g, gr;

const int POWER = 26;

int used[POWER];

vector<int> firstOrd;

int ans[POWER];

set<int> ban;
int Zero = -1;

void dfsZ(int v) {
  used[v] = 1;
  for (auto c : gr[v]) {
    if (!used[c]) {
      dfsZ(c);
    }
  }
  if (gr[v].empty() && ban.find(v) == ban.end()) {
    Zero = v;
    return;
  }
}

void calcZero() {
  for (int i = 0; i < POWER; i++) {
    if (!used[i]) {
      dfsZ(i);
    }
  }
  if (Zero == -1) {
    cout << "No";
    exit(0);
  }
}

pair<int, int> getEdge(string a, string b) {  // a < b
  for (size_t i = 0; i < a.size(); i++) {
    if (a[i] != b[i]) {
      return {a[i] - 'a', b[i] - 'a'};
    }
  }
  cout << "No";
  exit(0);
}

void topSort(int v) {
  used[v] = 1;
  for (int c : g[v]) {
    if (used[c] == 1) {
      cout << "No";
      exit(0);
    }
    if (used[c] == 0) {
      topSort(c);
    }
  }
  used[v] = 2;
  firstOrd.push_back(v);
}

bool cycle(int v) {
  used[v] = 1;
  for (int c : g[v]) {
    if (used[c] == 0) {
      if (cycle(c)) return true;
    } else {
      if (used[c] == 1) {
        return true;
      }
    }
  }
  used[v] = 2;
  return false;
}

int main() {
  cin >> n;
  g.resize(POWER, set<int>());
  gr.resize(POWER, set<int>());
  vector<string> numbers(n);
  for (int i = 0; i < n; i++) {
    string w;
    cin >> w;
    numbers[i] = w;
  }
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      if (numbers[j].size() < numbers[i].size()) {
        cout << "No";
        return 0;
      }
      string w1 = numbers[i], w2 = numbers[j];
      if (w1.size() > 1) ban.insert(w1[0] - 'a');
      if (w2.size() > 1) ban.insert(w2[0] - 'a');
      if (w1.size() != w2.size()) continue;
      pair<int, int> edge = getEdge(w1, w2);
      g[edge.first].insert(edge.second);
      gr[edge.second].insert(edge.first);
    }
  }
  memset(used, 0, POWER * sizeof(int));
  calcZero();
  memset(used, 0, POWER * sizeof(int));
  memset(ans, -1, POWER * sizeof(int));
  ans[Zero] = 0;
  for (int i = 0; i < POWER; i++) {
    if (!used[i]) {
      topSort(i);
    }
  }
  reverse(firstOrd.begin(), firstOrd.end());
  int cntInd = 1;
  for (auto c : firstOrd) {
    if (ans[c] == -1) {
      ans[c] = cntInd;
      cntInd++;
    }
  }
  cout << "Yes\n";
  for (int c : ans) {
    cout << c << " ";
  }
  return 0;
}
