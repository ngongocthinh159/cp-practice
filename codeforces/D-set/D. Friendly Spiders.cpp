/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/problemset/problem/1775/D
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
int spf[N];
vector<int> idx[N];
bool visPrime[N];
bool visIdx[N];
int par[N];
void pre_compute() {
    for (int i = 2; i < N; i++) spf[i] = i;
    for (int i = 2; i * i < N; i++) if (spf[i] == i)
        for (int j = i * i; j < N; j += i) spf[j] = min(spf[j], i);
}
vector<int> factor(int x) {
    int u = x;
    vector<int> res;
    while (x != 1) {
        int fact = spf[x];
        res.push_back(fact);
        while (x % fact == 0) x /= fact;
    }

    // cout << u << nline;
    // for (auto v : res) cout << v << ' ';
    // cout << nline;
    // cout << nline;

    return res;
}
void solve() {
    int n; cin >> n;
    int a[n + 1];
    for (int i = 1; i <= n; i++) cin >> a[i];
    int s, t; cin >> s >> t;
    if (s == t) {
        cout << 1 << nline;
        cout << s << nline;
        return;
    }
    if (a[s] == 1 || a[t] == 1) {
        cout << -1 << nline;
        return; 
    }
    for (int i = 1; i <= n; i++) {
        for (auto x : factor(a[i])) idx[x].push_back(i);
    }
    deque<int> q;
    q.push_front(s);
    visIdx[s] = 1;
    int level = 0;
    bool found = false;
    while (q.size()) {
        for (int sz = q.size(); sz; sz--) {
            int uIdx = q.back();
            q.pop_back();
            if (uIdx == t) {
                found = true;
                break;
            }
            for (auto x : factor(a[uIdx])) if (!visPrime[x]) {
                visPrime[x] = 1;
                for (auto vIdx : idx[x]) if (!visIdx[vIdx]) {
                    visIdx[vIdx] = 1;
                    par[vIdx] = uIdx;
                    q.push_front(vIdx);
                }
            }
        }
        if (found) break;
        level++;
    }
    if (!found) {
        cout << -1 << nline;
        return;
    }

    vector<int> res;
    res.reserve(n + 1);
    int cur = t;
    while (cur != 0) {
        res.push_back(cur);
        cur = par[cur];
    }
    reverse(all(res));
    
    cout << int(res.size()) << nline;
    for (auto x : res) cout << x << ' ';
    cout << nline;
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