/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/problemset/problem/2050/F
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
#define LOG 19
#define MASK(x) (1 << (x))
int n, q;
int a[N], rmq[LOG + 1][N], L[N];
void pre_compute() {

}
int query(int l, int r) {
    int msb = 32 - __builtin_clz(r - l) - 1;
    return __gcd(rmq[msb][l], rmq[msb][r - MASK(msb)]);
}
void solve() {
    cin >> n >> q;
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0, l = 0; i < n; i++) {
        if (a[l] != a[i]) l = i;
        L[i] = l;
        if (i + 1 < n) rmq[0][i] = abs(a[i] - a[i + 1]);
    }
    for (int j = 1; j <= LOG; j++) 
        for (int i = 0; i + MASK(j) < n; i++)
            rmq[j][i] = __gcd(rmq[j - 1][i], rmq[j - 1][i + MASK(j - 1)]);
    for (int i = 0; i < q; i++) {
        int l, r; cin >> l >> r;
        l--, r--;
        if (l == r || L[r] <= l)
            cout << 0 << ' ';
        else
            cout << query(l, r) << ' ';
    }
    cout << nline;
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