/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://szkopul.edu.pl/problemset/problem/ovRIpLFK3IhyFPjnVXeZtGxH/site/?key=statement
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

#define N 20005
int n, w[N], d[N];
ll surf_w[N], surf_d[N], surf_c[N];
vector<int> dp, ndp;

void pre_compute() {
    
}
ll cost(int l, int r) {
    if (l > r) return 0;
    return surf_c[l + 1] - surf_c[r + 2] - (surf_w[l + 1] - surf_w[r + 2]) * surf_d[r + 1];
}
void compute(int l, int r, int optl, int optr) {
    if (l > r) return;
    
    int mid = l + r >> 1;
    pair<int,int> best = {2e9 + 5, -1};
    
    for (int k = optl; k <= min(optr, mid); k++) {
        best = min(best, {dp[k - 1] + cost(k, mid), k});
    }
    
    ndp[mid] = best.first;
    int opt = best.second;
    
    compute(l, mid - 1, optl, opt);
    compute(mid + 1, r, opt, optr);
}
void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> w[i] >> d[i];
    }
    for (int i = n; i >= 1; i--) {
        surf_w[i + 1] = surf_w[i + 2] + w[i];
        surf_d[i + 1] = surf_d[i + 2] + d[i];
        surf_c[i + 1] = surf_c[i + 2] + w[i] * surf_d[i + 1];
    }
    dp.resize(n + 2);
    ndp.resize(n + 2);
    for (int i = 1; i <= n + 1; i++) {
        dp[i] = cost(1, i);
    }
    for (int i = 2; i <= 3; i++) {
        compute(1, n + 1, 1, n + 1);
        swap(dp, ndp);
    }
    cout << dp[n + 1] << nline;
}

int main() {
    fastio();
    // IN_OUT();
    int T = 1;
    // cin >> T;
    pre_compute();
    for (int cases = 1; cases <= T; cases++) {

        solve();
    }
    return 0;
}