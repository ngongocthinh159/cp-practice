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

struct FenwickTree {
    vector<int> bit;  // binary indexed tree
    int n;

    FenwickTree(int n) {
        this->n = n;
        bit.assign(n, 0);
    }

    FenwickTree(vector<int> const &a) : FenwickTree(a.size()) {
        for (size_t i = 0; i < a.size(); i++)
            add(i, a[i]);
    }

    int sum(int r) {
        int ret = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            ret += bit[r];
        return ret;
    }

    int sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }

    void add(int idx, int delta) {
        for (; idx < n; idx = idx | (idx + 1))
            bit[idx] += delta;
    }
};
void pre_compute() {
    
}
void solve() {
    int n; cin >> n;
    int m; cin >> m;
    int L[m + 1], R[m + 1];
    for (int i = 1; i <= m; i++) cin >> L[i] >> R[i];
    int q; cin >> q;
    int S[q + 1], T[q + 1];
    for (int i = 1; i <= q; i++) cin >> S[i] >> T[i];
    
    int order1[m + 1];
    iota(order1, order1 + m + 1, 0);
    sort(order1 + 1, order1 + m + 1, [&](int i, int j) {
        return R[i] < R[j];
    });

    int order2[m + 1];
    iota(order2, order2 + m + 1, 0);
    sort(order2 + 1, order2 + m + 1, [&](int i, int j) {
        return L[i] < L[j];
    });

    unordered_map<int,vector<int>> ltor,rtol;
    for (int i = 1; i <= m; i++) {
        ltor[L[i]].push_back(R[i]);
        rtol[R[i]].push_back(L[i]);
    }
    for (auto &[a, list] : ltor) sort(all(list));
    for (auto &[a, list] : rtol) sort(all(list));
    int order3[q + 1];
    iota(order3, order3 + q + 1, 0);
    sort(order3 + 1, order3 + q + 1, [&](int i, int j) {
        return T[i] < T[j];
    });
    FenwickTree tree(n + 1);
    bool ans[q + 1]{};
    int prev = 0;
    for (int j = 1; j <= q; j++) {
        int i = order3[j];
        int l = S[i];
        int r = T[i];
        while (prev < r) {
            prev++;
            for (auto _l : rtol[prev]) {
                tree.add(_l, 1);
            }
        }
        if (!ltor.count(l)) {
            ans[i] = 0; 
            continue;
        }
        auto it = upper_bound(all(ltor[l]), r);
        if (it == ltor[l].begin()) {
            ans[i] = 0;
            continue;
        }
        it--;
        int bR = *it;
        if (bR == r) {
            int cnt = tree.sum(l, r);
            if (cnt >= 2) {
                ans[i] = 1;
            } else {
                ans[i] = 0;
            }
        } else {
            if (!rtol.count(r)) {
                ans[i] = 0;
                continue;
            }
            auto it = lower_bound(all(rtol[r]), l);
            if (it == rtol[r].end()) {
                ans[i] = 0;
                continue;
            }
            int bL = *it;
            if (bL > bR + 1) {
                ans[i] = 0;
            } else {
                ans[i] = 1;
            }
        }
    }
    for (int i = 1; i <= q; i++) {
        if (ans[i]) 
            cout << "Yes" << nline;
        else 
            cout << "No" << nline;
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