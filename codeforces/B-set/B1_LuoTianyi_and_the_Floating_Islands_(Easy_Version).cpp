/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/problemset/problem/1824/B1
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
ll expo(ll a, ll b, ll mod) {if (a==0) return 1%mod; ll res = 1; while (b > 0) {if (b & 1)res = (res * a) % mod; a = (a * a) % mod; b = b >> 1;} return res;} // a = 0 return 0 | b = 0 return 1
ll expo(ll a, ll b) {ll res = 1; while (b > 0) {if (b & 1)res = res * a; a = a * a; b = b >> 1;} return res;} // a = 0 return 0 | b = 0 return 1
/*--------------------------------------------------------------------------------------------------------------------------*/

#define N 200005
int n, k;
vector<int> g[N];
ll fact[N], inv[N];
ll child[N], toRoot[N], dp[N];
void pre_compute() {
    fact[0] = 1;
    for (int i = 1; i < N; i++) fact[i] = fact[i - 1] * i % MOD;
    inv[N - 1] = expo(fact[N - 1], MOD - 2, MOD);
    for (int i = N - 2; i >= 0; i--) inv[i] = inv[i + 1] * (i + 1) % MOD;
}
ll nCk(ll n, ll k) {
    if (k > n) return 0;
    return fact[n] * inv[k] % MOD * inv[n - k] % MOD;
}
ll nCk_inv(ll n, ll k) {
    if (k > n) return 0;
    return fact[k] * fact[n - k] % MOD * inv[n] % MOD;
}
ll dfs(int u, int p) {
    if (int(g[u].size()) == 1 && g[u][0] == p) {
        child[u] = 1;
        return 0;
    }

    child[u] = 1;
    for (auto v : g[u]) if (v != p) {
        dfs(v, u);

        ll tmp = 0;
        tmp += child[u] * ((toRoot[v] + child[v]) % MOD) % MOD;
        tmp %= MOD;
        tmp += toRoot[u] * child[v] % MOD;
        tmp %= MOD;

        dp[u] += tmp;
        dp[u] %= MOD;

        dp[u] += dp[v];
        dp[u] %= MOD;
    
        child[u] += child[v];
        toRoot[u] += (toRoot[v] + child[v]) % MOD;
        toRoot[u] %= MOD;
    }

    return dp[u];
}
void solve() {
    cin >> n >> k;
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    if (k == 1) {
        cout << 1 << nline;
    } else if (k == 2) {
        ll res = dfs(1, 0);
        res += nCk(n, 2);
        res %= MOD;
        cout << (res * nCk_inv(n, 2) % MOD) << nline;
    } else {
        cout << 1 << nline;
    }
}

int main() {
    fastio();
    IN_OUT();
    int T = 1;
    // cin >> T;
    pre_compute();
    for (int cases = 1; cases <= T; cases++) {

        solve();
    }
    return 0;
}