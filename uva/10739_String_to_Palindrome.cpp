/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1680
 */

#include <bits/stdc++.h>
using namespace std;

string s;
void solve() {
    cin >> s;
    int n = s.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));
    for (int l = 0; l + 1 < n; l++) {
        dp[l][l + 1] = !(s[l] == s[l + 1]);
    }
    for (int len = 3; len <= n; len++)
        for (int l = 0; l + len - 1 < n; l++) {
            int r = l + len - 1;
            if (s[l] == s[r])
                dp[l][r] = dp[l + 1][r - 1];
            else
                dp[l][r] = 1 + min(dp[l + 1][r],
                                   min(dp[l][r - 1], dp[l + 1][r - 1]));
        }
    cout << dp[0][n - 1] << '\n';
}
int main() {
    int T;
    cin >> T;
    for (int i = 1; i <= T; i++) {
        cout << "Case " << i << ": ";
        solve();
    }
    return 0;
}