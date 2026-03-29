/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/contest/2211/problem/C2
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

struct dsu {
    vector<int> parent;
    vector<int> size;
    dsu(int n) {
        parent.resize(n);
        iota(all(parent), 0);
        size.assign(n, 1);
    }
    int find(int x) {
        if (x == parent[x]) return x;
        return parent[x] = find(parent[x]);
    }
    void unite(int a, int b) {
        int pa = find(a);
        int pb = find(b);
        if (pa != pb) {
            if (size[pb] > size[pa]) swap(a, b), swap(pa, pb);
            size[pa] += size[pb];
            parent[pb] = pa;
        }
    }
};
void pre_compute() {
    
}
void solve() {
    int n, k; cin >> n >> k;
    int a[n + 1], b[n + 1];
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];
    dsu d(n + 1);
    unordered_map<int,unordered_set<int>> idToVal;
    bool ok = true;
    for (int i = k + 1; i <= n; i++) {
        if (a[i] == a[i - k]) {
            d.unite(i - k, i);
        } else {
            if (b[i] == -1) b[i] = a[i];
            else {
                if (b[i] != a[i]) ok = false;
            }
            if (b[i - k] == -1) b[i - k] = a[i - k];
            else {
                if (b[i - k] != a[i - k]) ok = false;
            }
        }
    }
    for (int i = 1; i <= n; i++) if (b[i] != -1) {
        idToVal[d.find(i)].insert(b[i]);
    }
    for (auto &[id, S] : idToVal) if (int(S.size()) >= 2) ok = false;
    for (int i = 1; i <= n; i++) {
        int compo = d.find(i);
        if (idToVal[compo].size()) b[i] = *idToVal[compo].begin();
    }
    auto validFirstK = [&]() -> bool {
        unordered_map<int,int> fa,fb;
        for (int i = 1; i <= k; i++) {
            fa[a[i]]++;
            if (b[i] != -1) fb[b[i]]++;
        }
        for (auto &[val, cnt] : fb) if (fa[val] < cnt) return false;
        return true;
    };
    if (!validFirstK()) ok = false;
    if (!ok)
        cout << "NO" << nline;
    else
        cout << "YES" << nline;
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