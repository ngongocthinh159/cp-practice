/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/contest/1879/problem/D
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

#define N 300005
int n;
int a[N];
ll _2pow[N];
void pre_compute() {
    _2pow[0] = 1;
    for (int i = 1; i < N; i++) _2pow[i] = _2pow[i - 1] * 2 % MOD1;
}
void add(int &x, int y) {
    x += y;
    if (x < 0) x += MOD1;
    if (x >= MOD1) x -= MOD1;
}
int mul(int x, int y) {
    int res = 1LL * x * y % MOD1;
    return res;
}
void solve() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int ans = 0;

    for (int bit = 30; bit >= 0; bit--) {
        int cnt[2]{};
        int sum[2]{};
        add(cnt[0], 1);
        add(sum[0], -1);
        int cur = 0;
        for (int i = 0; i < n; i++) {
            int x = (a[i] >> bit) & 1;
            cur ^= x;

            int tmp = mul(cnt[cur ^ 1], i);
            add(tmp, - sum[cur ^ 1]);
            add(ans, mul(_2pow[bit], tmp));

            cnt[cur]++;
            add(sum[cur], i);
        }
    }
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