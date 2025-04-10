/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://www.codechef.com/problems/LGSEG?tab=statement
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

#define N 100005
int n, a[N], k, S;
void pre_compute() {
    
}
void solve() {
    cin >> n >> k >> S;
    for (int i = 0; i < n; i++) cin >> a[i];
    int msb = 32 - __builtin_clz(k) - 1;
    vector<vector<int>> par(msb + 1, vector<int>(n + 1));
    for (int j = 0; j <= msb; j++) par[j][n] = n;
    ll sum = 0;
    for (int r = n - 1, l = n - 1; r >= 0; r--) {
        sum += a[r];
        while (l > r && sum > S) {
            sum -= a[l];
            l--;
        }
        par[0][r] = l + 1;
    }
    for (int j = 1; j <= msb; j++)
        for (int i = 0; i < n; i++)
            par[j][i] = par[j - 1][par[j - 1][i]];
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int u = i;
        for (int j = msb; j >= 0; j--) if ((k >> j) & 1)
            u = par[j][u];
        ans = max(ans, u - i);
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