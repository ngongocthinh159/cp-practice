/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://usaco.org/index.php?page=viewproblem2&cpid=766
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
freopen("barnpainting.in", "r", stdin);
freopen("barnpainting.out", "w", stdout);
#endif
}
/*--------------------------------------------------------------------------------------------------------------------------*/

#define N 100005
#define C 3
int dp[N][C], c[N];
vector<int> g[N];
int n, k;
void pre_compute() {
    
}
void dfs(int u, int p) {
    if ((g[u].size() == 1 && g[u][0] == p) || !g[u].size()) {
        if (c[u] != -1) 
            dp[u][c[u]] = 1;
        else {
            for (int i = 0; i < C; i++) {
                dp[u][i] = 1;
            }
        }
        return;
    }
    for (auto  v : g[u]) if (v != p) 
        dfs(v, u);
    for (int i = 0; i < C; i++) {
        if (c[u] == -1 || (c[u] != -1 && i == c[u])) {
            ll res = 1;
            for (auto v : g[u]) if (v != p) {
                ll v_contrib = 0;
                for (int j = 0; j < C; j++) if (i != j) {
                    v_contrib += dp[v][j];
                    if (v_contrib >= MOD) v_contrib -= MOD;
                }
                res = res * v_contrib % MOD;
                if (!res) break;
            }
            dp[u][i] = res;
        }
    }
}
void solve() {
    cin >> n >> k;
    for (int i = 0; i <= n; i++) c[i] = -1;
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for (int i = 0; i < k; i++) {
        int u, val; cin >> u >> val;
        val--;
        c[u] = val;
    }
    dfs(1, -1);
    ll ans = 0;
    for (int i = 0; i < C; i++) {
        ans += dp[1][i];
        if (ans >= MOD) ans -= MOD;
    }
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