/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/problemset/problem/1036/C
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

#define N 20
ll dp[N][2][4];
string L, R;
void pre_compute() {
    
}
ll get(string &s) {
    int n = s.size();
    for (int i = 0; i <= n; i++)
        for (int smaller = 0; smaller < 2; smaller++)
            for (int cnt = 0; cnt <= 3; cnt++)
                dp[i][smaller][cnt] = 0;
    dp[0][0][0] = 1;
    for (int i = 0; i < n; i++)
        for (int smaller = 0; smaller < 2; smaller++)
            for (int cnt = 0; cnt <= 3; cnt++) if (dp[i][smaller][cnt]) {
                int upper = smaller ? 9 : s[i] - '0';
                for (int j = 0; j <= upper; j++) {
                    int next_smaller = smaller | (j < s[i] - '0');
                    int next_cnt = cnt + (j != 0);
                    if (next_cnt <= 3)
                        dp[i + 1][next_smaller][next_cnt] += dp[i][smaller][cnt];
                    else
                        break;
                }
            }
    ll ans = 0;
    for (int cnt = 0; cnt <= 3; cnt++) ans += dp[n][0][cnt] + dp[n][1][cnt];
    return ans;
}
bool is_classy(string &s) {
    int cnt = 0;
    for (auto c : s) if (c != '0') cnt++;
    return cnt <= 3;
}
void solve() {
    cin >> L >> R;
    ll res = get(R);
    res -= get(L);
    if (is_classy(L)) res += 1;
    cout << res << nline;
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