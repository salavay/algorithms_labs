#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9 + 7;

template<typename T>
struct Node {
  T value = 0;
  Node *next = nullptr;
  Node *prev = nullptr;
  Node() {}
  Node(T val) : value(val) {}
  ~Node() {}
};

template<typename T>
class List {
 private:
  Node<T> *begin;
  Node<T> *last;
  size_t size;

 public:
  List() {
    begin = nullptr;
    last = nullptr;
    size = 0;
  }
  void push_back(T value) {
    if (size++ == 0) {
      begin = new Node(value);
      last = begin;
      return;
    }
    last->next = new Node(value);
    last->next->prev = last;
    last = last->next;
  }
  void push_front(T value) {
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
  Node<T> *front() {
    return begin;
  }
  Node<T> *back() {
    return last;
  }
  void delete_node(Node<T> *node) {
    if (node == begin) {
      this->pop_front();
      return;
    }
    if (node == last) {
      this->pop_back();
      return;
    }
    size--;
    Node<T> *left = node->prev;
    Node<T> *right = node->next;
    if (left)
      left->next = right;
    if (right)
      right->prev = left;
    delete node;
  }
};

template<typename Key, typename Value>
class Hash_Table {
 private:
  vector<List<int>> arr;
  int M1 = 2e9 + 13;
  int M2 = 1e7 + 7;
  long long p = 33;
  size_t capacity = M2;
  static int const MAX_LEN = 20;
  long long p_pow[MAX_LEN];

  int get_Hash(Key key) {
    int ans = abs(key % M1) % M2;
    return ans;
  }

 public:
  Hash_Table() {
    arr.resize(capacity, List<Key>());
  }
  Value get(Key key) {
    int hash = get_Hash(key);
    Node<Key> *c = arr[hash].front();
    while (c) {
      if (c->value == key) {
        return c->value;
      }
      c = c->next;
    }
    return INF;
  }

  void put(Key key) {
    int hash = get_Hash(key);
    Node<Key> *c = arr[hash].front();
    while (c) {
      if (c->value == key) {
        c->value = key;
        return;
      }
      c = c->next;
    }
    arr[hash].push_back(key);
  }

  void delete_Key(Key key) {
    int hash = get_Hash(key);
    Node<Key> *c = arr[hash].front();
    while (c) {
      if (c->value == key) {
        arr[hash].delete_node(c);
        return;
      }
      c = c->next;
    }
  }
};

int main() {
#ifdef salavay
  freopen("test", "r", stdin);
#else
  freopen("set.in", "r", stdin);
  freopen("set.out", "w", stdout);
#endif
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  Hash_Table<int, int> table;
  string command;
  while (cin >> command) {
    if (command == "insert") {
      int key;
      cin >> key;
      table.put(key);
    }
    if (command == "exists") {
      int key;
      cin >> key;
      int value = table.get(key);
      if (value != INF)
        cout << "true" << '\n';
      else
        cout << "false\n";
    }
    if (command == "delete") {
      int key;
      cin >> key;
      table.delete_Key(key);
    }
  }
  return 0;
}
