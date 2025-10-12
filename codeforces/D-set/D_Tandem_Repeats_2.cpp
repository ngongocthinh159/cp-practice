/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/contest/1948/problem/D
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

void pre_compute() {
    
}
void solve() {
    string s;
    cin >> s;
    int n = s.size();
    int ans = 0;
    vector<vector<int>> dp(n, vector<int>(n + 1));
    for (int i = n - 1; i >= 0; i--)
        for (int j = n - 1; j >= i + 1; j--) {
            if (s[i] == s[j] || s[i] == '?' || s[j] == '?') {
                dp[i][j] = dp[i + 1][j + 1] + 1;
            }
        }
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++) {
            if (dp[i][j] >= j - i) ans = max(ans, 2*(j - i));
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
