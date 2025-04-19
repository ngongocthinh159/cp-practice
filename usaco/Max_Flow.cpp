/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://usaco.org/current/index.php?page=viewproblem2&cpid=576
*/

#include<bits/stdc++.h>
using namespace std;

#define nline '\n'
#define ll long long
#define MOD 1000000007
#define MOD1 998244353
#define LINF ((long long)1e18)
#define IINF ((int)1e9)

#define fastio() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
void IN_OUT() {
#ifndef ONLINE_JUDGE
freopen("maxflow.in", "r", stdin);
freopen("maxflow.out", "w", stdout);
#endif
}
/*--------------------------------------------------------------------------------------------------------------------------*/

#define N 50005
int n, k, T = -1;
int big[N], chain[N], depth[N], pos[N], par[N];
int segtree[4*N], lazy[4*N];
vector<int> g[N];

void pre_compute() {
    
}
void apply_and_tag(int idx, int s, int e, int val) {
    segtree[idx] += (e - s + 1) * val;
    lazy[idx] += val;
}
void push_down(int idx, int s, int e) {
    if (lazy[idx]) {
        int m = (s + e)/2;
        apply_and_tag(2*idx, s, m, lazy[idx]);
        apply_and_tag(2*idx + 1, m + 1, e, lazy[idx]);
        lazy[idx] = 0;
    }
}
int merge(const int &a, const int &b) {
    return a + b;
}
void update(int idx, int s, int e, int l, int r, int val) {
    if (s > r || l > e || s > e || l > r) return;
    if (l <= s && e <= r) {
        apply_and_tag(idx, s, e, val);
        return;
    }
    push_down(idx, s, e);
    int m = (s + e)/2;
    update(2*idx, s, m, l, r, val);
    update(2*idx + 1, m + 1, e, l, r, val);
    segtree[idx] = merge(segtree[2*idx], segtree[2*idx + 1]);
}
int query(int idx, int s, int e, int l, int r) {
    if (s > r || l > e || s > e || l > r) return 0;
    if (l <= s && e <= r) return segtree[idx];
    push_down(idx, s, e);
    int m = (s + e)/2;
    return merge(query(2*idx, s, m, l, r), query(2*idx + 1, m + 1, e, l, r));
}
int dfs_sz(int u, int p) {
    int mxc = 0, sz_u = 1;
    for (auto v : g[u]) if (v != p) {
        depth[v] = depth[u] + 1;
        par[v] = u;
        int sz_v = dfs_sz(v, u);
        sz_u += sz_v;
        if (mxc < sz_v) mxc = sz_v, big[u] = v;
    }
    return sz_u;
}
void dfs_chain(int u, int p, int top) {
    chain[u] = top;
    pos[u] = ++T;
    if (big[u])
        dfs_chain(big[u], u, top);
    for (auto v : g[u]) if (v != p && v != big[u])
        dfs_chain(v, u, v);
}
void update_hld(int u, int v, int val) {
    while (chain[u] != chain[v]) {
        if (depth[chain[u]] < depth[chain[v]]) swap(u, v);
        update(1, 0, n - 1, pos[chain[u]], pos[u], val);
        u = par[chain[u]];
    }
    if (depth[u] > depth[v]) swap(u, v);
    update(1, 0, n - 1, pos[u], pos[v], val);
}
void solve() {
    cin >> n >> k;
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs_sz(1, -1);
    dfs_chain(1, -1, 1);
    for (int i = 0; i < k; i++) {
        int u, v; cin >> u >> v;
        update_hld(u, v, 1);
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) ans = max(ans, query(1, 0, n - 1, pos[i], pos[i]));
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