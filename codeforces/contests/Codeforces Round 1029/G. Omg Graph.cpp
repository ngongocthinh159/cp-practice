/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/contest/2117/problem/G
*/

#include<bits/stdc++.h>
using namespace std;

#define nline '\n'
#define ll long long
#define MOD 1000000007
#define MOD1 998244353
#define LINF ((long long)1e18)
#define IINF ((int)1e9 + 5)

#define fastio() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
void IN_OUT() {
#ifndef ONLINE_JUDGE
freopen("Input.txt", "r", stdin);
freopen("Output.txt", "w", stdout);
#endif
}
/*--------------------------------------------------------------------------------------------------------------------------*/

#define N 200005
int n, m;
vector<int> g[N];
struct Edge {
    int u, v, w;
};
Edge e[N];
void pre_compute() {
    
}
void dijkstra(int src, vector<int> &opt) {
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<>> q;
    opt[src] = 0;
    q.push({0, src});
    while (q.size()) {
        auto [w_u, u] = q.top();
        q.pop();
        for (auto i : g[u]) {
            int v = e[i].u ^ e[i].v ^ u;
            int w_uv = e[i].w;
            if (opt[v] > max(w_u, w_uv)) {
                opt[v] = max(w_u, w_uv);
                q.push({opt[v], v});
            }
        }
    }
}
void solve() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) g[i].clear();

    for (int i = 0; i < m; i++) {
        cin >> e[i].u >> e[i].v >> e[i].w;
        g[e[i].u].push_back(i);
        g[e[i].v].push_back(i);
    }
    vector<int> opt1(n + 1, IINF);
    vector<int> opt2(n + 1, IINF);
    dijkstra(1, opt1);
    dijkstra(n, opt2);
    ll ans = LINF;
    for (int i = 0; i < m; i++) {
        int u = e[i].u;
        int v = e[i].v;
        ans = min(ans, 1LL*e[i].w + max(e[i].w, max(opt1[u], opt2[v])));
        ans = min(ans, 1LL*e[i].w + max(e[i].w, max(opt1[v], opt2[u])));
    }
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