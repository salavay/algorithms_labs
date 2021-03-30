#include<bits/stdc++.h>
// #define int ll

typedef long long ll;

using namespace std;

int const MAX_MEMORY = 30000003;

class Vec {
 private:
  pair<int, int> *a;
  signed size;
  signed last;

 public:
  Vec() {
    size = 1;
    a = new pair<int, int>[size];
    last = 0;
  }
  ~Vec() {
    delete[] a;
  }
  signed get_size() {
    return last;
  }
  void push_back(pair<int, int> x) {
    if (last == size) {
      pair<int, int> *tmp = new pair<int, int>[min(size * 2, 30000003)];
      for (signed i = 0; i < size; i++) {
        tmp[i] = a[i];
      }
      size *= 2;
      delete[] a;
      a = tmp;
    }
    a[last] = x;
    last++;
  }
  void pop_back() {
    if (last == size / 2) {
      pair<int, int> *tmp = new pair<int, int>[int(size) / 2];
      for (int i = 0; i < int(size) / 2; i++) {
        tmp[i] = a[i];
      }
      size /= 2;
      delete[] a;
      a = tmp;
    }
    last--;
  }
  pair<int, int> operator[](int ind) {
    return a[ind];
  }
};

class Stack {
 private:
  Vec arr;
 public:
  Stack() {}
  ~Stack() {}
  pair<int, int> pop() {
    pair<int, int> tmp = arr[int(arr.get_size()) - 1];
    arr.pop_back();
    return tmp;
  }
  pair<int, int> front() {
    return arr[int(arr.get_size()) - 1];
  }
  void push(int x) {
    arr.push_back({x, arr.get_size() == 0 ? x : min(x, arr[arr.get_size() - 1].second)});
  }
  bool empty() {
    return (arr.get_size() == 0);
  }
};

template<typename T>
class Queue {
 private:
  Stack *in;
  Stack *out;
  signed size;

 public:
  Queue() {
    in = new Stack();
    out = new Stack();
    size = 0;
  }
  void push(int value) {
    in->push(value);
    size++;
  }
  T pop() {
    if (out->empty()) {
      for (int i = 0; i < size - 1; i++) {
        out->push(in->pop().first);
      }
    }
    size--;
    return out->pop().first;
  }
  int get_min() {
    if (out->empty()) {
      for (int i = 0; i < int(size) - 1; i++) {
        out->push(in->pop().first);
      }
    }
    return min(in->front().second, out->front().second);
  }
  int get_size() {
    return size - 1;
  }
};

// ll const INFV = LONG_LONG_MAX;
signed MI = INT_MAX;
// ll M = 4294967296;
signed last0, last1;
signed a, b, c;

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  Queue<int> q;
  q.push(MI);
  int n, m, k;
  cin >> n >> m >> k;
  cin >> a >> b >> c;
  ll sum = 0;
  for (int i = 0; i < min(m, k); i++) {
    signed x;
    cin >> x;
    q.push(x);
    last1 = last0;
    last0 = x;
  }
  for (int i = k; i < m; i++) {
    signed z = (a * last1 + b * last0 + c);
    q.push(z);
    last1 = last0;
    last0 = z;
  }
  if (k > m) {
    for (int i = m; i < k; i++) {
      sum += q.get_min();
      signed z;
      cin >> z;
      q.push(z);
      q.pop();
      last1 = last0;
      last0 = z;
    }
    for (int i = k - m; i < n - m + 1; i++) {
      sum += q.get_min();
      signed z = (a * last1 + b * last0 + c);
      q.push(z);
      q.pop();
      last1 = last0;
      last0 = z;
    }
  } else {
    for (int i = 0; i < n - m + 1; i++) {
      sum += q.get_min();
      signed z = (a * last1 + b * last0 + c);
      q.push(z);
      q.pop();
      last1 = last0;
      last0 = z;
    }
  }
  cout << sum;
  return 0;
}
