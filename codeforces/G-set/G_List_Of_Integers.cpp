/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/problemset/problem/920/G
*/

#include <bits/stdc++.h>
using namespace std;

#define MAXN 1000005
int spf[MAXN], factors[15];
int x, p, k, top;
void pre_compute() {
    for (int i = 1; i < MAXN; i++)
        spf[i] = i;
    for (int i = 2; i * i < MAXN; i++) {
        if (spf[i] == i) {
            for (int j = i * i; j < MAXN; j += i) {
                spf[j] = min(spf[j], i);
            }
        }
    }
}
void factorize(int k) {
    top = 0;
    while (k != 1) {
        int fact = spf[k];
        factors[top++] = fact;
        while (k % fact == 0) k /= fact;
    }
}
int f(int x) {
    int res = x;
    for (int mask = 1; mask < (1 << top); mask++) {
        int cur = 1;
        for (int bit = 0; bit < top; bit++)
            if ((mask >> bit) & 1) {
                cur *= factors[bit];
            }
        int sign = __builtin_popcount(mask) & 1 ? -1 : 1;
        res += sign * x / cur;
    }
    return res;
}
void solve() {
    cin >> x >> p >> k;
    factorize(p);
    int base = f(x);
    int l = x, r = 1e9;
    while (r - l > 1) {
        int m = l + (r - l) / 2;
        if (f(m) - base >= k)
            r = m;
        else
            l = m;
    }
    cout << r << "\n";
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
    int T;
    cin >> T;
    while (T--)
        solve();
    return 0;
}
