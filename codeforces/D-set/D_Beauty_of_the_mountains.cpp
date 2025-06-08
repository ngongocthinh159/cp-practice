/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/problemset/problem/1982/D
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

#define N 505
int n, m, k;
int mat[N][N];
ll pref[N][N];
void pre_compute() {
    
}
ll query(int x1, int y1, int x2, int y2) {
    return pref[x2 + 1][y2 + 1] - pref[x2 + 1][y1] - pref[x1][y2 + 1] + pref[x1][y1];
}
void solve() {
    cin >> n >> m >> k;
    ll cap_sum = 0, nocap_sum = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> mat[i][j];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            char c; cin >> c;
            int x = c - '0';
            pref[i + 1][j + 1] = pref[i + 1][j] + pref[i][j + 1] - pref[i][j] + x;
            if (x)
                cap_sum += mat[i][j];
            else
                nocap_sum += mat[i][j];
        }
    ll dif = abs(cap_sum - nocap_sum);
    if (dif == 0) {
        cout << "YES" << nline;
        return;
    }
    int cur_gcd = -1;
    for (int i = 0; i <= n - k; i++)
        for (int j = 0; j <= m - k; j++) {
            int cap_cells = query(i, j, i + k - 1, j + k - 1);
            int cell_diffs = abs(2*cap_cells - k * k);
            if (cell_diffs) {
                if (cur_gcd == -1) cur_gcd = cell_diffs;
                cur_gcd = __gcd(cur_gcd, cell_diffs);
            }
        }
    if (cur_gcd == -1 || dif % cur_gcd != 0)
        cout << "NO" << nline;
    else
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