/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/contest/2228/problem/D
*/

#include "bits/stdc++.h"
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

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
ll expo(ll a, ll b, ll mod = MOD) {if (a==0) return 1%mod; ll res = 1; while (b > 0) {if (b & 1)res = (res * a) % mod; a = (a * a) % mod; b = b >> 1;} return res;} // a = 0 return 0 | b = 0 return 1
ll __gcd__(ll a, ll b) {if (!a || !b) return a | b; unsigned shift = __builtin_ctz(a | b); a >>= __builtin_ctz(a); do { b >>= __builtin_ctz(b); if (a > b) swap(a, b); b -= a; } while (b); return a << shift;} // only a >= 0 && b >= 0
ll gcd(ll a, ll b) {a = abs(a); b = abs(b); return __gcd__(a, b);} // get abs(a), abs(b) in case a < 0 || b < 0
typedef tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag, tree_order_statistics_node_update > pbds; // find_by_order, order_of_key
/*--------------------------------------------------------------------------------------------------------------------------*/

#define MX 2000005
int toIdx[MX];
int pmn[MX];
int pmx[MX];
int smn[MX];
int smx[MX];
pair<int,int> v[MX];
int y[MX];
void pre_compute() {
    
}
void solve() {
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> v[i].first >> v[i].second;
        y[i] = v[i].second;
    }
    sort(v, v + n, [](auto &a, auto &b) {
        return a.first < b.first;
    });
    for (int i = 0; i < n; i++) {
        pmn[i] = v[i].second;
        if (i - 1 >= 0) pmn[i] = min(pmn[i], pmn[i - 1]);
        pmx[i] = v[i].second;
        if (i - 1 >= 0) pmx[i] = max(pmx[i], pmx[i - 1]);
    }
    for (int i = n - 1; i >= 0; i--) {
        smn[i] = v[i].second;
        if (i + 1 < n) smn[i] = min(smn[i], smn[i + 1]);
        smx[i] = v[i].second;
        if (i + 1 < n) smx[i] = max(smx[i], smx[i + 1]);
    }

    auto intersect = [](int y1, int y2, int y3, int y4) -> pair<int,int> {
        if (y1 > y4 || y3 > y2) return {-1,-1};
        int a = max(y1,y3);
        int b = min(y2,y4);
        if (a == b) return {-1,-1};
        return {a,b};
    };
    
    sort(y, y + n);
    int sz = unique(y, y + n) - y;
    for (int i = 0; i < sz; i++) toIdx[y[i]] = i;

    ll ans = 0;
    int i = 0;
    while (i < n) {
        int x = v[i].first;
        while (i < n && v[i].first == x) {
            i++;
        }
        if (i < n) {
            int mn1 = pmn[i - 1];
            int mx1 = pmx[i - 1];
            int mn2 = smn[i];
            int mx2 = smx[i];
            auto [y1, y2] = intersect(mn1, mx1, mn2, mx2);
            if (y1 == -1) continue;
            ans += toIdx[y2] - toIdx[y1];
        }
    }
    cout << ans << nline;
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