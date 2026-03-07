/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/contest/2192/problem/D
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

#define N 200005
int n;
int a[N], depth[N];
ll sum_a[N], sum[N], best_d[N], best[N];
vector<vector<int>> g;
void dfs(int u, int p) {
    for (int i = 0; i < (int) g[u].size();i++) {
        if (g[u][i] == p) {
            swap(g[u][i], g[u].back());
            g[u].pop_back();
            break;
        }
    }

    sum_a[u] = a[u];
    sum[u] = 0;
    best[u] = 0;
    best_d[u] = depth[u];
    for (auto v : g[u]) {
        depth[v] = depth[u] + 1;
        dfs(v, u);
        sum_a[u] += sum_a[v];
        sum[u] += sum[v] + sum_a[v];
        best_d[u] = max(best_d[u], best_d[v]);
    }
    
    int n = g[u].size();
    vector<ll> pref(n + 1), surf(n + 2), pref_d(n + 1), surf_d(n + 2);
    for (int i = 0; i < (int) g[u].size();i++) {
        int v = g[u][i];
        pref[i + 1] = pref[i] + sum[v] + sum_a[v];
        pref_d[i+1] = max(pref_d[i], best_d[v]);
    }
    for (int i = n - 1; i >= 0; i--) {
        int v = g[u][i];
        surf[i + 1] = surf[i + 2] + sum[v] + sum_a[v];
        surf_d[i + 1] = max(surf_d[i + 2], best_d[v]);
    }
    for (int i = 0; i < (int) g[u].size(); i++) {
        int v = g[u][i];
        best[u] = max(best[u], best[v] + sum_a[v] + pref[i] + surf[i + 2]);

        if (g[u].size() >= 2) {
            ll delta = 1 + max(pref_d[i], surf_d[i + 2]) - depth[u];
            if (delta >= 1) {
                best[u] = max(best[u], sum[v] + sum_a[v] * delta + pref[i] + surf[i + 2]);
            }
        }
    }
}
void pre_compute() {
    
}
void solve() {
    cin >> n;
    for (int i= 1; i <= n; i++) cin >> a[i];
    g.clear();
    g.resize(n + 1);
    for (int i= 0; i < n - 1;i ++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1, 0);
    for (int i = 1; i<= n;i++) cout << best[i] << ' ';
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