/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=100
*/
#include <bits/stdc++.h>
using namespace std;

string s, t;
string get_s(int x) {
    string res = x <= 9 ? "0" : "";
    res += to_string(x);
    return res;
}
void solve() {
    cin >> t;
    int n = s.size(), m = t.size();
    s = " " + s;
    t = " " + t;
    vector<vector<int>> dp(n + 1, vector<int>(m + 1));
    for (int i = 0; i <= n; i++) dp[i][0] = i;
    for (int j = 0; j <= m; j++) dp[0][j] = j;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            if (s[i] == t[j])
                dp[i][j] = dp[i - 1][j - 1];
            else {
                dp[i][j] = 1 + min(dp[i][j - 1],
                                   min(dp[i - 1][j], dp[i - 1][j - 1]));
            }
        }
    int i = n, j = m;
    vector<pair<char, pair<char, int>>> v;
    while (i != 0 && j != 0) {
        if (s[i] == t[j]) {
            i--;
            j--;
            continue;
        }
        char oper, c;
        int pos;
        if (dp[i][j] == dp[i - 1][j - 1] + 1) {
            oper = 'C';
            c = t[j];
            pos = i;
            i--;
            j--;
        } else if (dp[i][j] == dp[i - 1][j] + 1) {
            oper = 'D';
            c = s[i];
            pos = i;
            i--;
        } else if (dp[i][j] == dp[i][j - 1] + 1) {
            oper = 'I';
            c = t[j];
            pos = i + 1;
            j--;
        }
        v.push_back({oper, {c, pos}});
    }
    while (i > 0) v.push_back({'D', {s[i], i}}), i--;
    while (j > 0) v.push_back({'I', {t[j], 1}}), j--;
    string res = "";
    for (auto &p : v) {
        res += p.first;
        res += p.second.first;
        res += get_s(p.second.second);
    }
    res += 'E';
    cout << res << "\n";
}
int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#ifndef ONLINE_JUDGE
    freopen("Input.txt", "r", stdin);
    freopen("Output.txt", "w", stdout);
#endif

    while (1) {
        cin >> s;
        if (s == "#") break;
        solve();
    }
    return 0;
}
