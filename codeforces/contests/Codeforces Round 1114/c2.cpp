/**
 * Author: Thinh Ngo Ngoc
 * Solution for: 
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
ll cal(vector<int> &a, vector<int> &b) {
    int n = a.size();
    ll res = 0;
    set<int> pos0, pos1;
    for (int i = n - 1; i >= 0; i--) {
        if (a[i] == 0) pos0.insert(i);
        else pos1.insert(i);
    }
    for (int i = 0; i < n; i++) {
        auto &pos = b[i] == 0 ? pos0 : pos1;
        auto &npos = b[i] == 0 ? pos1 : pos0;
        if (a[i] == b[i]) {
            pos.erase(pos.begin());
            continue;
        }
        int idx = *pos.begin();
        a[i] ^= 1;
        a[idx] ^= 1;
        res += idx - i;
        npos.erase(npos.begin());
        npos.insert(idx);
        pos.erase(pos.begin());
    }
    return res;
}
void solve() {
    int n; cin >> n;
    int a[n + 1], b[n + 1];
    for (int i = 1; i <= n; i++) {
        char x; cin >> x;
        a[i] = x - '0';
    }
    for (int i = 1; i <= n; i++) {
        char x; cin >> x;
        b[i] = x - '0';
    }
    int c1 = 0, c2 = 0;
    for (int i = 1; i <= n; i++) {
        int &c = (i&1) ? c1 : c2;
        if (a[i] == 1) c++;
        if (b[i] == 1) c--;
    }
    if (c1 || c2) {
        cout << -1 << nline;
        return;
    }
    vector<int> a1;
    vector<int> a2;
    vector<int> b1;
    vector<int> b2;
    for (int i = 1; i <= n; i++) {
        auto &_a = (i&1) ? a1 : a2;
        auto &_b = (i&1) ? b1 : b2;
        _a.push_back(a[i]);
        _b.push_back(b[i]);
    }
    // for (auto x : a1) cout << x << ' ';
    // cout << nline;
    // for (auto x : b1) cout << x << ' ';
    // cout << nline;
    
    // cout << nline;
    // cout << nline;
    // for (auto x : a2) cout << x << ' ';
    // cout << nline;
    // for (auto x : b2) cout << x << ' ';
    // cout << nline;

    cout << cal(a1, b1) + cal(a2, b2) << nline;
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