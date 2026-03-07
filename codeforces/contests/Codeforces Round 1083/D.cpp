/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/contest/2205/problem/D
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

#define N 500005
#define LOG 19
#define RELAX(x,y) (a[(x)] > a[(y)] ? (x) : (y))
int n;
int a[N];
int par[LOG][N];
void pre_compute() {
    
}
int query(int l, int r) {
    int msb = 32 - __builtin_clz(r - l + 1) - 1;
    return RELAX(par[msb][l], par[msb][r - MASK(msb) + 1]);
}
int dfs(int l, int r) {
    if (l > r) return 0;
    int idx = query(l, r);
    if (idx == l) return dfs(l + 1, r);
    if (idx == r) return dfs(l, r - 1);
    return min(dfs(l, idx - 1) + r - idx, dfs(idx + 1, r) + idx - l);
}
void solve() {
    cin >> n;
    for (int i= 0; i < n;i ++) cin >> a[i], par[0][i] = i;
    for (int j = 1; j < LOG; j ++)
        for (int i = 0; i + MASK(j) - 1 < n; i++)
            par[j][i] = RELAX(par[j - 1][i], par[j - 1][i + MASK(j - 1)]);
    cout << dfs(0, n - 1) << nline;
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