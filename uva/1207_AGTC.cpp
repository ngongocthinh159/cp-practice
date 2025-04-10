/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3648
*/

#include <bits/stdc++.h>
using namespace std;

int n, m;
string s, t;
void solve() {
    cin >> s >> m >> t;
    s = " " + s;
    t = " " + t;
    vector<vector<int>> dp(n + 1, vector<int>(m + 1));
    for (int i = 0; i <= n; i++) dp[i][0] = i;
    for (int i = 0; i <= m; i++) dp[0][i] = i;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            if (s[i] == t[j])
                dp[i][j] = dp[i - 1][j - 1];
            else
                dp[i][j] = 1 + min(dp[i - 1][j],
                                   min(dp[i - 1][j - 1], dp[i][j - 1]));
        }
    cout << dp[n][m] << '\n';
}
int main() {
    while (cin >> n)
        solve();
    return 0;
}