/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/contest/2126/problem/F
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

#define N 200005
int n, q;
vector<int> g[N];
int a[N];
struct Edge {
    int u, v, c;
} e[N];
int uToPEIdx[N], par[N];
ll uToTotC[N];
unordered_map<int,ll,chash> info[N];
ll uToTotE[N];
ll tot;
void dfs(int u, int p) {
    for (auto idx : g[u]) {
        int v = u ^ e[idx].v ^ e[idx].u;
        if (v != p) {
            uToPEIdx[v] = idx;
            par[v] = u;
            dfs(v, u);
            if (a[u] != a[v]) {
                tot += e[idx].c;
            }
            info[u][a[v]] += e[idx].c;
            uToTotE[u] += e[idx].c;
        }
    }
}
void pre_compute() {
    
}
void solve() {
    cin >> n >> q;
    for (int i = 1; i <= n; i++) g[i].clear();
    for (int i = 1; i <= n; i++) info[i].clear();
    tot = 0;

    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 0; i < n - 1; i++) {
        cin >> e[i].u >> e[i].v >> e[i].c;
        g[e[i].u].push_back(i);
        g[e[i].v].push_back(i);
    }
    
    dfs(1, -1);

    for (int i = 0; i < q; i++) {
        int u, x; cin >> u >> x;

        tot -= (uToTotE[u] - info[u][a[u]]);
        tot += (uToTotE[u] - info[u][x]);

        if (par[u] != -1) {
            int p = par[u];
            int e_c = e[uToPEIdx[u]].c;

            if (a[p] != a[u]) tot -= e_c;
            info[p][a[u]] -= e_c;

            if (a[p] != x) tot += e_c;
            info[p][x] += e_c;
        }

        a[u] = x;

        cout << tot << nline;
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