/**
 * Author: Thinh Ngo Ngoc
 * Solution for: 
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


#define N 100005
int n, m, w;
vector<int> g[N];
char s[N][15];
int color[N][15];
void pre_compute() {
    
}
bool dfs(int u, int day) {
    color[u][day] = 1;

    int nday = (day + 1) <= w ? (day + 1) : 1;
    bool res = false;
    for (auto v : g[u]) if (s[v][nday] == 'o') {
        if (color[v][nday] == 1) {
            res = true;
        } else if (color[v][nday] == 0) {
            res |= dfs(v, nday);
        }
    }
    if (s[u][nday] == 'o') {
        if (color[u][nday] == 1) {
            res = true;
        } else if (color[u][nday] == 0) {
            res |= dfs(u, nday);
        }
    }

    color[u][day] = 2;
    return res;
}
void solve() {
    cin >> n >> m;
    for (int i = 1; i <= n ;i++) g[i].clear();

    for (int i = 1; i <= m; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    cin >> w;

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= w; j++) color[i][j] = 0;

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= w; j++) cin >> s[i][j];

    bool ok = false;
    for (int i = 1; i <= n; i++) if (s[i][1] == 'o') {
        if (dfs(i, 1)) {
            ok = true;
            break;
        }
    }

    if (ok)
        cout << "Yes" << nline;
    else
        cout << "No" << nline;
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