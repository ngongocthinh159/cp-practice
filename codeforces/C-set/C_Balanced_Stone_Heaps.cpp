/**
 * Solution for: https://codeforces.com/problemset/problem/1623/C
*/

#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;
int n;
int h[N];
bool check(int x) {
    int a[n];
    for (int i = 0; i < n; i++) 
        a[i] = h[i];
    for (int i = n - 1; i >= 2; i--) {
        if (a[i] < x) return false;
        int canMove = min(a[i] - x, h[i]);
        int d = canMove / 3;
        a[i - 1] += d;
        a[i - 2] += 2*d;
    }
    return a[0] >= x && a[1] >= x;
}
void solve() {
    cin >> n;
    int l = 0, r = INT_MIN;
    for (int i = 0; i < n; i++) {
        cin >> h[i];
        r = max(r, h[i]);
    }
    int ans = 0;
    while (l <= r) {
        int m = l + (r - l)/2;
        if (check(m)) {
            ans = m;
            l = m + 1;
        } else {
            r = m - 1;
        }
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