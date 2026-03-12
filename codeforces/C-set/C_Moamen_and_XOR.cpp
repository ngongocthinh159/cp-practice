/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/problemset/problem/1557/C
*/

// #include<bits/stdc++.h>
#include "bits/stdc++.h"
using namespace std;

#define nline '\n'
#define ll long long
#define MOD 1000000007
#define MOD1 998244353
#define LINF ((long long)1e18)
#define IINF ((int)1e9)
#define MASK(i) (1LL << (i))
#define all(v) (v).begin(), (v).end()


template<class X, class Y>
bool minimize(X &x, const Y &y) {
    if (x > y) {
        x = y;
        return true;
    } else return false;
}
template<class X, class Y>
bool maximize(X &x, const Y &y) {
    if (x < y) {
        x = y;
        return true;
    } else return false;
}

#define fastio() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
void IN_OUT() {
#ifndef ONLINE_JUDGE
freopen("Input.txt", "r", stdin);
freopen("Output.txt", "w", stdout);
#endif
}
struct chash {static uint64_t splitmix64(uint64_t x) {x += 0x9e3779b97f4a7c15;x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;x = (x ^ (x >> 27)) * 0x94d049bb133111eb;return x ^ (x >> 31);}size_t operator()(uint64_t x) const {static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();return splitmix64(x + FIXED_RANDOM);}}; // https://codeforces.com/blog/entry/62393
struct chashp {static uint64_t splitmix64(uint64_t x) {x += 0x9e3779b97f4a7c15;x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;x = (x ^ (x >> 27)) * 0x94d049bb133111eb;return x ^ (x >> 31);}size_t operator()(pair<uint64_t,uint64_t> x) const {static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();return splitmix64(x.first + FIXED_RANDOM)^(splitmix64(x.second + FIXED_RANDOM) >> 1);}}; // https://codeforces.com/blog/entry/62393
/*--------------------------------------------------------------------------------------------------------------------------*/

#define N 200005
int n,k;
ll fact[N], inv[N], _2pow[N];
ll nCk(ll n, ll k) {
    if (k > n) return 0;
    return fact[n] * inv[n - k] % MOD * inv[k] % MOD;
}
ll expo(ll a, ll b) {
    ll res = 1;
    ll cur = a;
    while (b) {
        if (b&1) res = res * cur % MOD;
        cur = cur * cur % MOD;
        b >>= 1;
    } 
    return res;
}
void add(ll &x, ll y) {
    x += y;
    if (x >= MOD) x -= MOD;
}
void pre_compute() {
    fact[0] = 1;
    for (int i = 1; i < N; i++) fact[i] = fact[i - 1] * i % MOD;
    inv[N - 1] = expo(fact[N - 1], MOD - 2);
    for (int i = N - 2; i >= 0; i--) inv[i] = inv[i + 1] * (i + 1) % MOD;
    _2pow[0] = 1;
    for (int i = 1; i < N; i++) _2pow[i] = _2pow[i - 1] * 2 % MOD;
}
void solve() {
    cin >> n >> k;
    vector<vector<ll>> dp(k + 1, vector<ll>(2));
    ll c1 = 0, c2 = 0;
    for (int i = 0; i <= n - 1; i += 2) add(c1, nCk(n, i));
    for (int i = 0; i <= n - 2; i += 2) add(c2, nCk(n, i));
    dp[k][0] = 1;
    for (int i = k; i >= 1; i--)
        for (int smaller = 0; smaller < 2; smaller++) if (dp[i][smaller]) {
            if (smaller == 1) {
                add(dp[i - 1][smaller], dp[i][smaller] * _2pow[n] % MOD);
            } else {
                {
                    ll cur = 0;
                    if (n & 1) {
                        cur++;
                        add(cur, c1);
                    } else {
                        add(cur, c2);
                    }
                    add(dp[i - 1][0], dp[i][smaller] * cur % MOD);
                }
                if (!(n&1))
                    add(dp[i - 1][1], dp[i][smaller]);
            }
        }
    ll ans = dp[0][0];
    add(ans, dp[0][1]);
    cout << ans << nline;
}

int main() {
    fastio();
    IN_OUT();
    int T = 1;
    cin >> T;
    pre_compute();
    for (int cases = 1; cases <= T; cases++) {

        solve();
    }
    return 0;
}