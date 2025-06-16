/**
 * Author: Thinh Ngo Ngoc
 * Solution for: 
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

#define N 505
ll n, k, q;
ll p[N], d[N];
vector<pair<int,int>> g[N][2];

void pre_compute() {
    
}
void dfs(int u, int dir, bool &cycle, vector<vector<int>> &color) {
    color[u][dir] = 1;
    for (auto [v, dir_v] : g[u][dir]) {
        if (color[v][dir_v] == 1) {
            cycle = true;
            return;
        } else if (color[v][dir_v] == 0) {
            dfs(v, dir_v, cycle, color);
            if (cycle) return;
        }
    }
    color[u][dir] = 2;
}
void solve() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        g[i][0].clear();
        g[i][1].clear();
        cin >> p[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> d[i];
    }
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if ((d[i] + p[j] - p[i]) % k == d[j]) {
                g[i][1].push_back({j, 0});
                break;
            }
        }
        for (int j = i - 1; j >= 1; j--) {
            if ((d[i] + p[i] - p[j]) % k == d[j]) {
                g[i][0].push_back({j, 1});
                break;
            }
        }
        
    }

    cin >> q;
    for (int i = 0; i < q; i++) {
        ll x; cin >> x;
        auto it = lower_bound(p + 1, p + n + 1, x);
        int idx = it - p;
        if (idx == n + 1) {
            cout << "YES" << nline;
            continue;
        }

        bool ok = true;
        vector<vector<int>> color(n + 1, vector<int>(2));
        for (int j = idx; j <= n; j++) {
            if ((p[j] - x) % k == d[j]) {
                bool cycle = false;
                dfs(j, 0, cycle, color);
                if (cycle) 
                    ok = false;
                break;
            }
        }
        
        if (ok)
            cout << "YES" << nline;
        else
            cout << "NO" << nline;
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