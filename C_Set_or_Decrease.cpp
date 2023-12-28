/**
 * Solution for: https://codeforces.com/problemset/problem/1622/C
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int N = 2e5 + 5;
ll n, k;
ll a[N];
ll pre[N];
bool check(ll x) {
    ll sum = INT_MAX;
    for (int i = 1; i <= min(x, n - 1); i++) {
        int mn = a[0] - (x - i);
        sum = min(sum, )
    }
    return sum <= k;
}
void solve() {
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a, a + n);
    for (int i = 0; i < n; i++) {
        pre[i] = i == 0 ? a[i] : a[i] + pre[i - 1];
    }
    ll l = 0, r = 1e15;
    ll ans = -1;
    while (l <= r) {
        ll m = l + (r - l)/2;
        if (check(m)) {
            ans = m;
            r = m - 1;
        } else
            l = m + 1;
    }
    cout << ans << "\n";
}

int main() {
    int cases; cin >> cases;
    while (cases--) {
        solve();
    }
    return 0;
}