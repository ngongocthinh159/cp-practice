/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/contest/161/problem/D
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
#define K 505
int n, k;
vector<int> g[N];
ll dp[N][K], ans = 0;
void pre_compute() {
    
}
void solve() {
    cin >> n >> k;
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    auto dfs = [](auto self, int u, int p) -> void {
        for (auto v : g[u]) if (v != p)
            self(self, v, u);
        dp[u][0] = 1;
        for (auto v : g[u]) if (v != p) {
            for (int d = 1; k - d - 1 >= 0; d++) {
                ans += dp[u][d] * dp[v][k - d - 1];
            }
            ans += dp[v][k - 1];
            for (int i = 2; i <= k; i++) {
                dp[u][i] += dp[v][i - 1];
            }
            dp[u][1] += 1;
        }
    };
    dfs(dfs, 1, -1);
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