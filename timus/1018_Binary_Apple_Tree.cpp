/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://acm.timus.ru/problem.aspx?space=1&num=1018
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

void maximize(int &x, int y) {
    if (x < y) x = y;
}
#define N 105
int n, q, dp[N][N];
vector<pair<int,int>> g[N];
void pre_compute() {
    
}
void dfs(int u, int p) {
    vector<pair<int,int>> child;
    for (auto &[v, app] : g[u]) if (v != p) {
        child.push_back({v, app});
        dfs(v, u);
    }
    if (child.size()) {
        for (int j1 = 0; j1 < q; j1++) {
            maximize(dp[u][j1 + 1], dp[child[0].first][j1] + child[0].second);

            if (child.size() == 1) continue;
            for (int j2 = 0; j2 < q; j2++) {
                maximize(dp[u][j2 + 1], dp[child[1].first][j2] + child[1].second);

                int i = j1 + j2 + 2;
                if (i <= q) {
                    maximize(dp[u][i], dp[child[0].first][j1] + child[0].second + 
                                        dp[child[1].first][j2] + child[1].second);
                }
            }
        }
    }
}
void solve() {
    cin >> n >> q;
    for (int i = 0; i < n - 1; i++) {
        int u, v, ap; cin >> u >> v >> ap;
        g[u].push_back({v, ap});
        g[v].push_back({u, ap});
    }
    dfs(1, -1);
    cout << dp[1][q] << nline;
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