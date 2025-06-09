/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/problemset/problem/1826/D
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
ll a[N], pref[N], surf[N];

void pre_compute() {
    
}

void solve() {
    cin >> n;
    pref[0] = surf[n + 1] = INT_MIN;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        pref[i + 1] = max(pref[i], a[i] + i);
    }
    for (int i = n - 1; i >= 0; i--) {
        surf[i + 1] = max(surf[i + 2], a[i] - i);
    }
    ll ans = INT_MIN;
    for (int i = 1; i < n - 1; i++) {
        ans = max(ans, a[i] + pref[i] + surf[i + 2]);
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