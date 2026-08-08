/**
 * Author: Thinh Ngo Ngoc
 * Solution for: 
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

#define N 200005
int n;
int top;
int leaf;
vector<int> g[N];
int buf[N];
int child[N];
int big[N];
int val[N];
void pre_compute() {
    
}
void dfs0(int u) {
    child[u] = 1;
    big[u] = -1;
    int mxChild = 0;
    for (int i = 0; i < int(g[u].size()); i++) {
        int v = g[u][i];
        dfs0(v);
        child[u] += child[v];
        if (maximize(mxChild, child[v])) big[u] = v;
    }
    if (big[u] == -1) leaf++;
}
multiset<int> dfs(int u) {
    if (big[u] == -1) return {val[u]};
    multiset<int> S = dfs(big[u]);
    for (int i = 0; i < int(g[u].size()); i++) {
        int v = g[u][i];
        if (v == big[u]) continue;
        auto s = dfs(v);
        for (auto x : s) S.insert(x);
    }
    int mn = min(*S.begin(), val[u]);
    int mx = max(*S.begin(), val[u]);
    buf[++top] = mn;
    S.erase(S.begin());
    S.insert(mx);
    return S;
}
void solve() {
    cin >> n;

    for (int i = 1; i <= n; i++) g[i].clear();
    top = 0;
    leaf = 0;

    for (int i = 1; i <= n; i++) cin >> val[i];
    for (int i = 2; i <= n; i++) {
        int p; cin >> p;
        g[p].push_back(i);
    }

    dfs0(1);

    auto S = dfs(1);
    sort(buf + 1, buf + top + 1, greater<>());
    ll sum = 0;
    for (auto x : S) sum += x;
    for (int i = 1; i < leaf; i++) cout << -1 << ' ';
    cout << sum << ' ';
    for (int i = leaf + 1, j = 1; i <= n; i++, j++) {
        sum += buf[j];
        cout << sum << ' ';
    }
    cout << nline;
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