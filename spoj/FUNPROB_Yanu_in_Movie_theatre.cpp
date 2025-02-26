/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://www.spoj.com/problems/FUNPROB/
*/
#include <bits/stdc++.h>
using namespace std;

int n, m;
void solve() {
    if (n > m) {
        printf("%lf\n", 0.000000);
        return;
    }
    printf("%lf\n", 1.00*(m - n + 1)/(m + 1));
}
int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#ifndef ONLINE_JUDGE
    freopen("Input.txt", "r", stdin);
    freopen("Output.txt", "w", stdout);
#endif
    while (true) {
        cin >> n >> m;
        if (!n && !m) break;
        solve();
    }
    return 0;
}
