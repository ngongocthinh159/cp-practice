/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/contest/2121/problem/E
*/

#include<bits/stdc++.h>
using namespace std;

#define nline '\n'
#define ll long long
#define MOD 1000000007
#define MOD1 998244353
#define LINF ((long long)1e18)
#define IINF ((int)1e9)
#define MASK(i) (1LL << (i))

template<class X, class Y>
bool minimize(X &x, const Y &y) {
    if (x > y) {
        x = y;
        return true;
    } else return false;
}
template<class X, class Y>
bool maximize(X &x, const Y &y) {
    if (x < y) {
        x = y;
        return true;
    } else return false;
}

#define fastio() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
void IN_OUT() {
#ifndef ONLINE_JUDGE
freopen("Input.txt", "r", stdin);
freopen("Output.txt", "w", stdout);
#endif
}
struct chash {static uint64_t splitmix64(uint64_t x) {x += 0x9e3779b97f4a7c15;x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;x = (x ^ (x >> 27)) * 0x94d049bb133111eb;return x ^ (x >> 31);}size_t operator()(uint64_t x) const {static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();return splitmix64(x + FIXED_RANDOM);}}; // https://codeforces.com/blog/entry/62393
struct chashp {static uint64_t splitmix64(uint64_t x) {x += 0x9e3779b97f4a7c15;x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;x = (x ^ (x >> 27)) * 0x94d049bb133111eb;return x ^ (x >> 31);}size_t operator()(pair<uint64_t,uint64_t> x) const {static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();return splitmix64(x.first + FIXED_RANDOM)^(splitmix64(x.second + FIXED_RANDOM) >> 1);}}; // https://codeforces.com/blog/entry/62393
/*--------------------------------------------------------------------------------------------------------------------------*/


#define N 15
int dp[N][2][2];
void pre_compute() {
    
}
int dfs(int i, bool smaller, bool larger, string &l, string &r) {
    if (i == (int) l.size())
        return 0;
    if (dp[i][smaller][larger] != -1) return dp[i][smaller][larger];

    int lower = larger ? 0 : l[i] - '0';
    int upper = smaller ? 9 : r[i] - '0';
    // cout << lower << ' ' << upper << '\n';
    int res = IINF;
    for (int j = lower; j <= upper; j++) {
        int cost = (j == (l[i] - '0')) + (j == (r[i] - '0'));
        res = min(res, cost + dfs(i + 1, smaller | (j < (r[i] - '0')), larger | (j > (l[i] - '0')), l, r));
    }
    return dp[i][smaller][larger] = res;
}
void solve() {
    int l, r ; 
    cin >> l >> r;
    string ls = to_string(l);
    string rs = to_string(r);
    int n = ls.size();
    // cout << ls << nline;
    // cout << rs << nline;
    for (int i = 0; i <= n; i++)
        for (int j = 0; j < 2; j++)
            for (int k = 0; k < 2; k++) dp[i][j][k] = -1;
    cout << dfs(0, 0, 0, ls, rs) << nline;
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