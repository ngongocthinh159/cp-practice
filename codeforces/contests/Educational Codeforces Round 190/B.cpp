/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/contest/2230/problem/B
*/

// #include<bits/stdc++.h>
#include "bits/stdc++.h"
using namespace std;

#define nline '\n'
#define ll long long
#define MOD 1000000007
#define MOD1 998244353
#define LINF ((long long)1e18)
#define IINF ((int)1e9)
#define MASK(i) (1LL << (i))
#define all(v) (v).begin(), (v).end()


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

#define N 300005
int n;
int dp[N][8];
void pre_compute() {
    
}
int dfs(int i, int mask, string &t) {
    if (i == n) return 0;
    if (dp[i][mask] != -1) return dp[i][mask];

    int res = dfs(i + 1, mask, t);

    int idx;
    if (t[i] == '2' || t[i] == '6') idx = 1;
    else if (t[i] == '0') idx = 2;
    else idx = 0;
    int nmask = mask | (1 << idx);

    bool ok = true;
    int a = (nmask >> 0) & 1;
    int b = (nmask >> 1) & 1;
    int c = (nmask >> 2) & 1;
    if (a && idx == 1) ok = false;
    if (b && idx == 2) ok = false;
    if (ok) res = max(res, 1 + dfs(i + 1, nmask, t));

    return dp[i][mask] = res;
}
void solve() {
    string s; cin >> s;
    string t = "";
    int cnt = 0;
    for (auto c : s) {
        if (c != '4' && c != '8') t += c;
        else cnt++;
    }
    n = int(t.size());
    for (int i = 0; i < n; i++)
        for (int mask = 0; mask < 8; mask++) dp[i][mask] = -1;
    cout << (n - dfs(0, 0, t)) + cnt << nline;
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