/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/problemset/problem/2018/C
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

#define N 500005
int n;
void pre_compute() {
    
}
void solve() {
    cin >> n;
    vector<vector<int>> g(n + 1);
    vector<int> depth(n + 1), mxDepth(n + 1), diff(n + 2);
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    auto dfs1 = [&](auto self, int u, int p, int d) -> void {
        mxDepth[u] = d;
        depth[u] = d;
        for (auto v : g[u]) if (v != p) {
            self(self, v, u, d + 1);
            mxDepth[u] = max(mxDepth[u], mxDepth[v]);
        }
    };
    dfs1(dfs1, 1, -1, 0);
    for (int i = 1; i <= n; i++) {
        diff[depth[i]] += 1;
        diff[mxDepth[i] + 1] -= 1;
    }
    for (int i = 0; i < n; i++) diff[i + 1] += diff[i];
    int ans = INT_MAX;
    for (int i = 0; i < n; i++) {
        ans = min(ans, n - diff[i]);
    }
    cout << ans << nline;
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