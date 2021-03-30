#include <bits/stdc++.h>

using namespace std;

struct vertex {
  int value;
  int height = 1;
  vertex *left = nullptr;
  vertex *right = nullptr;
  vertex(int value) {
    this->value = value;
  }
};

class AVL_tree {
 private:
  vertex *root;
  int getHeight(vertex *a) {
    if (a != nullptr) {
      return a->height;
    } else {
      return 0;
    }
  }

  int getBalance(vertex *a) {
    return getHeight(a->right) - getHeight(a->left);
  }

  void updateHeight(vertex *a) {
    int leftHeight = getHeight(a->left);
    int rightHeight = getHeight(a->right);
    a->height = max(leftHeight, rightHeight) + 1;
  }

  vertex *rightRotate(vertex *a) {
    if (a == root) {
      root = a->left;
    }
    vertex *tmp = a->left;
    a->left = tmp->right;
    tmp->right = a;
    updateHeight(a);
    updateHeight(tmp);
    return tmp;
  }

  vertex *leftRotate(vertex *a) {
    if (a == root) {
      root = a->right;
    }
    vertex *tmp = a->right;
    a->right = tmp->left;
    tmp->left = a;
    updateHeight(a);
    updateHeight(tmp);
    return tmp;
  }

  vertex *balancing(vertex *a) {
    updateHeight(a);
    if (getBalance(a) == 2) {
      if (getBalance(a->right) < 0) {
        a->right = rightRotate(a->right);
      }
      return leftRotate(a);
    }
    if (getBalance(a) == -2) {
      if (getBalance(a->left) > 0) {
        a->left = leftRotate(a->left);
      }
      return rightRotate(a);
    }
    return a;
  }

  vertex *leftestFind(vertex *a) {
    if (a->left == nullptr) {
      return a;
    } else {
      return leftestFind(a->left);
    }
  }

  vertex *rightestFind(vertex *a) {
    if (a->right == nullptr) {
      return a;
    } else {
      return rightestFind(a->right);
    }
  }

  vertex *deleteTheLeftest(vertex *a) {
    if (a->left == nullptr) {
      return a->right;
    }
    a->left = deleteTheLeftest(a->left);
    return balancing(a);
  }

  vertex *deleteTheRightest(vertex *now) {
    if (now->right == nullptr) {
      return now->left;
    }
    now->right = deleteTheRightest(now->right);
    return balancing(now);
  }

 public:
  AVL_tree() {
    root = nullptr;
  }

  vertex *getRoot() {
    return root;
  }

  vertex *insert(vertex *now, int x) {
    if (exist(now, x)) {
      return nullptr;
    }
    if (now == nullptr) {
      if (now == root) {
        root = new vertex(x);
      }
      return new vertex(x);
    }
    if (x < now->value) {
      now->left = insert(now->left, x);
    } else {
      now->right = insert(now->right, x);
    }
    return balancing(now);
  }

  static bool exist(vertex *now, int x) {
    if (!now) {
      return false;
    }
    if (x < now->value) {
      return exist(now->left, x);
    } else {
      if (x == now->value) {
        return true;
      } else {
        return exist(now->right, x);
      }
    }
  }

  vertex *deleteValue(vertex *a, int x) {
    if (!exist(root, x)) {
      return nullptr;
    }
    if (a == nullptr) {
      return a;
    }
    if (x < a->value) {
      a->left = deleteValue(a->left, x);
    } else if (x > a->value) {
      a->right = deleteValue(a->right, x);
    } else {
      bool flagChangeRoot = (a == root);
      vertex *tmpL = a->left;
      vertex *tmpR = a->right;
      delete a;
      if (tmpL == nullptr) {
        if (tmpR == nullptr && flagChangeRoot) root = nullptr;
        if (flagChangeRoot && tmpR != nullptr) root = tmpR;
        return tmpR;
      }
      vertex *theRightest = rightestFind(tmpL);
      theRightest->left = deleteTheRightest(tmpL);
      theRightest->right = tmpR;
      if (flagChangeRoot) {
        root = balancing(theRightest);
      }
      return balancing(theRightest);
    }
    if (a == root) {
      root = balancing(a);
    }
    return balancing(a);
  }
  vertex *next(int x) {
    vertex *now = root;
    vertex *lastGood = nullptr;
    while (now) {
      if (now->value > x) {
        lastGood = now;
        now = now->left;
      } else {
        now = now->right;
      }
    }
    return lastGood;
  }

  vertex *prev(int x) {
    vertex *now = root;
    vertex *lastGood = nullptr;
    while (now) {
      if (now->value >= x) {
        now = now->left;
      } else {
        lastGood = now;
        now = now->right;
      }
    }
    return lastGood;
  }
};

signed main() {
#ifdef salavay
  freopen("test", "r", stdin);
#endif
  AVL_tree tree;
  string command;
  while (cin >> command) {
    int x;
    cin >> x;
    if (command == "insert") {
      tree.insert(tree.getRoot(), x);
    } else if (command == "delete") {
      tree.deleteValue(tree.getRoot(), x);
    } else if (command == "exists") {
      cout << (AVL_tree::exist(tree.getRoot(), x) ? "true" : "false");
      cout << '\n';
    } else if (command == "next") {
      vertex *next = tree.next(x);
      if (next != nullptr) {
        cout << next->value;
      } else {
        cout << "none";
      }
      cout << '\n';
    } else {
      vertex *prev = tree.prev(x);
      if (prev != nullptr) {
        cout << prev->value;
      } else {
        cout << "none";
      }
      cout << '\n';
    }
  }
  return 0;
}
