/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/problemset/problem/2014/E
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
int n, m, h;
bool H[N];
vector<pair<int,int>> g[N];
void pre_compute() {
    
}
auto compare = [] (pair<ll,pair<int,int>> &p1, pair<ll,pair<int,int>> &p2) {
    return p2.first < p1.first;
};
vector<vector<ll>> dijkstra(int src) {
    vector<vector<ll>> dist(n + 1, vector<ll>(2, LINF));
    priority_queue<pair<ll,pair<int,int>>,
            vector<pair<ll,pair<int,int>>>,
            decltype(compare)> q(compare);
    
    if (H[src]) {
        dist[src][1] = 0;
        q.push({0, {src,1}});
    } else {
        dist[src][0] = 0;
        q.push({0,{src,0}});
    }
    while (q.size()) {
        auto p = q.top();
        q.pop();
        ll w_u;
        int u, haveH;
        tie(w_u, ignore) = p;
        tie(u, haveH) = p.second;

        if (w_u > dist[u][haveH]) continue;

        for (auto [v, w_uv] : g[u]) {
            int nhaveH = haveH | H[v];
            int cost = haveH ? w_uv / 2 : w_uv;
            if (dist[v][nhaveH] > w_u + cost) {
                dist[v][nhaveH] = w_u + cost;
                q.push({dist[v][nhaveH], {v, nhaveH}});
            }
        }
    }
    return dist;
}

void solve() {
    cin >> n >> m >> h;
    for (int i = 1; i <= n; i++) g[i].clear(), H[i] = 0;
    for (int i = 1; i <= h; i++) {
        int u; cin >> u;
        H[u] = 1;
    }
    for (int i = 0; i < m; i++) {
        int u, v, w; cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }
    auto d1 = dijkstra(1);
    auto d2 = dijkstra(n);
    ll ans = LINF;
    for (int i = 1; i <= n; i++) {
        ll cur = max(min(d1[i][0], d1[i][1]), min(d2[i][0], d2[i][1]));
        if (cur < LINF)
            ans = min(ans, cur);
    }
    if (ans == LINF)
        cout << -1 << nline;
    else
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