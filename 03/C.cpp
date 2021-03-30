#include <bits/stdc++.h>

using namespace std;

int cnt = 0;
int size_h = 0;
int a[1000000];
int cnt_in_tree[100000000];
int what_cnt[100000000];

void siftDown(int v) {
  while (2 * v + 1 < size_h) {
    int ch1 = 2 * v + 1, ch2 = 2 * v + 2;
    int to = ch1;
    if (ch2 < size_h && a[ch2] < a[ch1]) {
      to = ch2;
    }
    if (a[v] <= a[to])
      break;
    swap(a[v], a[to]);
    swap(cnt_in_tree[what_cnt[v]], cnt_in_tree[what_cnt[to]]);
    swap(what_cnt[v], what_cnt[to]);
    v = to;
  }
}

void siftUp(int v) {
  while (a[v] < a[(v - 1) / 2]) {
    swap(a[v], a[(v - 1) / 2]);
    swap(cnt_in_tree[what_cnt[v]], cnt_in_tree[what_cnt[(v - 1) / 2]]);
    swap(what_cnt[v], what_cnt[(v - 1) / 2]);
    v = (v - 1) / 2;
  }
}

int extrMin() {
  int m = a[0];
  cnt_in_tree[what_cnt[0]] = -1;
  if (size_h != 1) {
    what_cnt[0] = what_cnt[size_h - 1];
    cnt_in_tree[what_cnt[size_h - 1]] = 0;
    a[0] = a[size_h - 1];
  }
  size_h--;
  siftDown(0);
  return m;
}

void insert(int val) {
  size_h++;
  a[size_h - 1] = val;
  what_cnt[size_h - 1] = cnt;
  cnt_in_tree[cnt] = size_h - 1;
  siftUp(size_h - 1);
}

int main() {
  string command;
  while (cin >> command) {
    cnt++;
    if (command == "push") {
      int x;
      cin >> x;
      insert(x);
    }
    if (command == "extract-min") {
      int tmp = what_cnt[0];
      if (size_h == 0) {
        cout << "*\n";
      } else {
        cout << extrMin() << " " << tmp << '\n';
      }
    }
    if (command == "decrease-key") {
      int x, v;
      cin >> x >> v;
      if (cnt_in_tree[x] != -1) {
        a[cnt_in_tree[x]] = v;
        siftUp(cnt_in_tree[x]);
      }
    }
  }
  return 0;
}
