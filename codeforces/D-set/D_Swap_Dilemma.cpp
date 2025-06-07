/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/problemset/problem/1983/D
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
int n;
int a[N], b[N], buf[N], orderA[N], orderB[N];
void pre_compute() {
    
}
int merge(int l, int r, int *a) {
    int m = (l + r)/2;
    int i = l, j = m + 1, k = l;
    int inverses = 0;
    while (i <= m && j <= r) {
        if (a[i] <= a[j]) {
            inverses += (j - m + 1);
            buf[k++] = a[i++];
        } else {
            buf[k++] = a[j++];
        }
    }
    while (i <= m) {
        inverses += (j - m + 1);
        buf[k++] = a[i++];
    }
    while (j <= r) buf[k++] = a[j++]; 
    for (int i = l; i <= r; i++) a[i] = buf[i];
    return inverses;
}
int dfs(int l, int r, int *a) {
    if (l == r) return 0;
    int m = (l + r)/2;
    int lans = dfs(l, m, a);
    int rans = dfs(m + 1, r, a);
    int merge_ans = merge(l, r, a);
    return lans + rans + merge_ans;
}
int cnt_inversions(int *a) {
    return dfs(0, n - 1, a);
}
void solve() {
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];
    iota(orderA, orderA + n, 0);
    iota(orderB, orderB + n, 0);
    sort(orderA, orderA + n, [&](int i, int j) {
        return a[i] < a[j];
    });
    sort(orderB, orderB + n, [&](int i, int j) {
        return b[i] < b[j];
    });
    for (int i = 0; i < n; i++) if (a[orderA[i]] != b[orderB[i]]) {
        cout << "NO" << nline;
        return;
    }
    if ((cnt_inversions(a)&1) == (cnt_inversions(b)&1))
        cout << "YES" << nline;
    else
        cout << "NO" << nline;
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