#include<bits/stdc++.h>

using namespace std;

class Vec {
 private:
    int *a;
    size_t size;
    size_t last;

 public:
    Vec() {
        size = 1;
        a = new int[size];
        last = 0;
    }
    ~Vec() {
        delete [] a;
    }
    size_t get_size() {
        return last;
    }
    void push_back(int x) {
        if (last == size) {
            int *tmp = new int[size*2];
            for (size_t i = 0; i < size; i++) {
                tmp[i] = a[i];
            }
            size *= 2;
            delete [] a;
            a = tmp;
        }
        a[last] = x;
        last++;
    }
    void pop_back() {
        if (last == size/2) {
            int *tmp = new int[int(size)/2];
            for (int i = 0; i < int(size)/2; i++) {
                tmp[i] = a[i];
            }
            size /= 2;
            delete [] a;
            a = tmp;
        }
        last--;
    }
    int operator[] (int ind) {
        return a[ind];
    }
};

class Stack{
 private:
    Vec arr;

 public:
    Stack() {}
    ~Stack() {}
    int pop() {
        int tmp = arr[int(arr.get_size()) - 1];
        arr.pop_back();
        return tmp;
    }
    void push(int x) {
        arr.push_back(x);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    Stack a;
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
