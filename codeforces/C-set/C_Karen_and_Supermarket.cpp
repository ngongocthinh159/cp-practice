/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/contest/815/problem/C
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

#define N 5005
int n, b;
vector<int> g[N];
int c[N], d[N], subsize[N];
ll dp[N][N][2], cur[N][2], pref[N][2];
void pre_compute() {
    
}
void dfs(int u, int p) {
    subsize[u] = 1;
    for (auto v : g[u]) if (v != p) {
        dfs(v, u);
        subsize[u] += subsize[v];
    }
    
    for (int i = 0; i <= subsize[u]; i++)
        for (int j = 0; j < 2; j++)
            cur[i][j] = LINF;
    cur[0][0] = 0;

    int cur_size = 0;
    for (auto v : g[u]) if (v != p) {
        for (int i = 0; i <= cur_size; i++) {
            pref[i][0] = cur[i][0];
            pref[i][1] = cur[i][1];
            cur[i][0] = cur[i][1] = LINF;
        }

        for (int u_cnt = 0; u_cnt <= cur_size; u_cnt++)
            for (int v_cnt = 0; v_cnt <= subsize[v]; v_cnt++) {
                cur[u_cnt + v_cnt][0] = min(cur[u_cnt + v_cnt][0], pref[u_cnt][0] + dp[v][v_cnt][0]);
                cur[u_cnt + v_cnt][1] = min(cur[u_cnt + v_cnt][1], pref[u_cnt][0] + dp[v][v_cnt][1]);
                cur[u_cnt + v_cnt][1] = min(cur[u_cnt + v_cnt][1], pref[u_cnt][1] + dp[v][v_cnt][0]);
                cur[u_cnt + v_cnt][1] = min(cur[u_cnt + v_cnt][1], pref[u_cnt][1] + dp[v][v_cnt][1]);
            }
        
        cur_size += subsize[v];
    }

    for (int i = 1; i <= subsize[u]; i++) {
        dp[u][i][0] = min(cur[i][0], cur[i - 1][0] + c[u]);
        dp[u][i][1] = min(cur[i - 1][0], cur[i - 1][1]) + c[u] - d[u];
    }
}
void solve() {
    cin >> n >> b;
    for (int i = 1; i <= n; i++) {
        cin >> c[i] >> d[i];
        if (i >= 2) {
            int p; cin >> p;
            g[p].push_back(i);
            g[i].push_back(p);
        }
    }
    dfs(1, -1);
    int ans = 0;
    for (int i = 1; i <= subsize[1]; i++) {
        if (dp[1][i][0] > b && dp[1][i][1] > b) break;
        ans = i;
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