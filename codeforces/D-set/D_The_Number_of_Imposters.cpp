/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/problemset/problem/1594/D
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

#define N 200005
int n, m;
vector<array<int,3>> g[N];
bool vis[N];
bool contra;
int side[N];
void pre_compute() {
    
}
void dfs(int u, int cur, int &cnt, int &compo_cnt) {
    if (cur == 1) cnt++;
    side[u] = cur;
    compo_cnt++;
    vis[u] = 1;
    for (auto [v, w, t] : g[u]) {
        if (vis[v]) {
            if (t == 0) {
                int nxt = cur ^ w;
                if (side[v] != nxt) contra = true;
            } else {
                int nxt = side[v] ^ w;
                if (nxt != cur) contra = true;
            }
        } else {
            dfs(v, cur ^ w, cnt, compo_cnt);
        }
    }
}
void solve() {
    cin >> n >> m;
    for (int i=0; i< m; i++) {
        int u, v;
        string s; cin >> u >> v >> s;
        if (s[0] == 'i') {
            g[u].push_back({v,1,0});
            g[v].push_back({u,1,1});
        } else {
            g[u].push_back({v,0,0});
            g[v].push_back({u,0,1});
        }
    }
    contra = false;
    int ans = 0;
    for (int i = 1; i <= n; i++) if (!vis[i]) {
        int cnt = 0, compo_cnt = 0;
        dfs(i, 0, cnt, compo_cnt);
        ans += max(cnt, compo_cnt - cnt);
    }

    if (contra) {
        cout << -1 << nline;
    } else {
        cout << ans << nline;
    }

    for (int i = 1; i <= n; i++) {
        g[i].clear();
        vis[i] = 0;
    }
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