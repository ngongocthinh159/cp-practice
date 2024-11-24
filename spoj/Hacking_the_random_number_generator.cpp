/**
 * Solution for: https://www.spoj.com/problems/HACKRNDM/
*/

#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
int n, k;
int a[N];
pair<int,int> find_range(int l, int r, int target) {
  int i1 = lower_bound(a + l, a + r, target) - a;
  if (i1 == n) return {-1, -1};
  int i2 = upper_bound(a + l, a + r, target) - a;
  return {i1, i2 - 1};
}
void solve() {
  cin >> n >> k;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  sort(a, a + n);
  int ans = 0;
  for (int i = 1; i < n; i++) {
    int target1 = a[i] - k;
    int target2 = a[i] + k;
    auto p1 = find_range(0, i, target1);
    auto p2 = find_range(0, i, target2);
    if (p1.first != -1) ans += p1.second - p1.first + 1;
    if (p2.first != -1) ans += p2.second - p2.first + 1;
  }
  cout << ans << "\n";
}

int main() {
  solve();
  return 0;
}