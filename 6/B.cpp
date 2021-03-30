#include <bits/stdc++.h>

using namespace std;

template<typename Key, typename Value>
class Hash_Table {
  struct map_element {
    Key key;
    Value value;
    map_element() {
      key = "";
      value = "";
    }
    map_element(Key key, Value value) : key(key), value(value) {}
  };

 private:
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
    arr[hash].push_back({key, value});
  }

  void delete_Key(Key key) {
    int hash = get_Hash(key);
    for (size_t i = 0; i < arr[hash].size(); i++) {
      if (arr[hash][i].key == key) {
        arr[hash][i].key = key;
        arr[hash].erase(arr[hash].begin() + i);
        return;
      }
    }
  }
};

int main() {
#ifdef salavay
  freopen("test", "r", stdin);
#else
  freopen("map.in", "r", stdin);
  freopen("map.out", "w", stdout);
#endif
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
  }
  return 0;
}
