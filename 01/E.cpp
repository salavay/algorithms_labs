#include<bits/stdc++.h>

using namespace std;

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

int main() {
  ios_base::sync_with_stdio(false);
  // cin.tie(0);
  // cout.tie(0);
  bool flag = true;
  string s;
  while (getline(cin, s)) {
    Stack<char> a;
    flag = true;
    for (char x : s) {
      if (x == '(' || x == '[') {
        a.push(x);
      } else {
        if (a.empty() || (x == ')' && a.front() != '(') || (x == ']' && a.front() != '[')) {
          flag = false;
          break;
        }
        if ((x == ')' && a.front() == '(') || (x == ']' && a.front() == '[')) {
          a.pop();
        }
      }
    }
    if (flag && a.empty()) {
      cout << "YES\n";
    } else {
      cout << "NO\n";
    }
  }
  return 0;
}
