/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://vjudge.net/problem/UVA-10325/origin
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define MAXM 20
ll n, m, a[MAXM];
ll gcd(ll a, ll b) {
  if (b == 0) return a;
  return gcd(b, a%b);
}
ll lcm(ll a, ll b) {
  return a * b / gcd(a, b);
}
void solve() {
  cin >> m;
  for (int i = 0; i < m; i++) cin >> a[i];
  ll ans = n;
  for (int mask = 1; mask < (1 << m); mask++) {
    int len = __builtin_popcountll(mask);
    int sign = len&1 ? -1 : 1;
    ll cur = 1;
    for (int bit = m - 1; bit >= 0; bit--) {
      if ((mask >> bit) & 1) {
        cur = lcm(cur, a[bit]);
      }
    }
    ans += (n/cur) * sign;
  }
  cout << ans << "\n";
}
int main() {
  ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
  while (cin >> n) {
    solve();
  }
  return 0;
}