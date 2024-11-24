/**
 * Solution for: https://www.spoj.com/problems/OPCPIZZA/
*/

#include <bits/stdc++.h>
using namespace std;
#define fastio() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)

const int N = 1e5 + 5;
int n, m;
int a[N];
void solve() {
  cin >> n >> m;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  if (n == 1) {cout << 0 << "\n"; return;}
  sort(a, a + n);
  int l = 0, r = n - 1, ans = 0;
  while (l < r) {
    int sum = a[l] + a[r];
    if (sum > m) r--;
    else if (sum < m) l++;
    else {
     	l++; r--; ans++;
    }
  }
  cout << ans << "\n";
}

int main() {
  fastio();
  int cases; cin >> cases;
  while (cases--) {
  	solve();  
  }
  return 0;
}