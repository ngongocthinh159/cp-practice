// https://codeforces.com/contest/768/problem/D
// MAXN: https://en.wikipedia.org/wiki/Coupon_collector%27s_problem

#include <bits/stdc++.h>
using namespace std;

#define MAXK 1005
#define MAXN 10005
int k, q, p;
double dp[MAXK][MAXN];
void pre_compute() {
    
}
void solve() {
    cin >> k >> q;
    dp[0][0] = 1;
    for (int j = 1; j < MAXK; j++)
        for (int i = 1; i < MAXN; i++)
            dp[j][i] = 1.00 * j / k * dp[j][i - 1] + 1.00 * (k - j + 1) / k * dp[j - 1][i - 1];
    for (int i = 0; i < q; i++) {
        cin >> p;
        double target = 1.00 * p / 2000;
        auto it = lower_bound(dp[k], dp[k] + MAXN, target);
        cout << (it - dp[k]) << "\n";
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
#ifndef ONLINE_JUDGE
    freopen("Input.txt", "r", stdin);
    freopen("Output.txt", "w", stdout);
#endif

    pre_compute();
    solve();
    return 0;
}
