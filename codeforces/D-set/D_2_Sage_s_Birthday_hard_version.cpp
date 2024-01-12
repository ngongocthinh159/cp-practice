/**
 * Solution for: https://codeforces.com/problemset/problem/1419/D2
*/

#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
int n;
int a[N];
bool check(int x) {
    int i = n - 1, j = x - 1;
    bool res = true;
    while (j >= 0) {
        res = res && (a[i - 1] > a[j] && a[i] > a[j]);
        i--; j--; 
    }
    return res;
}
void solve() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a, a + n);
    int l = 1, r = (n + 1)/2 - 1;
    int ans = 0;
    while (l <= r) {
        int m = l + (r - l)/2;
        if (check(m)) {
            ans = m;
            l = m + 1;
        } else
            r = m - 1;
    }
    cout << ans << "\n";
    int j = ans - 1, i = n - 1;
    for (int k = 0; k < n; k++) {
        if (k % 2 == 0 || j == -1) cout << a[i--] << " ";
        else cout << a[j--] << " ";
    }
}

int main() {
    solve();
    return 0;
}
