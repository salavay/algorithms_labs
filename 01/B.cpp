#include<bits/stdc++.h>

using namespace std;

class List {
 private:
  struct Node {
    int value = 0;
    Node *next = nullptr;
    Node *prev = nullptr;
    Node() {}
    Node(int val) : value(val) {}
    ~Node() {}
  };
  Node *begin;
  Node *last;
  size_t size;

 public:
  List() {
    size = 0;
  }
  void push_back(int value) {
    if (size++ == 0) {
      begin = new Node(value);
      last = begin;
      return;
    }
    last->next = new Node(value);
    last->next->prev = last;
    last = last->next;
  }
  void push_front(int value) {
    if (size++ == 0) {
      begin = new Node(value);
      last = begin;
      return;
    }
    begin->prev = new Node(value);
    begin->prev->next = begin;
    begin = begin->prev;
  }
  void pop_back() {
    size--;
    if (last->prev) {
      last = last->prev;
      delete last->next;
      last->next = nullptr;
    } else {
      delete last;
      last = nullptr;
      begin = nullptr;
    }
  }
  void pop_front() {
    size--;
    if (begin->next) {
      begin = begin->next;
      delete begin->prev;
      begin->prev = nullptr;
    } else {
      delete begin;
      begin = nullptr;
      last = nullptr;
      return;
    }
  }
  int front() {
    return begin->value;
  }
  int back() {
    return last->value;
  }
  int operator[](int ind) {
    int cnt = 0;
    Node *tmp = begin;
    while (cnt != ind) {
      tmp = tmp->next;
      cnt++;
    }
    return tmp->value;
  }
};

class Queue {
 private:
  List *data;

 public:
  Queue() {
    data = new List;
  }
  void push(int value) {
    data->push_back(value);
  }
  int pop() {
    int tmp = data->back();
    data->pop_back();
    return tmp;
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  Queue a;
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    char x;
    cin >> x;
    if (x == '-') {
      cout << a.pop() << "\n";
    } else {
      int value;
      cin >> value;
      a.push(value);
    }
  }
  return 0;
}
