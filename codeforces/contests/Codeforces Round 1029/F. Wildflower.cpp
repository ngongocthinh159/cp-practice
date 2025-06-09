/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/contest/2117/problem/F
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

#define N 200005
int n;
vector<int> g[N];
ll _2pow[N];
int depth[N], leaf[N];
void pre_compute() {
    _2pow[0] = 1;
    for (int i = 1; i < N; i++) _2pow[i] = _2pow[i - 1] * 2 % MOD;
}
void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++) g[i].clear();
    int top = 0;
    int branch_node = -1;

    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    auto dfs = [&](auto self, int u, int p) -> void {
        if ((int) g[u].size() == (p == -1 ? 0 : 1)) { // check leaf node
            leaf[top++] = u;
        }
        int child = 0;
        for (auto v : g[u]) if (v != p) {
            depth[v] = depth[u] + 1;
            child++;
            self(self, v, u);
        }
        if (child >= 2) branch_node = u;
    };
    dfs(dfs, 1, -1);
    if (top > 2) {
        cout << 0 << nline;
        return;
    }
    if (top == 1) {
        cout << _2pow[n] << nline;
        return;
    }
    assert(branch_node != -1);
    if (depth[leaf[0]] < depth[leaf[1]]) swap(leaf[0], leaf[1]);
    int len1 = depth[leaf[0]] - depth[branch_node];
    int len2 = depth[leaf[1]] - depth[branch_node];
    int dif_len = len1 - len2;
    int len3 = depth[branch_node] - depth[1] + 1;
    ll ans = _2pow[len3] * _2pow[dif_len] % MOD;
    ans += _2pow[len3] * (dif_len - 1 >= 0 ? _2pow[dif_len - 1] : 1) % MOD;
    ans %= MOD;
    cout << ans << nline;
}

int main() {
    fastio();
    IN_OUT();
    int T = 1;
    cin >> T;
    pre_compute();
    for (int cases = 1; cases <= T; cases++) {
        // cout << "case " << cases << endl;
        solve();
    }
    return 0;
}