/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/problemset/problem/1760/G
*/

#include<bits/stdc++.h>
using namespace std;

#define nline '\n'
#define ll long long
#define MOD 1000000007
#define MOD1 998244353
#define LINF ((long long)1e18)
#define IINF ((int)1e9)

#define fastio() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
void IN_OUT() {
#ifndef ONLINE_JUDGE
freopen("Input.txt", "r", stdin);
freopen("Output.txt", "w", stdout);
#endif
}
struct custom_hash {static uint64_t splitmix64(uint64_t x) {x += 0x9e3779b97f4a7c15;x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;x = (x ^ (x >> 27)) * 0x94d049bb133111eb;return x ^ (x >> 31);}size_t operator()(uint64_t x) const {static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();return splitmix64(x + FIXED_RANDOM);}}; // https://codeforces.com/blog/entry/62393

/*--------------------------------------------------------------------------------------------------------------------------*/

#define N 100005
vector<pair<int,int>> g[N];
int n, a, b;
void pre_compute() {
    
}
void solve() {
    cin >> n >> a >> b;
    for (int i = 1; i <= n; i++) g[i].clear();

    for (int i = 0; i < n - 1; i++) {
        int u, v, w; cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }
    bool ok = false;
    auto bfs1 = [&](int src, unordered_set<int,custom_hash> &S, int forbid = -1){
        deque<pair<int,int>> q;
        vector<bool> vis(n + 1);
        q.push_front({src, 0});
        vis[src] = 1;
        while (q.size()) {
            for (int sz = q.size(); sz; sz--) {
                auto [u, w_u] = q.back();
                q.pop_back();
                for (auto [v, w_uv] : g[u]) { 
                    if (!vis[v] && v != forbid) {
                        S.insert(w_u ^ w_uv);
                        vis[v] = 1;
                        q.push_front({v, w_u ^ w_uv});
                    } else if (v == forbid) {
                        if ((w_u ^ w_uv) == 0) ok = true;
                    }
                }
            }
        }
    };

    unordered_set<int,custom_hash> S1;
    S1.insert(0);
    bfs1(a, S1, b);

    if (ok) {
        cout << "YES" << nline;
        return;
    }
    
    unordered_set<int,custom_hash> S2;
    bfs1(b, S2, -1);
    for (auto x : S1) if (S2.count(x)) {
        cout << "YES" << nline;
        return;
    }
    cout << "NO" << nline;
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