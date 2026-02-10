/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/contest/293/problem/E
*/

#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

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
typedef tree<pair<int,int>, null_type, less<pair<int,int>>, rb_tree_tag, tree_order_statistics_node_update > pbds; // find_by_order, order_of_key



#define N 100005

int n, L, W;
vector<pair<int,ll>> g[N];
bool del[N];
int child[N], top, id = 0, subid = 0;
array<int, 3> buf[N];
pbds S;
pbds SL[N];

void pre_compute() {
    
}
int dfs(int u, int p) {
    child[u] = 1;
    for (auto &[v, w] : g[u]) if (v != p && !del[v]) child[u] += dfs(v, u);
    return child[u];
}
int find_centroid(int u, int p, int sz) {
    for (auto &[v, w] : g[u]) if (v != p && !del[v] && child[v] > sz/2) return find_centroid(v, u, sz);
    return u;
}
void go(int u, int p, int wu, int d, int sid) {
    if (d > L || wu > W) return;
    buf[top++] = {d, wu, sid};
    for (auto &[v, w] : g[u]) if (v != p && !del[v])
        go(v, u, wu + w, d + 1, sid);
}
ll CD(int u, int p) {
    int sz = dfs(u, p);
    u = find_centroid(u, p, sz);
    
    ll ans = 0;
    S.clear();
    top = 0, subid = 0;
    for (int i = 0; i < sz + 5; i++) SL[i].clear();

    buf[top++] = {0, 0, subid++};
    for (auto &[v, w] : g[u]) if (v != p && !del[v])
        go(v, u, w, 1, subid++);
    sort(buf, buf + top);
    for (int i = top - 1, j = 0; i >= 0; i--) {
        int remainD = L - buf[i][0], remainW = W - buf[i][1];
        while (j < top && buf[j][0] <= remainD) {
            S.insert({buf[j][1], id++});
            SL[buf[j][2]].insert({buf[j][1], id++});
            j++;
        }
        auto it = S.upper_bound({remainW, INT_MAX});
        if (it != S.begin()) {
            it--;
            ans += S.order_of_key(*it) + 1;

            auto it2 = SL[buf[i][2]].upper_bound({remainW, INT_MAX});
            if (it2 != SL[buf[i][2]].begin()) {
                it2--;
                ans -= SL[buf[i][2]].order_of_key(*it2) + 1;
            }
        }
    }
    
    del[u] = 1;
    for (auto &[v, w] : g[u]) if (v != p && !del[v])
        ans += CD(v, u);
    return ans / 2;
}
void solve() {
    cin >> n >> L >> W;
    for (int i = 1; i < n; i++) {
        int p, w; cin >> p >> w;
        int u = p, v = i + 1;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }
    cout << CD(1, 0) << nline;
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