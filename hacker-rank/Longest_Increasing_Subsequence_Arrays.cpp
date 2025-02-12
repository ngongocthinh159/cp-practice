/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://www.hackerrank.com/contests/world-codesprint-5/challenges/longest-increasing-subsequence-arrays/problem
*/

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

#define ll long long
#define MOD 1000000007
#define MAXM 500005
ll m, n;
ll n_1_pow[MAXM], n_pow[MAXM], fact[MAXM], ifact[MAXM];
ll expo(ll a, ll b, ll mod) {if (a==0) return 1%mod; ll res = 1; while (b > 0) {if (b & 1)res = (res * a) % mod; a = (a * a) % mod; b = b >> 1;} return res;} // a = 0 return 0 | b = 0 return 1

void pre_compute() {
    fact[0] = 1;
    for (int i = 1; i < MAXM; i++) fact[i] = fact[i - 1]*i % MOD;
    ifact[MAXM - 1] = expo(fact[MAXM - 1], MOD - 2, MOD);
    for (int i = MAXM - 2; i >= 0; i--) ifact[i] = ifact[i + 1] * (i + 1) % MOD;
}
ll nCk(ll n, ll k) {
    return fact[n]*ifact[k] % MOD
        *ifact[n - k] % MOD;
}
void solve() {
    cin >> m >> n;
    
    n_1_pow[0] = n_pow[0] = 1;
    for (int i = 1; i < MAXM; i++) {
        n_1_pow[i] = n_1_pow[i - 1] * (n - 1) % MOD;
        n_pow[i] = n_pow[i - 1] * n % MOD;
    }

    ll ans = 0;
    for (int i = n - 1; i < m; i++) {
        ll remain = m - (i + 1);
        ll len = i + 1;
        ll cur = nCk(len - 1, n - 1);
        cur = (cur * n_1_pow[len - n]) % MOD;
        cur = (cur * n_pow[remain]) % MOD;
        ans = (ans + cur) % MOD;
    }
    cout << ans << "\n";
}

int main() {
    int T; cin >> T;
    pre_compute();
    while (T--) {
        solve();
    }
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    return 0;
}
