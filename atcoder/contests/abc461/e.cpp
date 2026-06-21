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

struct segtree {
    vector<int> nodes;
    int n;
    segtree(int _n) {
        n = _n;
        nodes.resize(4*n);
    }
    int merge(const int l, const int r) {
        return l + r;
    }
    void update(int idx, int s, int e, int pos, int delta) {
        if (s == e) {
            nodes[idx] += delta;
            return;
        }
        int m = (s + e)/2;
        if (pos <= m)
            update(2*idx, s, m, pos, delta);
        else
            update(2*idx + 1, m + 1, e, pos, delta);
        nodes[idx] = merge(nodes[2*idx], nodes[2*idx + 1]);
    }
    int query(int idx, int s, int e, int l, int r) {
        if (s > r || l > e || s > e || l > r) return 0;
        if (l <= s && e <= r) return nodes[idx];
        int m = (s + e)/2;
        return merge(query(2*idx, s, m, l, r), query(2*idx + 1, m + 1, e, l, r));
    }
};
#define N 300005
int lastPosPaintRow[N];
int lastPosPaintCol[N];
void pre_compute() {
    
}
void solve() {
    int n, q; cin >> n >> q;
    segtree treeRowActive(N);
    segtree treeColActive(N);
    
    ll black = 0;
    for (int i = 1; i <= q; i++) {
        int t; cin >> t;
        int row, col;
        if (t == 1) {
            cin >> row;
            
            if (lastPosPaintRow[row] == 0) 
                black += n;
            else {
                black += treeColActive.query(1, 0, N - 1, lastPosPaintRow[row] + 1, i);
            }

            if (lastPosPaintRow[row]) {
                treeRowActive.update(1, 0, N - 1, lastPosPaintRow[row], -1);
            }
            treeRowActive.update(1, 0, N - 1, i, 1);

            lastPosPaintRow[row] = i;
        } else {
            cin >> col;

            black -= treeRowActive.query(1, 0, N - 1, lastPosPaintCol[col] + 1, i);

            if (lastPosPaintCol[col]) {
                treeColActive.update(1, 0, N - 1, lastPosPaintCol[col], -1);
            }
            treeColActive.update(1, 0, N - 1, i, 1);

            lastPosPaintCol[col] = i;
        }
        cout << black << nline;
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