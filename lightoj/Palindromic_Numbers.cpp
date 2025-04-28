/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://lightoj.com/problem/palindromic-numbers
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
ll l, r, dp[N][N][2];
void pre_compute() {
    
}
bool is_ok(string &s, ll x) {
    int n = s.size();
    int half = (n + 1)/2;
    string t = s.substr(0, half);
    ll X;
    if (n&1) {
        string rt = t.substr(0, half - 1);
        reverse(rt.begin(), rt.end());
        t += rt;
        X = stoll(t);
    } else {
        string rt = t;
        reverse(rt.begin(), rt.end());
        t += rt;
        X = stoll(t);
    }
    return X <= x;
}
ll get(ll x) {
    if (x == 0)
        return 1;
    string s = to_string(x);
    int n = s.size();
    for (int i = 0; i <= n; i++)
        for (int start_idx = 1; start_idx <= i + 1; start_idx++)
            for (int smaller = 0; smaller < 2; smaller++)
                    dp[i][start_idx][smaller] = 0;
    for (int start_idx = 1; start_idx <= n; start_idx++)
        dp[start_idx - 1][start_idx][start_idx == 1 ? 0 : 1] = 1;
    for (int i = 0; i < n; i++)
        for (int start_idx = 1; start_idx <= i + 1; start_idx++)
            for (int smaller = 0; smaller < 2; smaller++) if (dp[i][start_idx][smaller]) {
                if (start_idx != 1 && smaller == 0) continue;

                int len = n + 1 - start_idx;
                int half = (len + 1)/2;
                if (i + 1 <= start_idx + half - 1) {
                    int upper = smaller ? 9 : s[i] - '0';
                    for (int j = (i + 1 == start_idx ? 1 : 0); j <= upper; j++) {
                        int next_smaller = smaller | (j < s[i] - '0');
                        dp[i + 1][start_idx][next_smaller] += dp[i][start_idx][smaller];
                    }
                }
            }

    ll ans = 0;
    for (int start_idx = 1; start_idx <= n; start_idx++) {
        int len = n + 1 - start_idx;
        int half = (len + 1)/2;
        ans += dp[start_idx + half - 1][start_idx][1];
    }
    ans += is_ok(s, x);
    ans += 1;
    return ans;
}
void solve() {
    cin >> l >> r;
    if (l > r) swap(l, r);
    ll res = get(r);
    if (l > 0) {
        l--;
        res -= get(l);
    }
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
