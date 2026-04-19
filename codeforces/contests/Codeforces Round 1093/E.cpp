/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/contest/2220/problem/E
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
int n;
string color;
vector<int> g[N];
bool vis[N];
double dp[N][2];
void pre_compute() {
    
}
void dfs(int u, int p) {
    vis[u] = 1;
    {
        int idx = -1;
        for (int i = 0; i < int(g[u].size()); i++) if (g[u][i] == p) {
            idx = i;
            break;
        }
        if (idx != -1) {
            swap(g[u][idx], g[u].back());
            g[u].pop_back();
        }
    }
    if (color[u] == '1') {
        dp[u][0] = 0; 
        dp[u][1] = IINF;
        return;
    }
    if (int(g[u].size()) == 0) {
        dp[u][0] = IINF;
        dp[u][1] = 1;
        return;
    }

    for (auto v : g[u])
        dfs(v, u);

    sort(g[u].begin(), g[u].end(), [&](int i, int j) {
        return dp[i][0] - dp[i][1] < dp[j][0] - dp[j][1];
    });

    dp[u][0] = dp[u][1] = IINF;

    
    int sz = g[u].size();
    vector<double> suf(sz + 1);
    for (int i = sz - 1; i >= 0; i--) {
        int v = g[u][i];
        suf[i] = suf[i + 1] + dp[v][1];
    }
    if (p != -1)
        dp[u][1] = (sz + 1) + suf[0];
    double pref = 0;
    for (int i = 0; i < sz; i++) {
        int v = g[u][i];
        pref += dp[v][0];
        dp[u][0] = min(dp[u][0], pref + suf[i + 1] + 1.00 * (sz + (p != -1 ? 1 : 0)) / (i + 1));
        if (p != -1)
            dp[u][1] = min(dp[u][1], pref + suf[i + 1] + 1.00 * (sz + 1) / (i + 2));
    }
}
void solve() {
    cin >> n;
    cin >> color;
    color = " " + color;

    for (int i = 1; i <= n; i++) {
        g[i].clear();
        vis[i] = 0;
    }
    for (int i = 0 ;i < n - 1; i ++) {
        int u, v; cin>> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    double ans = 0;
    for (int i = 1; i <= n; i++) if (color[i] == '0' && !vis[i]) {
        dfs(i, -1);
        ans += dp[i][0];
    }
    printf("%.8f\n", ans);
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