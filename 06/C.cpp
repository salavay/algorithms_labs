#include <bits/stdc++.h>

using namespace std;

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
  struct map_element {
    Key key;
    Value value;
    Node<Key> *node;
    map_element() {
      key = "";
      value = "";
    }
    map_element(Key key, Value value) : key(key), value(value) {}
    map_element(Key key, Value value, Node<Key> *node) : key(key), value(value), node(node) {}
  };

 private:
  List<Key> list;
  size_t M1 = 1e7 + 7;
  long long p = 31;
  size_t capacity = M1;
  static int const MAX_LEN = 20;
  long long p_pow[MAX_LEN];
  vector<vector<map_element>> arr;
  int get_Hash(Key key) {
    long long sum = key[0];
    for (size_t i = 1; i < key.length(); i++) {
      sum = (sum + (p_pow[i] * 1ll * key[i]) % M1) % M1;
    }
    return abs(static_cast<int>(sum % M1));
  }

 public:
  Hash_Table() {
    p_pow[0] = 1;
    for (int i = 1; i < MAX_LEN; i++) {
      p_pow[i] = p_pow[i - 1] * p;
    }
    arr.resize(capacity, vector<map_element>());
  }

  Value get(Key key) {
    int hash = get_Hash(key);
    for (map_element c : arr[hash]) {
      if (c.key == key) {
        return c.value;
      }
    }
    return "none";
  }

  void put(Key key, Value value) {
    int hash = get_Hash(key);
    for (size_t i = 0; i < arr[hash].size(); i++) {
      if (arr[hash][i].key == key) {
        arr[hash][i].value = value;
        return;
      }
    }
    list.push_back(key);
    arr[hash].push_back({key, value, list.back()});
  }

  void delete_Key(Key key) {
    int hash = get_Hash(key);
    for (size_t i = 0; i < arr[hash].size(); i++) {
      if (arr[hash][i].key == key) {
        list.delete_node(arr[hash][i].node);
        arr[hash].erase(arr[hash].begin() + i);
        return;
      }
    }
  }
  string prev(Key key) {
    if (this->get(key) == "none") return "none";
    int hash = get_Hash(key);
    for (map_element c : arr[hash]) {
      Node<Key> *ans = c.node->prev;
      if (ans) {
        return this->get(ans->value);
      } else {
        return "none";
      }
    }
    return "none";
  }

  string next(Key key) {
    if (this->get(key) == "none") return "none";
    int hash = get_Hash(key);
    for (map_element c : arr[hash]) {
      Node<Key> *ans = c.node->next;
      if (ans) {
        return this->get(ans->value);
      } else {
        return "none";
      }
    }
    return "none";
  }
};

int main() {
#ifdef salavay
  freopen("test", "r", stdin);
#else
  freopen("linkedmap.in", "r", stdin);
  freopen("linkedmap.out", "w", stdout);
#endif
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  Hash_Table<string, string> table;
  string command;
  while (cin >> command) {
    if (command == "put") {
      string key, value;
      cin >> key >> value;
      table.put(key, value);
    }
    if (command == "get") {
      string key;
      cin >> key;
      string value = table.get(key);
      cout << value << '\n';
    }
    if (command == "delete") {
      string key;
      cin >> key;
      table.delete_Key(key);
    }
    if (command == "prev") {
      string key;
      cin >> key;
      cout << table.prev(key) << '\n';
    }
    if (command == "next") {
      string key;
      cin >> key;
      cout << table.next(key) << '\n';
    }
  }
  return 0;
}
