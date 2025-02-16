/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://www.hackerearth.com/practice/algorithms/graphs/depth-first-search/practice-problems/algorithm/the-grass-type/
*/

#include <bits/stdc++.h>
using namespace std;

template<class X, class Y>
    bool maximize(X &x, const Y &y) {
        if (x < y) {
            x = y;
            return true;
        } else return false;
    }

#define ll long long
#define nline "\n"
struct custom_hash {static uint64_t splitmix64(uint64_t x) {x += 0x9e3779b97f4a7c15;x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;x = (x ^ (x >> 27)) * 0x94d049bb133111eb;return x ^ (x >> 31);}size_t operator()(uint64_t x) const {static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();return splitmix64(x + FIXED_RANDOM);}}; // https://codeforces.com/blog/entry/62393

#define MAXN 100005
int n, sz[MAXN], big[MAXN], tin[MAXN], tout[MAXN], ver[MAXN], T = -1;
ll a[MAXN];
ll ans, pairs;
vector<int> g[MAXN];
unordered_map<int,int,custom_hash> freq;
void dfs1(int u, int par) {
    sz[u] = 1;
    big[u] = -1;
    int mx = -1;
    tin[u] = ++T;
    ver[T] = u;
    for (auto v : g[u]) if (v != par) {
        dfs1(v, u);
        sz[u] += sz[v];
        if (maximize(mx, sz[v]))
            big[u] = v;
    }
    tout[u] = T;
}
void del(int v, int u) {
    freq[a[v]]--;
}
void cnt(int v, int u) {
    if (a[v] <= a[u] && a[u]%a[v] == 0) pairs += freq[a[u]/a[v]];
}
void add(int v, int u) {
    freq[a[v]]++;
}
void dfs2(int u, int par, bool keep) {
    for (auto v : g[u]) if (v != par && v != big[u])
        dfs2(v, u, 0);
    if (big[u] != -1)
        dfs2(big[u], u, 1);
    pairs = 0;
    cnt(u, u);
    add(u, u);
    for (auto v : g[u]) if (v != par && v != big[u]) {
        for (int p = tin[v]; p <= tout[v]; p++)
            cnt(ver[p], u);
        for (int p = tin[v]; p <= tout[v]; p++)
            add(ver[p], u);
    }
    ans += pairs;
    if (!keep) {
        for (int p = tin[u]; p <= tout[u]; p++)
            del(ver[p], u);
    }
}
void solve() {
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    dfs1(1, -1);
    dfs2(1, -1, 1);
    cout << ans << nline;
}

int main(){
	ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#ifndef ONLINE_JUDGE
    freopen("Input.txt", "r", stdin);
    freopen("Output.txt", "w", stdout);
#endif
	solve();
	return 0;
}
