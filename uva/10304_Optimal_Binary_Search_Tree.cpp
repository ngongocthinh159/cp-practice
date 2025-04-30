/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1245
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

#define N 255
int n;
int freq[N], K[N][N];
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
    for (int i = 0; i < n; i++) cin >> freq[i], pref[i + 1] = pref[i] + freq[i];
    for (int i = 0; i < n; i++) {
        dp[i][i] = freq[i];
        K[i][i] = i;
        for (int j = i + 1; j < n; j++)
            dp[i][j] = LINF;
    }
    for (int i = n - 2; i >= 0; i--)
        for (int j = i + 1; j < n; j++) {
            for (int k = K[i][j - 1]; k <= K[i + 1][j]; k++) {
                if (minimize(dp[i][j], dp[i][k - 1] + dp[k + 1][j] + pref[j + 1] - pref[i])) {
                    K[i][j] = k;
                }
            }
        }
    cout << dp[0][n - 1] - pref[n] << nline;
}

int main() {
    fastio();
    IN_OUT();
    int T = 1;
    // cin >> T;
    pre_compute();
    while (cin >> n)
        solve();
    // for (int cases = 1; cases <= T; cases++) {

    // }
    return 0;
}