/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/contest/2230/problem/E
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
    int n, m;
    cin >> n;
    ll p[n + 1], c[n + 1];
    for (int i = 1; i <= n; i++) cin >> p[i];
    for (int i = 1; i <= n; i++) cin >> c[i];
    cin >> m;
    ll tp[m + 1], cp[m + 1], d[m + 1]; 
    for (int i = 1; i <= m; i++) cin >> tp[i];
    for (int i = 1; i <= m; i++) cin >> cp[i];
    for (int i = 1; i <= m; i++) cin >> d[i];

    vector<int> order1(n + 1);
    iota(all(order1), 0);
    sort(order1.begin() + 1, order1.end(), [&](int i, int  j) {
        return p[i] < p[j]; 
    });
    vector<int> order2(n + 1);
    iota(all(order2), 0);
    sort(order2.begin() + 1, order2.end(), [&](int i, int  j) {
        return c[i] < c[j]; 
    });

    vector<ll> p1(n + 1), s1(n + 1);
    vector<ll> p2(n + 1), s2(n + 1);
    for (int i = 1; i <= n; i++) {
        p1[i] = i - 1 >= 1 ? min(p1[i - 1], c[order1[i]]) : c[order1[i]];
        p2[i] = i - 1 >= 1 ? min(p2[i - 1], p[order2[i]]) : p[order2[i]];
    }
    for (int i = n; i >= 1; i--) {
        s1[i] = i + 1 <= n ? min(s1[i + 1], c[order1[i]]) : c[order1[i]];
        s2[i] = i + 1 <= n ? min(s2[i + 1], p[order2[i]]) : p[order2[i]];
    }
    auto getCap = [](ll x, ll t, ll d) -> ll {
        if (x < t) return 0;
        if (x >= t + d) return t + d;
        return x;
    };
    ll mn = LINF;
    for (int i = 1; i <= n; i++) mn = min(p[i] + c[i], mn); 
    for (int i = 1; i <= m; i++) {
        ll res = LINF;
        auto idx = lower_bound(order1.begin() + 1, order1.end(), tp[i], [&](int i, int target) {
            return p[i] < target;
        }) - order1.begin();
        idx--;
        if (idx >= 1) res = min(res, 0 + getCap(p1[idx], cp[i], d[i]));

        idx = lower_bound(order1.begin() + 1, order1.end(), tp[i] + d[i], [&](int i, int target) {
            return p[i] < target;
        }) - order1.begin();
        if (idx <= n) res = min(res, tp[i] + d[i] + getCap(s1[idx], cp[i], d[i]));

        idx = lower_bound(order2.begin() + 1, order2.end(), cp[i], [&](int i, int target) {
            return c[i] < target;
        }) - order2.begin();
        idx--;
        if (idx >= 1) res = min(res, 0 + getCap(p2[idx], tp[i], d[i]));

        idx = lower_bound(order2.begin() + 1, order2.end(), cp[i] + d[i], [&](int i, int target) {
            return c[i] < target;
        }) - order2.begin();
        if (idx <= n) res = min(res, cp[i] + d[i] + getCap(s2[idx], tp[i], d[i]));

        res = min(res, mn);

        cout << res << nline;
    }
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