/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/contest/55/problem/C
*/
#include <bits/stdc++.h>
using namespace std;

int n, m, k;
void solve() {
    cin >> n >> m >> k;
    bool found = false;
    for (int i = 0; i < k; i++) {
        int x, y; cin >> x >> y;
        x--, y--;
        if (x <= 4 || n - 1 - x <= 4 || y <= 4 || m - 1 - y <= 4)
            found = true;
    }
    if (found)
        cout << "YES" << "\n";
    else
        cout << "NO" << "\n";
}
int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    solve();
    return 0;
}
