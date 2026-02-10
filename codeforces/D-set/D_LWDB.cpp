/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/gym/100633/problem/D
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
#define LOG 18
int n, q, T = 0;
bool del[N];
int child[N], par[LOG][N], parcd[N], depth[N], pref[N];
vector<pair<int, int>> g[N];
deque<array<int, 3>> nodes[N]; // [<dist, time, color>,..]
void pre_compute() {
    
}

int LCA(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    int k = depth[u] - depth[v];
    for (int bit = LOG - 1; bit >= 0; bit--) if ((k >> bit) & 1) u = par[bit][u];
    if (u == v) return u;
    for (int bit = LOG - 1; bit >= 0; bit--) if (par[bit][u] != par[bit][v]) {
        u = par[bit][u];
        v = par[bit][v];
    }
    return par[0][u];
}
int dist(int u, int v) {
    return pref[u] + pref[v] - 2 * pref[LCA(u, v)];
}
void dfs0(int u, int p) {
    for (auto &[v, w] : g[u]) if (v != p) {
        depth[v] = depth[u] + 1;
        pref[v] = pref[u] + w;
        par[0][v] = u;
        for (int j = 1; j < LOG; j++) par[j][v] = par[j - 1][par[j - 1][v]];
        dfs0(v, u);
    }
}

int dfs(int u, int p) {
    child[u] = 1;
    for (auto &[v, w] : g[u]) if (v != p && !del[v]) child[u] += dfs(v, u);
    return child[u];
}
int find_centroid(int u, int p, int sz) {
    for (auto &[v, w] : g[u]) if (v != p && !del[v] && child[v] > sz/2)
        return find_centroid(v, u, sz);
    return u;
}
void CD(int u, int p) {
    dfs(u, p);
    u = find_centroid(u, p, child[u]);

    parcd[u] = p;

    del[u] = 1;
    for (auto &[v, w] : g[u]) if (v != p && !del[v])
        CD(v, u);
}
void paint(int u, int d, int c) {
    int v = u;
    while (v != 0) {
        int remainD = d - dist(v, u);
        if (remainD >= 0) {
            while (nodes[v].size() && nodes[v].front()[0] <= remainD) nodes[v].pop_front();
            nodes[v].push_front({remainD, T, c});
        }
        v = parcd[v];
    }

    T++;
}
int query(int u) {
    int v = u;
    int c = 0, maxT = -1;
    while (v != 0) {
        int requiredD = dist(u, v);
        if (nodes[v].back()[0] >= requiredD) {
            int l = -1, r = nodes[v].size();
            while (r - l > 1) {
                int m = l + (r - l)/2;
                if (nodes[v][m][0] >= requiredD)
                    r = m;
                else
                    l = m;
            }
            if (maximize(maxT, nodes[v][r][1])) c = nodes[v][r][2];
        }
        v = parcd[v];
    }
    return c;
}
void solve() {
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v, w; cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }
    dfs0(1, 0);
    CD(1, 0);

    for (int i = 1; i <= n; i++) nodes[i].push_front({0, 0, 0});
    T++;

    cin >> q;
    int t, v, d, c;
    for (int i = 0; i < q; i++) {
        cin >> t;
        if (t == 1) {
            cin >> v >> d >> c;
            paint(v, d, c);
        } else {
            cin >> v;
            cout << query(v) << nline;
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