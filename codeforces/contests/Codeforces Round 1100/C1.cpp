/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/contest/2229/problem/C1
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


void pre_compute() {
    
}
int p(int x) {
    if (x >= 0) return 1;
    return -1;
}
void solve() {
    int n; cin >> n;
    ll a[n + 1];
    for (int i = 1; i <= n; i++) cin >> a[i];

    vector<int> v;
    vector<int> parity;
    int lastidx = -1;
    for (int i = 1; i <= n;) {
        int curp = p(a[i]);
        int st = i, end = i;
        while (i <= n && p(a[i]) == curp) {
            end = i;
            i++;
        }
        v.push_back(end);
        if (curp == 1) lastidx = v.size() - 1;
    }
    cout << lastidx + 1 << nline;
    for (int i = lastidx; i >= 0; i--) {
        cout << v[i] << ' ';
    }
    cout << nline;

    // ll dp[n + 1][2]{};
    // array<ll,3> trace[n + 1][2]{};
    // for (int i = 1; i <= n; i++) {
    //     dp[i][0] = -a[i] + dp[i - 1][0];
    //     trace[i][0] = {i - 1, 1, 1};
    //     // if (minimize(dp[i][0], a[i] + dp[i - 1][0])) {
    //     //     trace[i][0] = {i - 1, 0, 0};
    //     // }
    //     // dp[i][1] = -a[i] + dp[i - 1][1];
    //     // trace[i][1] = {i - 1, 1, 0};
    //     // if (maximize(dp[i][1], a[i] + dp[i - 1][1])) {
    //     //     trace[i][1] = {i - 1, 1, 1};
    //     // }
    // }
    // // cout << dp[2][0] << nline;
    // // cout << dp[2][1] << nline;
    // // cout << dp[n][0] << nline;
    // vector<int> res;
    // int I = n, J = 0;
    // while (I != 0) {
    //     ll pI = trace[I][J][0];
    //     ll pJ = trace[I][J][1];
    //     ll choose = trace[I][J][2];

    //     if (choose) res.push_back(I);

    //     I = pI;
    //     J = pJ;
    // }
    // cout << int(res.size()) << nline;
    // for (auto x : res) cout << x << ' ';
    // cout << nline;
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