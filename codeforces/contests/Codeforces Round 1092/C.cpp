/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/contest/2216/problem/C
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
void solve() {
    int n, k, p, q; cin >> n >> k >> p >> q;
    int a[n + 1], b[n + 1], c[n + 1];
    ll pb[n + 1]{}, sufb[n + 2]{};
    ll pc[n + 1]{}, sufc[n + 2]{};
    ll pmn[n + 1]{}, smn[n + 2]{};
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) {
        b[i] = a[i] % p;
        c[i] = a[i] % q % p;

        pb[i] = pb[i - 1] + b[i];
        pc[i] = pc[i - 1] + c[i];
        pmn[i] = pmn[i - 1] + min(b[i], c[i]);
    }
    for (int i = n; i >= 1; i--) {
        sufb[i] = sufb[i + 1] + b[i];
        sufc[i] = sufc[i + 1] + c[i];
        smn[i] = smn[i + 1] + min(b[i], c[i]);
    }
    ll res = LINF;
    for (int i = k; i <= n; i++) {
        ll w = min(pb[i] - pb[i - k], pc[i] - pc[i - k]);
        res = min(res, w + pmn[i - k] + smn[i + 1]);
    }
    cout << res << nline;
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