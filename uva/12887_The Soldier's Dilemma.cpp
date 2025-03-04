/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=4752
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define MAXN 5005
int n;
ll C[MAXN];
const int MOD = 1e9 + 7;
ll expo(ll a, ll p, ll m) {
  ll res = 1;
  ll cur = a;
  while (p) {
    if (p&1)
      res = res * cur % m;
   	cur = cur * cur % m;
    p >>= 1;
  }
  return res;
}

void pre_compute() {
  C[0] = 1;
  for (int i = 0; i < MAXN - 1; i++)
    C[i + 1] = 1LL * (4*i + 2) * C[i] % MOD * expo(i + 2, MOD - 2, MOD) % MOD;
}
void solve() {
  cin >> n;
  cout << C[n] << "\n";
}
int main() {
  ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
  pre_compute();
  int T; cin >> T;
  while (T--) {
  	solve();  
  }
  return 0;
}
