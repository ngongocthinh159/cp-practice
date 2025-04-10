/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/contest/1516/problem/D
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

#define N 100005
int n, q, top;
int a[N], spf[N], buf[N];
void pre_compute() {
    for (int i = 1; i < N; i++) spf[i] = i;
    for (int i = 2; i * i < N; i++) if (spf[i] == i)
        for (int j = i * i; j < N; j += i) 
            spf[j] = min(spf[j], i);
}
void factorize(int x) {
    top = 0;
    while (x != 1) {
        int fact = spf[x];
        while (x % fact == 0) x /= fact;
        buf[top++] = fact;
    }
}
void solve() {
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> a[i];
    int msb = 32 - __builtin_clz(n) - 1;
    vector<vector<int>> par(msb + 1, vector<int>(n + 1));
    unordered_map<int,int> freq;
    int cnt = 0;
    for (int r = 1, l = 1; r <= n; r++) {
        factorize(a[r]);
        for (int i = 0; i < top; i++) if (++freq[buf[i]] == 2) cnt++;
        while (l < r && cnt >= 1) {
            factorize(a[l]);
            for (int i = 0; i < top; i++) if (--freq[buf[i]] == 1) cnt--;
            l++;
        }
        par[0][r] = l - 1;
    }
    for (int j = 1; j <= msb; j++)
        for (int i = 1; i <= n; i++)
            par[j][i] = par[j - 1][par[j - 1][i]];
    for (int i = 0; i < q; i++) {
        int l, r; cin >> l >> r;
        int u = r, segment = 0;
        for (int j = msb; j >= 0; j--) {
            if (par[j][u] >= l) {
                u = par[j][u];
                segment += (1 << j);
            }
        }
        segment++;
        cout << segment << nline;
    }
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