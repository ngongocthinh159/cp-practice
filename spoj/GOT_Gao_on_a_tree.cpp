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
freopen("Input.txt", "r", stdin);
freopen("Output.txt", "w", stdout);
#endif
}
/*--------------------------------------------------------------------------------------------------------------------------*/

struct FenwickTree {
    vector<int> bit;  // binary indexed tree
    int n;

    FenwickTree(int n) {
        this->n = n;
        bit.assign(n, 0);
    }

    FenwickTree(vector<int> const &a) : FenwickTree(a.size()) {
        for (size_t i = 0; i < a.size(); i++)
            add(i, a[i]);
    }

    int sum(int r) {
        int ret = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            ret += bit[r];
        return ret;
    }

    int sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }

    void add(int idx, int delta) {
        for (; idx < n; idx = idx | (idx + 1))
            bit[idx] += delta;
    }
};



#define N 100005
#define M 200005
#define LOG 17
struct Query {
    int u, v, c, idx;  
};
int n, m, T = -1;
int in[N], out[N], depth[N], val[N], par[LOG + 1][N];
bool ans[M];
vector<int> g[N], val_to_node[N];
vector<Query> val_to_query[N];

void pre_compute() {
    
}
void dfs(int u, int p) {
    in[u] = ++T;
    for (auto v : g[u]) if (v != p) {
        depth[v] = depth[u] + 1;
        par[0][v] = u;
        for (int j = 1; j <= LOG; j++) {
            if (!par[j - 1][v]) break;
            par[j][v] = par[j - 1][par[j - 1][v]];
        }
        dfs(v, u);
    }
    out[u] = ++T;
}
int get_lca(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    int k = depth[u] - depth[v];
    for (int bit = LOG; bit >= 0; bit--) if ((k >> bit) & 1) {
        u = par[bit][u];
    }
    if (u == v) return u;
    for (int bit = LOG; bit >= 0; bit--) if (par[bit][u] != par[bit][v]) {
        u = par[bit][u];
        v = par[bit][v];
    }
    return par[0][u];
}
int cal(int u, int v, int c, FenwickTree& tree) {
    int lca = get_lca(u, v);
    int res = tree.sum(0, in[u])
                + tree.sum(0, in[v])
                - 2 * tree.sum(0, in[lca])
                + (val[lca] == c);
    return res;
}
void clear() {
    T = -1;
    for (int i = 0; i <= n; i++) {
        g[i].clear();
        val_to_query[i].clear();
        val_to_node[i].clear();
    }
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= LOG; j++) {
            if (!par[j][i]) break;
            par[j][i] = 0;
        }
}
void solve() {
    for (int i = 1; i <= n; i++) {
        int c; cin >> c;
        val[i] = c;
        val_to_node[c].push_back(i);
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for (int i = 0; i < m; i++) {
        int u, v, c; cin >> u >> v >> c;
        val_to_query[c].push_back(Query({u, v, c, i}));
    }
    dfs(1, -1);

    FenwickTree tree(2*n);
    for (int i = 0; i <= n; i++) if (val_to_query[i].size()) {
        for (auto u : val_to_node[i]) {
            tree.add(in[u], 1);
            tree.add(out[u], -1);
        }
        for (auto &q : val_to_query[i]) {
            ans[q.idx] = cal(q.u, q.v, q.c, tree) >= 1;
        }
        for (auto u : val_to_node[i]) {
            tree.add(in[u], -1);
            tree.add(out[u], 1);
        }
    }
    for (int i = 0; i < m; i++) {
        if (ans[i])
            cout << "Find" << nline;
        else
            cout << "NotFind" << nline;
    }
    cout << nline;

    clear();
}

int main() {
    fastio();
    IN_OUT();
    int T = 1;
    int cnt = 1;
    pre_compute();
    while (cin >> n && cin >> m) {
        solve();
    }
    return 0;
}