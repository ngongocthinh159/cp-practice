/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/contest/959/problem/F
*/

#include<bits/stdc++.h>
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

#define N 100005
#define B 20
struct query {
    int l, x, idx;
};
vector<query> at[N];
int x[N], basis[B];
int sz;
ll _2pow[N], ans[N];
void pre_compute() {
    _2pow[0] = 1;
    for (int i = 1; i < N; i++) _2pow[i] = _2pow[i - 1] * 2 % MOD;
}
void insertVector(int mask) {
    for (int bit = B - 1; bit >= 0; bit--) if ((mask >> bit) & 1) {
        if (!basis[bit]) {
            basis[bit] = mask;
            sz++;
            return;
        }
        mask ^= basis[bit];
    }
}
bool isInVectorSpace(int x) {
    for (int bit = B - 1; bit >= 0; bit--) if (basis[bit]) {
        x = min(x, x ^ basis[bit]);
    }
    return x == 0;
}
void solve() {
    int n, q; cin >> n >> q;
    for (int i = 0; i < n; i++) cin >> x[i];
    for (int i = 0; i < q; i++) {
        int l, x;
        cin >> l >> x; l--;
        at[l].push_back(query{l, x, i});
    }
    for (int i = 0; i < n; i++) {
        insertVector(x[i]);
        for (auto &q : at[i]) {
            if (isInVectorSpace(q.x)) {
                ans[q.idx] = _2pow[i + 1 - sz];
            } else
                ans[q.idx] = 0;
        }
    }
    for (int i = 0; i < q; i++) cout << ans[i] << nline;
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
