/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://www.spoj.com/problems/BRKSTRNG/cstart=0
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

#define N 1005
int n, m, a[N], opt[N][N];
ll dp[N][N];
bool minimize(ll &x, ll y) {
    if (x > y) {
        x = y;
        return true;
    }
    return false;
}
ll C(int l, int r) {
    int lo = l == 0 ? 1 : a[l - 1] + 1;
    int hi = r == m - 1 ? n : a[r + 1];
    return hi - lo + 1;
}
void pre_compute() {
    
}
bool solve() {
    if (!(cin >> n))
        return false;
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < m; i++) {
        dp[i][i] = C(i, i);
        opt[i][i] = i;
        for (int j = i + 1; j < m; j++)
            dp[i][j] = LINF;
    }
    for (int i = m - 2; i >= 0; i--)
        for (int j = i + 1; j < m; j++) {
            for (int k = opt[i][j - 1]; k <= opt[i + 1][j]; k++) {
                if (minimize(dp[i][j], (k - 1 >= i ? dp[i][k - 1] : 0) + (k + 1 <= j ? dp[k + 1][j] : 0) + C(i, j)))
                    opt[i][j] = k;
            }
        }
    cout << dp[0][m - 1] << nline;

    return true;
}

int main() {
    fastio();
    IN_OUT();
    int T = 1;
    // cin >> T;
    pre_compute();
    while (solve()) {}
    return 0;
}