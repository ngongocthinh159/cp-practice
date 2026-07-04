/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/problemset/problem/1725/M
*/

#include "bits/stdc++.h"
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
ll expo(ll a, ll b, ll mod = MOD) {if (a==0) return 1%mod; ll res = 1; while (b > 0) {if (b & 1)res = (res * a) % mod; a = (a * a) % mod; b = b >> 1;} return res;} // a = 0 return 0 | b = 0 return 1
ll __gcd__(ll a, ll b) {if (!a || !b) return a | b; unsigned shift = __builtin_ctz(a | b); a >>= __builtin_ctz(a); do { b >>= __builtin_ctz(b); if (a > b) swap(a, b); b -= a; } while (b); return a << shift;} // only a >= 0 && b >= 0
ll gcd(ll a, ll b) {a = abs(a); b = abs(b); return __gcd__(a, b);} // get abs(a), abs(b) in case a < 0 || b < 0
typedef tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag, tree_order_statistics_node_update > pbds; // find_by_order, order_of_key
/*--------------------------------------------------------------------------------------------------------------------------*/


#define N 100005
vector<array<ll,3>> g[N][2];
ll dist[N][2];
void pre_compute() {
    
}
void solve() {
    int n, m; cin >> n >> m;

    for (int i = 1; i <= m; i++) {
        int u, v, w; cin >> u >> v >> w;
        g[u][0].push_back({v, 0, w});
        g[v][1].push_back({u, 1, w});
    }
    for (int i = 1; i <= n; i++) {
        g[i][0].push_back({i, 1, 0});
    }
    memset(dist, 0x3f, sizeof dist);
    
    dist[1][0] = 0;
    priority_queue<array<ll,3>,vector<array<ll,3>>,greater<>> q;
    q.push({0,1,0});
    while (q.size()) {
        auto t = q.top();
        q.pop();
        ll w_u = t[0];
        ll u = t[1];
        ll s = t[2];
        if (w_u > dist[u][s]) continue;
        for (auto &tv : g[u][s]) {
            ll v = tv[0];
            ll sv = tv[1];
            ll w_uv = tv[2];
            if (dist[v][sv] > w_u + w_uv) {
                dist[v][sv] = w_u + w_uv;
                q.push({dist[v][sv], v, sv});
            }
        }
    }
    for (int v = 2; v <= n; v++) {
        ll d = min(dist[v][0], dist[v][1]);
        if (d == 4557430888798830399ll) 
            cout << -1 << ' ';
        else 
            cout << d << ' ';
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