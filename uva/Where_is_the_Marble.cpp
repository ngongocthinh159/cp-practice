/**
 * Solution: https://vjudge.net/problem/UVA-10474
*/

#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;
int n, q;
int a[N];
void solve() {
  if (!n && !q) return;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  sort(a, a + n);
  for (int i = 0; i < q; i++) {
    int val; cin >> val;
    int index = lower_bound(a, a + n, val) - a;
    if (index == n || a[index] != val) cout << val << " not found\n";
    else cout << val << " found at " << index + 1 << "\n";
  }
}

int main() {
  cin >> n >> q; int i = 1;
  while (n && q) {
    cout << "CASE# " << i++ << ":\n";
    solve();
    cin >> n >> q;
  }
  return 0;
}