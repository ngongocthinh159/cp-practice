/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/contest/2226/problem/E
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
    vector<int> nodes;
    vector<int> lazy;
    int n;
    segtree(int _n) {
        n = 4*_n;
        nodes.resize(n);
        lazy.resize(n);
    }
    int merge(int &l , int &r) {
        return min(l, r);
    }
    void apply(int idx, int s, int e, int delta) {
        nodes[idx] += delta;
        lazy[idx] += delta;
    }
    void push_down(int idx, int s, int e) {
        if (lazy[idx]) {
            int m = (s + e)/2;
            apply(2*idx, s, m, lazy[idx]);
            apply(2*idx + 1, m + 1, e, lazy[idx]);
            lazy[idx] = 0;
        }
    }
    void update(int idx, int s, int e, int l, int r, int delta) {
        if (s > r || l > e || s > e || l > r) return;
        if (l <= s && e <= r) {
            apply(idx, s, e, delta);
            return; 
        }
        push_down(idx, s, e);
        int m = (s + e)/2;
        update(2*idx, s, m, l, r, delta);
        update(2*idx + 1, m + 1, e, l, r, delta);
        nodes[idx] = merge(nodes[2*idx], nodes[2*idx + 1]);
    }
    int query(int idx, int s, int e, int l, int r) {
        if (s > r || l > e || s > e || l > r) return IINF;
        if (l <= s && e <= r) return nodes[idx];
        int m = (s + e)/2;
        int lans = query(2*idx, s, m, l, r);
        int rans = query(2*idx + 1, m + 1, e, l, r);
        return merge(lans, rans);
    }
};
void pre_compute() {
    
}
void solve() {
    int n; cin >> n;
    int a[n + 1];
    int ans[n + 1];
    for (int i = 1; i <= n; i++) cin >> a[i];
    int mex = 0;
    int sz = n + 5;
    segtree tree(sz);
    unordered_map<int,int,chash> f;
    for (int i = 1; i <= n; i++) {
        if (a[i] < mex) {
            if (f[a[i]] == 0) {
                tree.update(1, 0, sz - 1, 0, min(a[i], sz - 1), 1); // - receiver
            } else {
                tree.update(1, 0, sz - 1, 0, min((a[i] - 1)/2, sz - 1), 1); // + offerer
            }
        } else {
            tree.update(1, 0, sz - 1, 0, min((a[i] - 1)/2, sz - 1), 1); // + offerer
        }

        f[a[i]]++;

        while (1) {
            if (f[mex] != 0) {
                tree.update(1, 0, sz - 1, 0, min((mex - 1)/2, sz - 1), -1); // - offerer
                if (tree.query(1, 0, sz - 1, 0, mex) >= 0) {
                    mex++;
                } else {
                    tree.update(1, 0, sz - 1, 0, min((mex - 1)/2, sz - 1), 1); // rollback
                    break;
                }
            } else {
                tree.update(1, 0, sz - 1, 0, mex, -1); // + receiver
                if (tree.query(1, 0, sz - 1, 0, mex) >= 0) {
                    mex++;
                } else {
                    tree.update(1, 0, sz - 1, 0, mex, 1); // rollback
                    break;
                }
            }
        }

        ans[i] = mex;
    }
    for (int i = 1; i <= n; i++) cout << ans[i] << ' ';
    cout << nline;
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