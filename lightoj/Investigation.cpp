/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://lightoj.com/problem/investigation
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

#define N 12
#define K 95
ll dp[N][2][K][K], _10powmod[N];
int a, b, k;
void pre_compute() {
    
}
ll find(int x) {
    string s = to_string(x);
    int n = s.size();
    for (int i = 0; i <= n; i++)
        for (int smaller = 0; smaller < 2; smaller++)
            for (int d_mod = 0; d_mod < k; d_mod++)
                for (int num_mod = 0; num_mod < k; num_mod++)
                    dp[i][smaller][d_mod][num_mod] = 0;
    dp[0][0][0][0] = 1;
    for (int i = 0; i < n; i++)
        for (int smaller = 0; smaller < 2; smaller++)
            for (int d_mod = 0; d_mod < k; d_mod++)
                for (int num_mod = 0; num_mod < k; num_mod++) if (dp[i][smaller][d_mod][num_mod]) {
                    int upper = smaller ? 9 : s[i] - '0';
                    for (int j = 0; j <= upper; j++) {
                        int nsmaller = smaller | (j < s[i] - '0');
                        int nd_mod = (d_mod + j) % k;
                        int nnum_mod = (num_mod + _10powmod[n - (i + 1)] * j % k) % k;
                        dp[i + 1][nsmaller][nd_mod][nnum_mod] += dp[i][smaller][d_mod][num_mod];
                    }
                }
    ll ans = dp[n][0][0][0] + dp[n][1][0][0];
    return ans;
}
void solve() {
    cin >> a >> b >> k;
    if (k >= K) {
        cout << 0 << nline;
        return;
    }
    _10powmod[0] = 1%k;
    for (int i = 1; i < N; i++) _10powmod[i] = _10powmod[i - 1] * 10 % k;
    a--;
    ll res = find(b) - find(a);
    cout << res << nline;
}

int main() {
    fastio();
    IN_OUT();
    int T = 1;
    cin >> T;
    pre_compute();
    for (int cases = 1; cases <= T; cases++) {
        cout << "Case " << cases << ": ";
        solve();
    }
    return 0;
}