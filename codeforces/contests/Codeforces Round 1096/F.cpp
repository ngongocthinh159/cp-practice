/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/contest/2227/problem/F
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

struct segtree {
    vector<ll> nodes;
    vector<ll > lazy;
    segtree(int n) {
        nodes.resize(4*n);
        lazy.resize(4*n);
    }
    ll merge(ll l, ll r) {
        return l + r;
    }
    void apply(int idx, int s, int e, ll val) {
        nodes[idx] += (e - s + 1) * val;
        lazy[idx] += val;
    }
    void push_down(int idx, int s, int e) {
        if (lazy[idx]) {
            int m = (s + e)/2;
            apply(2*idx, s, m, lazy[idx]);
            apply(2*idx + 1, m + 1, e, lazy[idx]);
            lazy[idx] = 0;
        }
    }
    void update(int idx, int s, int e, int l, int r, ll val) {
        if (s > r || l > e || s > e || l > r) return;
        if (l <= s && e <= r) {
            apply(idx, s, e, val);
            return;
        }
        push_down(idx, s, e);
        int m = (s + e)/2;
        update(2*idx, s, m, l, r, val);
        update(2*idx + 1, m + 1, e, l, r, val);
        nodes[idx] = merge(nodes[2*idx], nodes[2*idx + 1]);
    }
    ll query(int idx, int s, int e, int l, int r) {
        if (s > r || l > e || s > e || l > r) return 0;
        if (l <= s && e <= r) return nodes[idx];
        push_down(idx, s, e);
        int m = (s + e)/2;
        ll lans = query(2*idx, s, m, l, r);
        ll rans = query(2*idx + 1, m + 1, e, l, r);
        return merge(lans, rans);
    }
};
void pre_compute() {
    
}
void solve() {
    int n; cin >> n;
    int a[n + 1];
    segtree tree1(n + 1);
    segtree tree2(n + 1);
    vector<ll> gain(n + 1);
    ll mx = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        gain[i] = tree2.query(1, 0, n, a[i], n);
        tree2.update(1, 0, n, a[i], a[i], 1);
        mx = max(mx, gain[i]);
    }
    ll h = 0;
    ll sum = 0;
    for (int i = n; i >= 1; i--) {
        sum += a[i] * h - tree1.query(1, 0, n, 1, a[i]);
        h++;
        tree1.update(1, 0, n, 1, a[i], 1);
    }
    cout << (sum + mx) << nline;
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