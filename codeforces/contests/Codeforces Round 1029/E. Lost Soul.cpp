/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/contest/2117/problem/E
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
int n;
int a[N], b[N], idxa[N][2], idxb[N][2];
void pre_compute() {
    
}
void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++)
        idxa[i][0] = idxa[i][1] = idxb[i][0] = idxb[i][1] = -1;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    for (int i = n - 1; i >= 0; i--) {
        if (a[i] == b[i]) {
            cout << i+1 << nline;
            return;
        }
        
        int par = i&1;
        bool ok = false;
        if (idxa[a[i]][par^1] != -1 || idxa[a[i]][par] != -1) {
            ok = true;
        }
        if (idxb[a[i]][par^1] != -1 && idxb[a[i]][par^1] - i > 1) {
            ok = true;
        }
        if (idxb[a[i]][par] != -1) {
            ok = true;
        }

        if (idxb[b[i]][par^1] != -1 || idxb[b[i]][par] != -1) {
            ok = true;
        }
        if (idxa[b[i]][par^1] != -1 && idxa[b[i]][par^1] - i > 1) {
            ok = true;
        }
        if (idxa[b[i]][par] != -1) {
            ok = true;
        }

        if (ok) {
            cout << i + 1 << nline;
            return;
        }

        if (idxa[a[i]][i&1] == -1)
            idxa[a[i]][i&1] = i;
        if (idxb[b[i]][i&1] == -1)
            idxb[b[i]][i&1] = i;
    }
    cout << 0 << nline;
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