/*
    Solution for: https://codeforces.com/contest/474/problem/B
*/

#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
int n, m, q;
int a[N];
int pre[N];
bool check(int m, int q) {
    return pre[m] >= q;
} 
void solve() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        pre[i] = i == 0 ? a[i] : a[i] + pre[i - 1];
    }
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> q;

        int l = 0, r = n - 1;
        int ans;
        while (l <= r) {
            int m = l + (r - l)/2;

            if (check(m, q)) {
                ans = m;
                r = m - 1;
            } else {
                l = m + 1;
            }
        }
        cout << ans + 1 << "\n";
    }
}

int main() {
    solve();
    return 0;
}