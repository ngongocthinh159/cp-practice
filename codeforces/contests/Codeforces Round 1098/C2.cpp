/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/contest/2228/problem/C2
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


void pre_compute() {
    
}
void solve() {
    ll a, n; cin >> a >> n;
    vector<int> d(n);
    for (int i = 0; i < n; i++) cin >> d[i];
    auto append = [](ll prefix, int x, int cnt) {
        while (cnt--) prefix = prefix * 10 + x;
        return prefix;
    };
    int mn = d[0], mx = d[n - 1];

    string s = to_string(a);
    int len = s.size();
    vector<ll> v;

    // smaller length
    if (len > 1) v.push_back(append(0, mx, len - 1));
    
    // larger length
    if (mn != 0) 
        v.push_back(append(0, mn, len + 1));
    else if (mn == 0 && n > 1) 
        v.push_back(append(d[1], mn, len));
    
    // equal length: must be differnt at 1 position
    ll prefix = 0;
    bool ok = true;
    for (int i = 0; i < len; i++) {
        int c = s[i] - '0'; 
        bool found = false;
        for (int j = 0; j < n; j++) {
            if (i == 0 && d[j] == 0 && len > 1) continue;

            if (d[j] < c) {
                v.push_back(append(prefix * 10 + d[j], mx, len - i - 1));
            } else if (d[j] > c) {
                v.push_back(append(prefix * 10 + d[j], mn, len - i - 1));
            } else if (d[j] == c) {
                found = true;
            }

        }

        if (found) {
            prefix = prefix * 10 + c;
        } else {
            ok = false; // cannot continue prefix
            break;
        }
    }
    if (ok) v.push_back(prefix);
    ll ans = LINF;
    for (auto x : v) ans = min(ans, abs(x - a));
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