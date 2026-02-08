/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/contest/342/problem/E
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
#define LOG 18
int n, m;
vector<int> g[N];
int best[N], child[N], par[LOG][N], par1[N], depth[N], color[N];
bool del[N];

void pre_compute() {
    
}
int LCA(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    int k = depth[u] - depth[v];
    for (int bit = LOG - 1; bit >= 0; bit--) if ((k >> bit) & 1) u = par[bit][u];
    if (u == v) return u;
    for (int bit = LOG - 1; bit >= 0; bit--) if (par[bit][u] != par[bit][v]) {
        u = par[bit][u];
        v = par[bit][v]; 
    } 
    return par[0][u];
}
int dist(int u, int v) {
    return depth[u] + depth[v] - 2*depth[LCA(u, v)];
}
void dfs(int u, int p, int d) {
    depth[u] = d;
    for (auto v : g[u]) if (v != p) {
        par[0][v] = u;
        for (int j = 1; j < LOG; j++) par[j][v] = par[j - 1][par[j - 1][v]];
        dfs(v, u, d + 1);
    }
}
int dfs1(int u, int p) {
    child[u] = 1;
    for (auto v : g[u]) if (v != p && !del[v])
        child[u] += dfs1(v, u);
    return child[u];
}
int find_centroid(int u, int p, int sz) {
    for (auto v : g[u]) if (v != p && !del[v] && child[v] > sz/2)
        return find_centroid(v, u, sz);
    return u;
}
void CD(int u, int p) {
    int sz = dfs1(u, -1);
    u = find_centroid(u, -1, sz);
    
    par1[u] = p;
    del[u] = 1;
    for (auto v : g[u]) if (!del[v]) {
        CD(v, u);
    }
}
void paint(int u) {
    int v = u;
    while (v != -1) {
        best[v] = min(best[v], dist(u, v));
        v = par1[v];
    }
}
int query(int u) {
    int ans = IINF, v = u;
    while (v != -1) {
        ans = min(ans, best[v] + dist(u, v));
        v = par1[v];
    }
    return ans;
}
void solve() {
    cin >> n >> m;
    for (int i = 0; i < n - 1; i++) {
        int u,v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    // prepare
    dfs(1, -1, 0);
    color[1] = 1;
    CD(1, -1);
    
    for (int i = 1; i <= n; i++) best[i] = IINF;

    paint(1); // paint node 1
    int t, u;
    for (int i = 0; i < m; i++) {
        cin >> t >> u;
        if (t == 1)
            paint(u);
        else
            cout << query(u) << nline;
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