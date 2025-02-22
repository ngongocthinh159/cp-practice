/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://www.spoj.com/problems/MSKYCODE/vn/
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define MAXN 10005
int n, cnt[MAXN], a[MAXN];
ll dp[MAXN];
void pre_compute() {
}
ll _4Cn(int n) {
    if (n < 4) return 0;
    return 1LL * n * (n - 1) * (n - 2) * (n - 3) / (1 * 2 * 3 * 4);
}
void solve() {
    memset(cnt, 0, sizeof cnt);
    memset(dp, 0, sizeof dp);
    int mx = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        cnt[a[i]]++;
        mx = max(mx, a[i]);
    }
    for (int i = mx; i >= 1; i--) {
        ll cur = 0;
        for (int j = i; j <= mx; j += i) {
            cur += cnt[j];
            dp[i] -= dp[j];
        }
        dp[i] += _4Cn(cur);
    }
    cout << dp[1] << "\n";
}
int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#ifndef ONLINE_JUDGE
    freopen("Input.txt", "r", stdin);
    freopen("Output.txt", "w", stdout);
#endif

    pre_compute();
    while (cin >> n) {
        solve();
    }
    return 0;
}
