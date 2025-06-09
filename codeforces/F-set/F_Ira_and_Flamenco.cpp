/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/problemset/problem/1833/F
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

#define N 200005
int n, m;
int a[N], buf[N], cnt[N], inv[N];

ll expo(ll a, ll b) {
    ll res = 1;
    ll cur = a;
    while (b) {
        if (b&1)
            res = res * cur % MOD;
        cur = cur * cur % MOD;
        b >>= 1;
    }
    return res;
}
void pre_compute() {
    for (int i = 1; i < N; i++)
        inv[i] = expo(i, MOD - 2);
}
void solve() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    if (m == 1) {
        cout << n << nline;
        return;
    }
    sort(a, a + n);
    int top = 0;
    for (int i = 0; i < n;) {
        int x = a[i], _cnt = 0;
        while (i < n && x == a[i]) {
            _cnt++; 
            i++;
        }
        buf[top] = x;
        cnt[top++] = _cnt;
    }
    ll mul = cnt[0];
    ll ans = 0;
    for (int r = 1, l = 0; r < top; r++) {
        if (buf[r] - buf[r - 1] > 1) {
            l = r;
            mul = cnt[r];
        } else {
            mul = mul * cnt[r] % MOD;
        }
        while (r - l + 1 > m) {
            mul = mul * inv[cnt[l++]] % MOD;
        }
        if (r - l + 1 == m) {
            ans += mul;
            if (ans >= MOD) ans -= MOD;
        }
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