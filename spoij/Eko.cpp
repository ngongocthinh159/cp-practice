/**
 * Solution for: https://www.spoj.com/problems/EKO/
*/

#include <bits/stdc++.h>
using namespace std;
#define fastio() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)

const int N = 1e6 + 5;
int n, m;
int a[N];
bool check(int h) {
  long long sum = 0;
  for (int i = 0; i < n; i++) {
    sum += (a[i] > h ? a[i] - h : 0);
    if (sum >= m) return true;
  }
  return false;
}
void solve() {
  cin >> n >> m;
  int mx = INT_MIN;
  for (int i = 0; i < n; i++) {
    cin >> a[i]; mx = max(mx, a[i]);
  }
  int l = 0, r = mx, ans = -1;
  while (l <= r) {
    int m = l + (r - l)/2;
    if (check(m)) {
      ans = m;
      l = m + 1;
    } else {
      r = m - 1;
    }
  }
  cout << ans << "\n";
}

int main() {
  fastio();
  solve();
  return 0;
}