/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/contest/1401/problem/D
*/

#include "bits/stdc++.h"
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

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
ll expo(ll a, ll b, ll mod = MOD) {if (a==0) return 1%mod; ll res = 1; while (b > 0) {if (b & 1)res = (res * a) % mod; a = (a * a) % mod; b = b >> 1;} return res;} // a = 0 return 0 | b = 0 return 1
ll __gcd__(ll a, ll b) {if (!a || !b) return a | b; unsigned shift = __builtin_ctz(a | b); a >>= __builtin_ctz(a); do { b >>= __builtin_ctz(b); if (a > b) swap(a, b); b -= a; } while (b); return a << shift;} // only a >= 0 && b >= 0
ll gcd(ll a, ll b) {a = abs(a); b = abs(b); return __gcd__(a, b);} // get abs(a), abs(b) in case a < 0 || b < 0
typedef tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag, tree_order_statistics_node_update > pbds; // find_by_order, order_of_key
/*--------------------------------------------------------------------------------------------------------------------------*/

#define N 100005
int n, m;
vector<int> g[N];
int p[N];
struct edge {
    int u, v;
};
edge es[N];
ll pairCnt[N];
int child[N];
void pre_compute() {
    
}
void dfs1(int u, int p) {
    child[u] = 1;
    for (auto eidx : g[u]) {
        int v = es[eidx].u ^ es[eidx].v ^ u;
        if (v != p) {
            dfs1(v, u);
            child[u] += child[v];
        }
    }
}
void dfs(int u, int p, int ePos, int out) {
    if (ePos != 0) {
        pairCnt[ePos] = 1ll * child[u] * out; 
    }
    for (auto eidx : g[u]) {
        int v = es[eidx].u ^ es[eidx].v ^ u;
        if (v != p) {
            int nout = out + child[u] - child[v];
            dfs(v, u, eidx, nout);
        }
    }
}
void solve() {
    cin >> n;
    for (int i = 0; i <= n; i++) g[i].clear();
    for (int i = 1; i <= n - 1; i++) {
        cin >> es[i].u >> es[i].v;
        g[es[i].u].push_back(i);
        g[es[i].v].push_back(i);
    }
    cin >> m;
    for (int i = 1; i <= m; i++) cin >> p[i];
    sort(p + 1, p + m + 1);
    dfs1(1, 0);
    dfs(1, 0, 0, 0);
    vector<int> order(n);
    iota(all(order), 0);
    sort(order.begin() + 1, order.end(), [&](int i, int j){
        return pairCnt[i] < pairCnt[j];
    });
    ll ans = 0;
    for (int i = n - 1, j = m; i >= 1; i--) {
        int cur;
        if (j >= i) {
            cur = 1;
            while (j >= i) {
                cur = 1ll * cur * p[j] % MOD;
                j--;
            }
        } else {
            cur = j >= 1 ? p[j--] : 1;
        }
        ans += 1ll * cur * (pairCnt[order[i]] % MOD) % MOD;
        ans %= MOD;
    }
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