/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://www.hackerearth.com/problem/algorithm/counting-on-tree-1/
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

#define N 50005
#define K 105
int n, k, a[N];
ll dp[N][K], buf[K];
vector<int> g[N];

void add(ll &x, ll y) {
    x += y;
    if (x >= MOD) x -= MOD;
}
void pre_compute() {
    
}
void dfs(int u, int p) {
    dp[u][0] = !a[u];
    dp[u][1] = a[u];
    for (auto v : g[u]) if (v != p) {
        dfs(v, u);
        
        for (int i = 0; i <= k; i++) buf[i] = 0;

        for (int c_sum = 0; c_sum <= k; c_sum++)
            for (int sum = 0; sum + c_sum <= k; sum++)
                add(buf[c_sum + sum], dp[v][c_sum] * dp[u][sum] % MOD);
        
        for (int i = 0; i <= k; i++) 
            add(dp[u][i], buf[i]);
    }
}
void clear() {
    for (int i = 0; i <= n; i++) {
        g[i].clear();
        for (int j = 0; j <= k; j++) 
            dp[i][j] = 0;
    }
}
void solve() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1, -1);

    ll res = 0;
    for (int u = 1; u <= n; u++)
        add(res, dp[u][k]);
    cout << res << nline;
    
    clear();
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