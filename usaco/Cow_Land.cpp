/**
 * Author: Thinh Ngo Ngoc
 * Solution for: 
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
freopen("cowland.in", "r", stdin);
freopen("cowland.out", "w", stdout);
#endif
}
/*--------------------------------------------------------------------------------------------------------------------------*/


#define MAXN 100005
int n, q, T = -1;
int chain[MAXN], height[MAXN], big[MAXN], euler[MAXN], par[MAXN], e[MAXN], sz[MAXN], tin[MAXN];
vector<int> g[MAXN];

int segtree[4*MAXN];
void build(int i, int s, int e, int *arr) {
    if (s == e) {
        segtree[i] = arr[s];
        return;
    }
    int m = (s + e)/2;
    build(2*i, s, m, arr);
    build(2*i + 1, m + 1, e, arr);
    segtree[i] = segtree[2*i] ^ segtree[2*i + 1];
}
int query(int i, int s, int e, int l, int r) {
    if (s > r || e < l || s > e || l > r) return 0;
    if (l <= s && e <= r) return segtree[i];
    int m = (s + e)/2;
    return query(2*i, s, m, l, r) ^ query(2*i + 1, m + 1, e, l, r);
}
void update(int i, int s, int e, int pos, int val) {
    if (s == e) {
        segtree[i] = val;
        return;
    }
    int m = (s + e)/2;
    if (pos <= m) 
        update(2*i, s, m, pos, val);
    else
        update(2*i + 1, m + 1, e, pos, val);
    segtree[i] = segtree[2*i] ^ segtree[2*i + 1];
}

void dfs_sz(int u, int p) {
    sz[u] = 1;
    int big_sz = 0;
    big[u] = -1;
    for (auto v : g[u]) if (v != p) {
        height[v] = 1 + height[u];
        par[v] = u;
        dfs_sz(v, u);
        sz[u] += sz[v];
        if (sz[v] > big_sz) {
            big_sz = sz[v];
            big[u] = v;
        }
    }
}
void dfs_chain(int u, int p, int top) {
    euler[++T] = e[u];
    tin[u] = T;
    chain[u] = top;
    if (big[u] != -1) 
        dfs_chain(big[u], u, top);
    for (auto v : g[u]) if (v != p && v != big[u])
        dfs_chain(v, u, v);
}
int query_hld(int u, int v) {
    int ans = 0;
    while (chain[u] != chain[v]) {
        if (height[chain[u]] < height[chain[v]]) swap(u, v);
        ans ^= query(1, 0, n - 1, tin[chain[u]], tin[u]);
        u = par[chain[u]];
    }
    if (height[u] > height[v]) swap(u, v);
    ans ^= query(1, 0, n - 1, tin[u], tin[v]);
    return ans;
}
void pre_compute() {
    
}
void solve() {
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> e[i];
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs_sz(1, -1);
    dfs_chain(1, -1, 1);
    build(1, 0, n - 1, euler);

    for (int i = 0; i < q; i++) {
        int t, u, v;
        cin >> t >> u >> v;
        if (t == 1) {
            update(1, 0, n - 1, tin[u], v);
        } else {
            printf("%d\n", query_hld(u, v));
        }
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