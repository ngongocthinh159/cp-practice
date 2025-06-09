/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/contest/2117/problem/D
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
int a[N];
void pre_compute() {
    
}
void solve() {
    cin >> n;
    for (int i = 1; i <= n ;i++) {
        cin >> a[i];
    }
    bool found = false;
    pair<ll, ll> last;
    for (int i = 2; i <= n; i++) {
        ll a1 = 1;
        ll b1 = n - 1 + 1;
        ll c1 = -a[1];
        ll a2 = i;
        ll b2 = n - i + 1;
        ll c2 = -a[i];
        ll d = a1*b2 - a2*b1;
        ll dx = b1*c2 - b2*c1;
        ll dy = c1*a2 - c2*a1;
        if (d != 0) {
            if (dx % d != 0 || dy % d != 0) {
                cout << "NO" << nline;
                return;
            }
            ll x = dx/d;
            ll y = dy/d;
            if (x < 0 || y < 0) {
                cout << "NO" << nline;
                return;
            }
            if (found) {
                if (last.first != x || last.second != y) {
                    cout << "NO" << nline;
                    return;
                }
            } else {
                last.first = x;
                last.second = y;
            }
            found = true;
        }
    }
    cout << "YES" << nline;
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