/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/contest/766/problem/E
*/

#include<bits/stdc++.h>
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


#define N 100005
#define BIT 20
int n;
int a[N], child[N];
bool del[N];
vector<int> g[N];
int b[BIT][2];
ll ans = 0, _2pow[BIT];
void pre_compute() {
    _2pow[0] = 1;
    for (int i = 1; i < BIT; i++) _2pow[i] = _2pow[i - 1] * 2;
}
int dfs(int u, int p) {
    child[u] = 1;
    for (auto v : g[u]) if (v != p && !del[v]) child[u] += dfs(v, u);
    return child[u];
}
int find_centroid(int u, int p, int sz) {
    for (auto v : g[u]) if (v != p && !del[v] && child[v] > sz/2)
        return find_centroid(v, u, sz);
    return u; 
}
void add(int x) {
    for (int i = BIT - 1; i >= 0; i--) b[i][(x >> i)&1]++;
}
void acc_sub(int u, int p, int cur) {
    cur = cur ^ a[u];
    for (int i = BIT - 1; i >= 0; i--)
        ans += 1ll * b[i][!((cur >> i) & 1)] * _2pow[i];
    for (auto v : g[u]) if (v != p && !del[v])
        acc_sub(v, u, cur);
}
void merge_sub(int u, int p, int cur) {
    cur = cur ^ a[u];
    add(cur);
    for (auto v : g[u]) if (v != p && !del[v])
        merge_sub(v, u, cur);
}
void CD(int u, int p) {
    dfs(u, p);
    u = find_centroid(u, p, child[u]);

    for (int i = BIT - 1; i >= 0; i--) b[i][0] = b[i][1] = 0;
    add(a[u]);
    for (auto v : g[u]) if (v != p && !del[v]) {
        acc_sub(v, u, 0);

        merge_sub(v, u, a[u]);
    }

    del[u] = 1;
    for (auto v : g[u]) if (v != p && !del[v])
        CD(v, u);
}
void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 0; i < n - 1; i ++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    CD(1, 0);
    for (int i = 1; i <= n; i++) ans += a[i];
    cout << ans << nline;
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