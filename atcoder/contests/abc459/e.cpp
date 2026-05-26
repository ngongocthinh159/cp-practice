/**
 * Author: Thinh Ngo Ngoc
 * Solution for: 
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
ll expo(ll a, ll b, ll mod) {if (a==0) return 1%mod; ll res = 1; while (b > 0) {if (b & 1)res = (res * a) % mod; a = (a * a) % mod; b = b >> 1;} return res;} // a = 0 return 0 | b = 0 return 1
struct chash {static uint64_t splitmix64(uint64_t x) {x += 0x9e3779b97f4a7c15;x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;x = (x ^ (x >> 27)) * 0x94d049bb133111eb;return x ^ (x >> 31);}size_t operator()(uint64_t x) const {static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();return splitmix64(x + FIXED_RANDOM);}}; // https://codeforces.com/blog/entry/62393
struct chashp {static uint64_t splitmix64(uint64_t x) {x += 0x9e3779b97f4a7c15;x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;x = (x ^ (x >> 27)) * 0x94d049bb133111eb;return x ^ (x >> 31);}size_t operator()(pair<uint64_t,uint64_t> x) const {static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();return splitmix64(x.first + FIXED_RANDOM)^(splitmix64(x.second + FIXED_RANDOM) >> 1);}}; // https://codeforces.com/blog/entry/62393
/*--------------------------------------------------------------------------------------------------------------------------*/


#define MX 1000005
#define N 200005
int n;
ll fact[MX], inv[MX];
vector<int> g[N];
ll p[N], c[N], d[N];
ll subtreeCandies[N], subtreeChosen[N];
ll dp[N];
void pre_compute() {
    fact[0] = 1;
    for (int i = 1; i < MX; i++) fact[i] = fact[i - 1] * i % MOD1;
    inv[MX - 1] = expo(fact[MX - 1], MOD1 - 2, MOD1);
    for (int i = MX - 2; i >= 0; i--) inv[i] = inv[i + 1] * (i + 1) % MOD1;
}
ll nCk(ll n, ll k) {
    if (k > n) return 0;
    ll res = inv[k];
    for (ll i = n; i >= n - k + 1; i--) {
        res = res * (i % MOD1) % MOD1;
    }
    return res;
}
void dfs(int u, int p) {
    dp[u] = 1;
    subtreeCandies[u] = c[u];
    for (auto v : g[u]) if (v != p) {
        dfs(v, u);
        subtreeCandies[u] += subtreeCandies[v];
        subtreeChosen[u] += subtreeChosen[v];
        dp[u] = dp[u] * dp[v] % MOD1;
    }
    dp[u] = dp[u] * nCk(subtreeCandies[u] - subtreeChosen[u], d[u]) % MOD1;
    subtreeChosen[u] += d[u];
}
void solve() {
    cin >> n;
    for (int i = 2; i <= n; i++) {
        cin >> p[i];
        g[i].push_back(p[i]);
        g[p[i]].push_back(i);
    }

    for (int i = 1; i <= n; i++) cin >> c[i];
    for (int i = 1; i <= n; i++) cin >> d[i];
    dfs(1, 0);
    cout << dp[1] << nline;
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