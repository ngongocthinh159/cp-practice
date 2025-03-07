/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://vjudge.net/problem/UVA-10404/origin
*/

#include<bits/stdc++.h>
using namespace std;

#define fastio() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
void IN_OUT() {
#ifndef ONLINE_JUDGE
freopen("Input.txt", "r", stdin);
freopen("Output.txt", "w", stdout);
#endif
}
/*--------------------------------------------------------------------------------------------------------------------------*/

#define MAXN 1000005
#define MAXM 15
int n, m, a[MAXM];
bool dp[MAXN];
void solve() {
    cin >> m;
    for (int i = 0; i < m; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) {
        dp[i] = false;
        for (int j = 0; j < m; j++) if (i - a[j] >= 0 && dp[i - a[j]] == false) {
            dp[i] = true;
            break;
        }

    }
    if (dp[n]) 
        cout << "Stan wins" << "\n";
    else
        cout << "Ollie wins" << "\n";
}

int main() {
    fastio();
    IN_OUT();
    while (cin >> n)
        solve();
    return 0;
}