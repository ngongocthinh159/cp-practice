#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
int n;
int a[N];
int _size;

void heapifyDown(int i) {
  int biggest = i;
  int left = 2*i + 1;
  int right = 2*i + 2;
  if (left < _size && a[left] > a[biggest]) {
    biggest = left;
  }
  if (right < _size && a[right] > a[biggest]) {
    biggest = right;
  }
  if (biggest != i) {
    swap(a[biggest], a[i]);
    heapifyDown(biggest);
  }
}

void push(int val) {
  int i = _size;
  a[i] = val;
  while (i != 0 && a[(i - 1) / 2] < a[i]) {
    swap(a[(i - 1) / 2], a[i]);
    i = (i - 1) / 2;
  }
  _size++;
}

int top() {
  if (_size == 0) return -1;
  return a[0];
}

void pop() {
  if (_size == 0) return;
  a[0] = a[_size - 1];
  _size--;
  heapifyDown(0);
}

void solve() {
  _size = 0;
  cin >> n;
  for (int i = 0; i < n; i++) {
    int val; cin >> val;
    push(val);
    if (_size < 3) cout << "-1" << "\n";
    else {
        int first = top(); pop();
      int second = top(); pop();
      int third = top(); pop();
      push(first); push(second); push(third);
      cout << 1LL * first * second * third << "\n";
    }
  }
}

int main() {
  solve();
  return 0;
}