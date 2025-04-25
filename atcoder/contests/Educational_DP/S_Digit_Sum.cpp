/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://atcoder.jp/contests/dp/tasks/dp_s
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

#define N 10005
#define D 105
string s;
int d;
ll dp[N][2][D];
void pre_compute() {

}
void solve() {
    cin >> s >> d;
    int n = s.size();
    s = " " + s;
    dp[0][0][0] = 1;
    for (int i = 0; i < n; i++)
        for (int smaller = 0; smaller < 2; smaller++)
            for (int mod = 0; mod < d; mod++) if (dp[i][smaller][mod]) {
                int upper = smaller ? 9 : (s[i + 1] - '0');
                for (int j = 0; j <= upper; j++) {
                    int next_smaller = smaller | (j < (s[i + 1] - '0'));
                    int next_mod = (mod + j) % d;

                    dp[i + 1][next_smaller][next_mod] += dp[i][smaller][mod];
                    dp[i + 1][next_smaller][next_mod] %= MOD; 
                }
            }
    ll ans = 0;
    for (int smaller = 0; smaller < 2; smaller++)
        ans = (ans + dp[n][smaller][0]) % MOD;
    ans -= 1;
    if (ans < 0) ans += MOD;
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