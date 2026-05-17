/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/contest/2227/problem/G
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
    segtree(int n) {
        nodes.resize(4*n);
    }
    ll merge(ll l, ll r) {
        return l + r;
    }
    void update(int idx, int s, int e, int pos, int val) {
        if (s == e) {
            nodes[idx] += val;
            return;
        }
        int m = (s + e)/2;
        if (pos <= m)
            update(2*idx, s, m, pos, val);
        else
            update(2*idx + 1, m + 1, e, pos, val);
        nodes[idx] = merge(nodes[2*idx], nodes[2*idx + 1]);
    }
    ll query(int idx, int s, int e, int l, int r) {
        if (s > r || l > e || s > e || l > r) return 0;
        if (l <= s && e <= r) return nodes[idx];
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
    for (int i = 1; i <= n; i++) cin >> a[i];
    vector<ll> pref(n + 1);
    for (int i = 1; i <= n; i++) {
        pref[i] = pref[i - 1] + (a[i] * ((i & 1) ? 1 : -1));
    }
    vector<ll> v = pref;
    sort(all(v));
    v.erase(unique(all(v)), v.end());
    unordered_map<ll,ll> prefToIdx;
    for (int i = 0; i < int(v.size()); i++) prefToIdx[v[i]] = i;
    
    int sz = v.size();
    segtree treeOdd(sz);
    segtree treeEven(sz);
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        if (i - 3 >= 0) {
            if ((i - 3)&1) {
                treeOdd.update(1, 0, sz - 1, prefToIdx[pref[i - 3]], 1);
            } else {
                treeEven.update(1, 0, sz - 1, prefToIdx[pref[i - 3]], 1);
            }
        }
        
        ll curPref = pref[i];
        int idx = prefToIdx[curPref];
        if (i&1) {
            ans += treeEven.query(1, 0, sz - 1, 0, idx - 1);
        } else {
            ans += treeOdd.query(1, 0, sz - 1, idx + 1, sz - 1);
        }
    }
    ans += n;
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