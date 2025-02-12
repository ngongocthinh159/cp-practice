/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/problemset/problem/300/C
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define MAX 1000005
#define MOD 1000000007

ll a, b, n, fact[MAX], ifact[MAX];
ll expo(ll a, ll b, ll mod) {
    if (a == 0) return 1 % mod;
    ll res = 1;
    while (b > 0) {
        if (b & 1) res = (res * a) % mod;
        a = (a * a) % mod;
        b = b >> 1;
    }
    return res;
}
ll extended_gcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll x1, y1;
    ll g = extended_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - a / b * y1;
    return g;
}
void pre_compute() {
    fact[0] = 1;
    for (int i = 1; i < MAX; i++) fact[i] = fact[i - 1] * i % MOD;
    ifact[MAX - 1] = expo(fact[MAX - 1], MOD - 2, MOD);
    for (int i = MAX - 2; i >= 0; i--) ifact[i] = ifact[i + 1] * (i + 1) % MOD;
}
ll nCk(ll n, ll k) {
    return fact[n] * ifact[k] % MOD * ifact[n - k] % MOD;
}
bool check_digit(ll sum, int a, int b) {
    while (sum) {
        if (!(sum % 10 == a || sum % 10 == b)) return false;
        sum /= 10;
    }
    return true;
}
void solve() {
    cin >> a >> b >> n;
    ll x0, y0;
    ll g = extended_gcd(a, b, x0, y0);
    ll mxSum = 9*n, k, x, y, c;
    ll ans = 0;
    for (ll sum = 1; sum <= mxSum; sum++) {
        if (!check_digit(sum, a, b)) continue;
        if (sum % g) continue;

        c = sum;
        k = n * g - c * (x0 + y0);
        if (k % (b - a) == 0) {
            k /= (b - a);
            x = x0 * c / g + k * b / g;
            y = y0 * c / g - k * a / g;
            if (0 <= x && x <= n) ans = (ans + nCk(n, x)) % MOD;
        }
    }
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#ifndef ONLINE_JUDGE
    freopen("Input.txt", "r", stdin);
    freopen("Output.txt", "w", stdout);
#endif
    pre_compute();
    solve();
    return 0;
}
