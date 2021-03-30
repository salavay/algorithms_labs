#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

template<typename T>
class Vec {
 private:
  T *a;
  size_t size;
  size_t last;

 public:
  Vec() {
    size = 1;
    a = new T[size];
    last = 0;
  }
  ~Vec() {
    delete[] a;
  }
  size_t get_size() {
    return last;
  }
  void push_back(T x) {
    if (last == size) {
      T *tmp = new T[size * 2];
      for (size_t i = 0; i < size; i++) {
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
      T *tmp = new T[int(size) / 2];
      for (int i = 0; i < int(size) / 2; i++) {
        tmp[i] = a[i];
      }
      size /= 2;
      delete[] a;
      a = tmp;
    }
    last--;
  }
  T operator[](int ind) {
    return a[ind];
  }
};

template<typename T>
class Stack {
 private:
  Vec<T> arr;

 public:
  Stack() {}
  ~Stack() {}
  T pop() {
    T tmp = arr[int(arr.get_size()) - 1];
    arr.pop_back();
    return tmp;
  }
  T front() {
    return arr[int(arr.get_size()) - 1];
  }
  void push(T x) {
    arr.push_back(x);
  }
  bool empty() {
    return (arr.get_size() == 0);
  }
};

template<typename T>
class Queue {
 private:
  Stack<T> *in;
  Stack<T> *out;
  size_t size;

 public:
  Queue() {
    in = new Stack<T>;
    out = new Stack<T>;
    size = 0;
  }
  void push(int value) {
    in->push(value);
    size++;
  }
  T pop() {
    if (out->empty()) {
      for (int i = 0; i < int(size); i++) {
        out->push(in->pop());
      }
    }
    size--;
    return out->pop();
  }
};

int pll(string s) {
  int sum = 0, k = 1;
  for (int i = int(s.size()) - 1; i >= 0; i--) {
    sum += int(s[i] - '0') * k;
    k *= 10;
  }
  return sum;
}

int main() {
  ios_base::sync_with_stdio(false);
  // cin.tie(0);
  // cout.tie(0);
  Stack<int> nmb;
  Stack<char> sgn;
  string s;
  string k = "";
  getline(cin, s);
  for (int i = 0; i < int(s.size()); i++) {
    if ('0' <= s[i] && s[i] <= '9') {
      k += s[i];
      continue;
    }
    if (s[i] == ' ' && k != "") {
      nmb.push(pll(k));
      k = "";
      continue;
    }
    if (s[i] == ' ') {
      continue;
    }
    int y = nmb.pop(), x = nmb.pop();
    switch (s[i]) {
      case '+':nmb.push(x + y);
        break;
      case '*':nmb.push(x * y);
        break;
      case '-':nmb.push(x - y);
        break;
    }
  }
  cout << nmb.pop();
  return 0;
}
