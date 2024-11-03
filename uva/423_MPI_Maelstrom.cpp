/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=364
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define nline "\n"
int n;
const ll LINF = 1e18;
vector<vector<pair<int, ll>>> g;
ll dijkstra(int src) {
    vector<ll> dist(n + 1, LINF);
    dist[src] = 0;
    set<pair<ll, int>> S;
    S.insert({0, src});
    while (S.size()) {
        auto p = *S.begin();
        S.erase(S.begin());
        ll w_u = p.first;
        int u = p.second;
        for (auto _p : g[u]) {
            int v = _p.first;
            ll w_uv = _p.second;
            if (dist[v] > w_u + w_uv) {
                S.erase({dist[v], v});
                dist[v] = w_u + w_uv;
                S.insert({dist[v], v});
            }
        }
    }
    ll ans = -1;
    for (int i = 1; i <= n; i++) ans = max(ans, dist[i]);
    return ans;
}
ll stoll(string &s) {
    ll res = 0;
    ll pow = 1;
    for (int i = s.size() - 1; i>= 0; i--) {
        res += (s[i] - '0')*pow;
        pow = pow*10;
    }
    return res;
}
void solve() {
    g.clear();
    g.resize(n + 1);
    string line, cur;
    for (int i = 2; i <= n; i++) {
        getline(cin, line);
        stringstream ss(line);
        for (int j = 1; j <= i - 1; j++) {
            ss >> cur;
            if (cur != "x") {
                ll w = stoll(cur);
                g[i].push_back({j, w});
                g[j].push_back({i, w});
            }
        }
    }
    cout << dijkstra(1) << nline;
}

int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#ifndef ONLINE_JUDGE
    freopen("Input.txt", "r", stdin);
    freopen("Output.txt", "w", stdout);
#endif
    string tmp;
    getline(cin, tmp);
    while (tmp.size()) {
        n = stoll(tmp);
        solve();
        getline(cin, tmp);
    }
}
