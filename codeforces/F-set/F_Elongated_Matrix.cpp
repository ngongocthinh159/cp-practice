/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/problemset/problem/1102/F
 */

#include <bits/stdc++.h>
using namespace std;

#define nline '\n'
#define ll long long
#define MOD 1000000007
#define MOD1 998244353
#define LINF ((long long)1e18)
#define IINF ((int)1e9)

#define fastio()                      \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL)
void IN_OUT() {
#ifndef ONLINE_JUDGE
    freopen("Input.txt", "r", stdin);
    freopen("Output.txt", "w", stdout);
#endif
}
/*--------------------------------------------------------------------------------------------------------------------------*/

#define N 16
#define M 10005
ll a[N][M];
ll D1[N][N], D2[N][N];
ll dp[N][N][1 << N];
void pre_compute() {
}
void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> a[i][j];
    if (n == 1) {
        ll ans = LINF;
        for (int j = 0; j < m - 1; j++) ans = min(ans, abs(a[0][j] - a[0][j + 1]));
        cout << ans << '\n';
        return;
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) if (i != j) {
            ll cur1 = LINF, cur2 = LINF;
            for (int k = 0; k < m; k++)
                cur1 = min(cur1, abs(a[i][k] - a[j][k]));
            for (int k = 0; k < m - 1; k++)
                cur2 = min(cur2, abs(a[j][k] - a[i][k + 1]));
            D1[i][j] = cur1;
            D2[i][j] = cur2;
        }
    int nMask = (1 << n) - 1;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int mask = 0; mask <= nMask; mask++)
                dp[i][j][mask] = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) if (i != j)
            dp[i][j][(1 << i) | (1 << j)] = D1[i][j];
    for (int mask = 0; mask <= nMask; mask++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) if (i != j) {
                if (!((mask >> i) & 1) || !((mask >> j) & 1)) continue;
                for (int k = 0; k < n; k++) if (!((mask >> k) & 1))
                    dp[i][k][mask | (1 << k)] =
                        max(dp[i][k][mask | (1 << k)],
                            min(dp[i][j][mask], D1[j][k]));
            }
    ll ans = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) if (i != j)
            ans = max(ans, min(dp[i][j][nMask], D2[i][j]));
    cout << ans << '\n';
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