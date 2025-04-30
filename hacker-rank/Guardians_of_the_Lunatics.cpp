/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://www.hackerrank.com/contests/ioi-2014-practice-contest-2/challenges/guardians-lunatics-ioi14/problem
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


#define MAXL 8005
int L, G, c[MAXL];
ll pref[MAXL];
vector<ll> ndp, dp;
void pre_compute() {
    
}
ll C(int i, int j) {
    return 1LL * (pref[j + 1] - pref[i]) * (j - i + 1);
}
void compute(int l, int r, int optl, int optr) {
    if (l > r) return;

    int mid = (r + l) >> 1;
    pair<ll,int> best = {LINF, -1};

    for (int k = optl; k <= min(mid, optr); k++) {
        best = min(best, {dp[k - 1] + C(k, mid), k});
    }

    ndp[mid] = best.first;
    int opt = best.second;

    compute(l, mid - 1, optl, opt);
    compute(mid + 1, r, opt, optr);
}
void solve() {
    cin >> L >> G;
    for (int i = 1; i <= L; i++) cin >> c[i], pref[i + 1] = pref[i] + c[i];
    ndp.resize(L + 1);
    dp.resize(L + 1);
    for (int i = 1; i <= L; i++) dp[i] = C(1, i);
    for (int i = 2; i <= G; i++) {
        compute(1, L, 1, L);
        swap(dp, ndp);
    }
    cout << dp[L] << nline;
}

int main() {
    fastio();
    IN_OUT();
    int T = 1;
    // cin >> T;
    pre_compute();
    for (int cases = 1; cases <= T; cases++) {

        solve();
    }
    return 0;
}