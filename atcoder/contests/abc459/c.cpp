/**
 * Author: Thinh Ngo Ngoc
 * Solution for: 
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

#define N 300005
struct node {
    int mn, sum;
    node() {
        mn = 0;
        sum = 0;
    }
    node(int _mn, int _sum) {
        mn = _mn;
        sum = _sum;
    }
};
struct segtree {
    vector<node> nodes;
    int n;
    segtree(int _n) {
        n = _n;
        nodes.resize(4*n);
    }
    node merge(node &l, node &r) {
        node res;
        res.sum = l.sum + r.sum;
        res.mn = min(l.mn, r.mn);
        return res;
    }
    void update(int idx, int s, int e, int pos, int delta) {
        if (s == e) {
            nodes[idx].mn += delta;
            nodes[idx].sum += delta;
            return;
        }
        int m = (s + e)/2;
        if (pos <= m)
            update(2*idx, s, m, pos, delta);
        else
            update(2*idx + 1, m + 1, e, pos, delta);
        nodes[idx] = merge(nodes[2*idx], nodes[2*idx + 1]);
    }
    node query(int idx, int s, int e, int l, int r) {
        if (s > r || l > e || s > e || l > r) return node{IINF, 0};
        if (l <= s && e <= r) return nodes[idx];
        int m = (s + e)/2;
        node lans = query(2*idx, s, m, l, r);
        node rans = query(2*idx + 1, m + 1, e, l, r);
        return merge(lans, rans);
    }
};
void pre_compute() {
    
}
void solve() {
    int n, q; cin >> n >> q;
    segtree tree(N);
    int a[n + 1]{};
    unordered_map<int,int,chash> f;
    f[0] = n;
    int mn = 0;
    tree.update(1, 0, N - 1, 0, n);
    for (int i = 0; i < q; i++) {
        int t; cin >> t;
        if (t == 1) {
            int x; cin >> x;
            tree.update(1, 0, N - 1, a[x], -1);
            
            if (--f[a[x]] == 0 && a[x] == mn) mn++;

            a[x]++;
            tree.update(1, 0, N - 1, a[x], +1);
            f[a[x]]++;
        } else {
            int y; cin >> y;
            cout << tree.query(1, 0, N - 1, y + mn, N - 1).sum << nline;
        }
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