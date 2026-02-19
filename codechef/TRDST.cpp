/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://www.codechef.com/problems/TRDST
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
#define LOG 20
#define data __data
int n, T = 0, cur_sz, p_cur_sz;
int k[N], child[N], parcd[N], euler[2*N], pos[N], depth[N], rmq[LOG][2*N];
vector<int> g[N];
bool del[N];
struct data {
    vector<int> dist;
    vector<int> pdist;
};
data nodes[N];
void pre_compute() {
    
}
void dfs0(int u, int p) {
    pos[u] = T;        
    euler[T++] = u;
    for (auto v : g[u]) if (v != p) {
        depth[v] = depth[u] + 1;
        dfs0(v, u);
        euler[T++] = u;
    }
}
int mini(int u, int v) {
    if (depth[u] < depth[v]) return u;
    return v;
}
int query_rmq(int l, int r) {
    int msb = 32 - __builtin_clz(r - l + 1) - 1;
    return mini(rmq[msb][l], rmq[msb][r - MASK(msb) + 1]);
}
int LCA(int u, int v) {
    if (pos[u] > pos[v]) swap(u, v);
    return query_rmq(pos[u], pos[v]);
}
int dist(int u, int v) {
    return depth[u] + depth[v] - 2 * depth[LCA(u, v)];
}
int dfs(int u, int p) {
    child[u] = 1;
    for (auto v : g[u]) if (v != p && !del[v]) child[u] += dfs(v, u);
    return child[u];
}
int find_centroid(int u, int p, int sz) {
    for (auto v : g[u]) if (v != p && !del[v] && child[v] > sz/2)
        return find_centroid(v, u, sz);
    return u;
}
void acc(int u, int p, int d, int pCentroid, data &node) {
    node.dist[d]++;
    if (pCentroid && dist(u, pCentroid) < p_cur_sz) 
        node.pdist[dist(u, pCentroid)]++;
    for (auto v : g[u]) if (v != p && !del[v])
        acc(v, u, d + 1, pCentroid, node);
}
void CD(int u, int p, int psz) {
    int sz = dfs(u, p);
    u = find_centroid(u, p, sz);

    cur_sz = sz;
    p_cur_sz = psz;
    parcd[u] = p;
    auto &node = nodes[u];
    node.dist.resize(cur_sz);
    node.pdist.resize(p_cur_sz);
    node.dist[0]++;
    if (p != 0 && dist(u, p) < p_cur_sz) 
        node.pdist[dist(u, p)]++;
    for (auto v : g[u]) if (v != p && !del[v])
        acc(v, u, 1, p, node);
    for (int i = 1; i < cur_sz; i++)
        node.dist[i] += node.dist[i - 1];
    for (int i = 1; i < p_cur_sz; i++)
        node.pdist[i] += node.pdist[i - 1];

    del[u] = 1;
    for (auto v : g[u]) if (v != p && !del[v])
        CD(v, u, sz);
}
int cnt_nodes_within(int u, int mx_dist) {
    int res = 0;
    int v = u;
    int prev = -1;
    while (v != 0) {
        int wanted = mx_dist - dist(v, u);
        if (wanted >= 0) {
            wanted = min(wanted, (int) nodes[v].dist.size() - 1);
            res += nodes[v].dist[wanted];
            
            if (prev != -1) {
                res -= nodes[prev].pdist[wanted];
            }
        }

        prev = v;
        v = parcd[v];
    }
    return res;
}
void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> k[i];
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs0(1, 0);

    for (int i = 0; i < T; i++) rmq[0][i] = euler[i];
    for (int j = 1; j < LOG; j++)
        for (int i = 0; i + MASK(j) - 1 < T; i++) rmq[j][i] = mini(rmq[j - 1][i], rmq[j - 1][i + MASK(j - 1)]);

    CD(1, 0, n);

    for (int i = 1; i <= n; i++) {
        int l = -1, r = n;
        while (r - l > 1) {
            int m = l + (r - l) / 2;
            if (n - cnt_nodes_within(i, m) >= k[i])
                l = m;
            else
                r = m;
        }
        cout << l << " ";
    }
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