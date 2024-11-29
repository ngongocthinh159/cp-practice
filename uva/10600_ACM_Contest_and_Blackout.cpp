/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1541
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define IINF ((int)1e9)
#define MAX 105
#define LOG 20
#define RELAX(x, y) (x > y ? (x) : (y))
#define MASK(j) (1 << (j))

int n, m;
vector<vector<int>> edges;
vector<int> choose_edges;
ll min_mst;

int height[MAX], par[LOG + 1][MAX], rmq_max[LOG + 1][MAX];

void prim(vector<vector<int>> &g) {
    min_mst = 0;
    set<vector<int>> S;
    vector<vector<int>> min_e(n + 1, {IINF, -1, -1});
    S.insert({0, 1, -1});
    min_e[1] = {0, -1, -1};
    vector<int> visited(n + 1);
    while (S.size()) {
        auto p = *S.begin();
        S.erase(S.begin());
        int w_paru = p[0];
        int u = p[1];
        int e_idx = p[2];
        int par = min_e[u][1];

        visited[u] = true;
        if (par != -1) choose_edges.push_back(e_idx);
        min_mst += w_paru;

        for (auto &idx : g[u]) {
            int v = edges[idx][0]^edges[idx][1]^u;
            int w_uv = edges[idx][2];
            if (!visited[v] && min_e[v][0] > w_uv) {
                S.erase({min_e[v][0], v, min_e[v][2]});
                min_e[v] = {w_uv, u, idx};
                S.insert({min_e[v][0], v, min_e[v][2]});
            }
        }
    }
}
void dfs(int u, int dir_par, vector<vector<int>> &g) {
    for (auto &idx : g[u]) {
        int v = edges[idx][0]^edges[idx][1]^u;
        int w_uv = edges[idx][2];
        if (v != dir_par) {
            height[v] = height[u] + 1;
            par[0][v] = u;
            rmq_max[0][v] = w_uv;
            dfs(v, u, g);
        }
    }
}
int query_max_edge(int u, int v) {
    if (height[u] < height[v]) swap(u, v);
    int len = height[u] - height[v];
    int ans = INT_MIN;
    for (int bit = LOG; bit >= 0; bit--) {
        if ((len >> bit) & 1) {
            ans = RELAX(ans, rmq_max[bit][u]);
            u = par[bit][u];
        }
    }
    return ans;
}
int jump(int u, int k) {
    int res = u;
    for (int bit = LOG; bit >= 0; bit--) {
        if ((k >> bit) & 1) res = par[bit][res];
    }
    return res;
}
int query_lca(int u, int v) {
    if (height[u] < height[v]) swap(u, v);
    u = jump(u, height[u] - height[v]);
    if (u == v) return u;
    for (int bit = LOG; bit >= 0; bit--) {
        if (par[bit][u] != par[bit][v]) {
            u = par[bit][u];
            v = par[bit][v];
        }
    }
    return par[0][v];
}
void solve() {
    cin >> n >> m;
    vector<vector<int>> g;
    g.resize(n + 1);
    edges.clear();
    choose_edges.clear();
    for (int j = 0; j <= LOG; j++) 
        for (int i = 1; i <= n; i++) {
            rmq_max[j][i] = IINF;
            par[j][i] = 0;
        }

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back({u, v, w});
        g[u].push_back(i);
        g[v].push_back(i);
    }
    prim(g);
    vector<vector<int>> g2;
    g2.resize(n + 1);
    for (auto &idx : choose_edges) {
        vector<int> e = edges[idx];
        g2[e[0]].push_back(idx);
        g2[e[1]].push_back(idx);
    }
    swap(g, g2);
    dfs(1, -1, g);
    for (int j = 1; j <= LOG; j++)
        for (int i = 1; i <= n; i++) {
            if (height[i] - MASK(j) >= 0) {
                par[j][i] = par[j - 1][par[j - 1][i]];
            }
        }
    for (int j = 1; j <= LOG; j++)
        for (int i = 1; i <= n; i++) {
            if (height[i] - MASK(j) >= 0) {
                rmq_max[j][i] = RELAX(rmq_max[j - 1][i], rmq_max[j - 1][par[j - 1][i]]);
            }
        }
    unordered_set<int> S;
    for (auto idx : choose_edges) S.insert(idx);
    ll ans = IINF;
    for (int i = 0; i < m; i++) {
        if (!S.count(i)) {
            int u = edges[i][0];
            int v = edges[i][1];
            int w_uv = edges[i][2];
            int lca_uv = query_lca(u, v);
            int max_e = max(query_max_edge(u, lca_uv), query_max_edge(v, lca_uv));
            ans = min(ans, min_mst + w_uv - max_e);
        }
    }
    cout << min_mst << " " << ans << "\n";
}
int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#ifndef ONLINE_JUDGE
    freopen("Input.txt", "r", stdin);
    freopen("Output.txt", "w", stdout);
#endif

    int cases;
    cin >> cases;
    while (cases--) {
        solve();
    }

    return 0;
}
