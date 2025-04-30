/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://oj.vnoi.info/problem/optcut
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
int n, a[N], opt[N][N];
ll pref[N], dp[N][N];
bool minimize(ll &x, ll y) {
    if (x > y) {
        x = y;
        return true;
    }
    return false;
}
void pre_compute() {
    
}
void solve() {
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i], pref[i + 1] = pref[i] + a[i];
    for (int i = 0; i < n; i++) {
        dp[i][i] = 0;
        opt[i][i] = i;
        for (int j = i + 1; j < n; j++)
            dp[i][j] = LINF;
    }
    for (int i = n - 2; i >= 0; i--)
        for (int j = i + 1; j < n; j++) {
            for (int k = opt[i][j - 1]; k <= min(j - 1, opt[i + 1][j]); k++)
                if (minimize(dp[i][j], dp[i][k] + dp[k + 1][j])) opt[i][j] = k;
            dp[i][j] += pref[j + 1] - pref[i];
        }
    cout << dp[0][n - 1] << nline;
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