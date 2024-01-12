/*
    Solution for: https://codeforces.com/contest/1873/problem/F
*/

#include <bits/stdc++.h>
using namespace std;

const int N = 2*1e5;
int a[N + 5], h[N + 5];
int n, k;

void solve() {
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> h[i];
    }
    int l = 0, r = 0;
    int sum = 0;
    int ans = 0;
    while (r < n) {
        sum += a[r];

        // re-validate window
        while (l <= r && sum > k) {
            sum -= a[l++];
        }
        if (r - l + 1 >= 2 && h[r - 1] % h[r] != 0) {
            l = r; sum = a[r];
        }

        // valid window
        if (r - l + 1 >= 1) {
            ans = max(ans, r - l + 1);
        }

        r++;        
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int cases; cin >> cases;
    while (cases--) {
        solve();
    }
    return 0;
}

