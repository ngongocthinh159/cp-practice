/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/problemset/problem/1829/H
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
int n, k;
int a[N];
void pre_compute() {
    
}
void add(ll &x, ll y){
    x += y;
    if (x >= MOD) x -= MOD;
}
void solve() {
    cin >> n >> k;
    for (int i = 0; i < n; i++) cin >> a[i];
    vector<vector<ll>> dp(n + 1, vector<ll>(1<<6));
    for (int i = 0; i < n; i++) {
        add(dp[i + 1][a[i]], 1);
        for (int mask = 0; mask < (1 << 6); mask++) if (dp[i][mask]) {
            add(dp[i + 1][mask], dp[i][mask]);
            add(dp[i + 1][mask & a[i]], dp[i][mask]);
        }
    }
    ll ans = 0;
    for (int mask = 0; mask < (1 << 6); mask++) {
        if (__builtin_popcount(mask) == k) {
            add(ans, dp[n][mask]);
        }
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