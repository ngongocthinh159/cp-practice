/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://oj.vnoi.info/problem/dtgame
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

#define N 2005
int n, p[N];
ll pref[N], dp[N][N];
int opt[N][N];
void pre_compute() {

}
ll C(int l, int r) {
    if (l > r) return 0;
    return pref[r + 1] - pref[l];
}
bool maximize(ll &x, ll y) {
    if (x < y) {
        x = y;
        return true;
    }
    return false;
}
void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
        pref[i + 1] = pref[i] + p[i];
        dp[i][i] = 0;
        opt[i][i] = i;
        for (int j = i + 1; j <= n; j++)    
            dp[i][j] = -LINF;
    }
    for (int i = n - 1; i >= 1; i--)
        for (int j = i + 1; j <= n; j++) {
            for (int k = opt[i][j - 1]; k <= opt[i + 1][j]; k++) {
                if (maximize(dp[i][j], min(dp[i][k] + C(i, k), dp[k + 1][j] + C(k + 1, j))))
                    opt[i][j] = k;
            }
        }
    cout << dp[1][n] << nline;
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