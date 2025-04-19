/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/problemset/problem/1118/F1
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

#define N 300005
int n, a[N], in1[N], in2[N], out1[N], out2[N], ans = 0;
vector<int> g[N];
void dfs1(int u, int p) {
    in1[u] = a[u] == 1;
    in2[u] = a[u] == 2;
    for (auto v : g[u]) if (v != p) {
        dfs1(v, u);
        in1[u] += in1[v];
        in2[u] += in2[v];
    }
}
void dfs2(int u, int p) {
    for (auto v : g[u]) if (v != p) {
        out1[v] = in1[u] - in1[v] + out1[u];
        out2[v] = in2[u] - in2[v] + out2[u];
        if (! ((in1[v] >= 1 && in2[v] >= 1) || (out1[v] >= 1 && out2[v] >= 1)))
            ans++;
        dfs2(v, u);

    }
}
void pre_compute() {
    
}
void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs1(1, -1);
    dfs2(1, -1);
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