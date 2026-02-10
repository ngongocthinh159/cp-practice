/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/contest/716/problem/E
*/

#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

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
void extendgcd(ll a, ll b, ll*v) {if (b == 0) {v[0] = 1; v[1] = 0; v[2] = a; return ;} extendgcd(b, a % b, v); ll x = v[1]; v[1] = v[0] - v[1] * (a / b); v[0] = x; return;} //pass an arry of size1 3, calculate modular invese a^-1 % b, only work with a and b coprime
ll modinv(ll a, ll m) {ll arr[3]; extendgcd(a, m, arr); return arr[0];} // inverse mod: a^-1 % m for non prime m, and gcd(a,m)=1
/*--------------------------------------------------------------------------------------------------------------------------*/

#define N 100005
int n, M;
vector<pair<int,int>> g[N];
bool del[N];
int child[N], bufdown[N], bufup[N], top;
ll _10pow[N], inverse_mod_10pow[N];
// unordered_map<int,int> fdown, fup;
gp_hash_table<int,int> fdown, fup;
ll ans = 0;
void pre_compute() {
    
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
void acc_ans_sub(int u, int p, int wp, int d, ll hup, ll hdown) {
    hup = (hup * 10 % M + wp) % M;
    hdown = (hdown + wp * _10pow[d - 1] % M) % M;

    // hup + hdown * _10pow[d] = 0 mod M
    // hdown * _10pow[d] = -hup % M
    int keydown = ((-hup + M) % M) * inverse_mod_10pow[d] % M;
    auto it1 = fdown.find(keydown);
    if (it1 != fdown.end()) ans += it1->second;

    // hup + hdown * _10pow[d] = 0 mod M
    // hup * inverse_mod_10pow[d] + hdown = 0 mod M
    // hup * inverse_mod_10pow[d] = -hdown mod M
    int keyup = (-hdown + M) % M;
    auto it2 = fup.find(keyup);
    if (it2 != fup.end()) ans += it2->second;

    for (auto &[v, w] : g[u]) if (v != p && !del[v])
        acc_ans_sub(v, u, w, d + 1, hup, hdown);
    
    bufdown[top] = hdown;
    bufup[top++] = hup * inverse_mod_10pow[d] % M;
}
void CD(int u, int p) {
    int sz = dfs(u, p);
    u = find_centroid(u, p, sz);

    fdown.clear();
    fup.clear();
    fdown[0]++, fup[0]++;
    for (auto &[v, w] : g[u]) if (v != p && !del[v]) {
        top = 0;

        acc_ans_sub(v, u, w, 1, 0, 0);
        
        for (int i = 0; i < top; i++) fdown[bufdown[i]]++, fup[bufup[i]]++;
    }

    del[u] = 1;
    for (auto &[v, w] : g[u]) if (v != p && !del[v])
        CD(v, u);
}
void solve() {
    cin >> n >> M;
    for (int i = 0; i < n - 1; i++) {
        int u, v, w; cin >> u >> v >> w;
        u++, v++;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }

    _10pow[0] = 1;
    for (int i = 1; i < N; i++) _10pow[i] = _10pow[i - 1] * 10 % M;

    inverse_mod_10pow[0] = 1;
    inverse_mod_10pow[1] = (modinv(10, M) + M) % M;
    for (int i = 2; i < N; i++) inverse_mod_10pow[i] = inverse_mod_10pow[i - 1] * inverse_mod_10pow[1] % M;

    CD(1, 0);
    cout << ans << nline;
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