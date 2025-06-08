/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/problemset/problem/1931/F
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
/*--------------------------------------------------------------------------------------------------------------------------*/
#define N 200005
int n, k;
vector<int> g[N];
int buf[N], color[N];
void pre_compute() {
    
}
void dfs(int u, bool &cycle) {
    color[u] = 1;
    for (auto v : g[u]) {
        if (color[v] == 1) {
            cycle = 1;
            break;
        } else if (!color[v]) 
            dfs(v, cycle);
    }
    color[u] = 2;
}
void solve() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++)g[i].clear(), color[i] = 0;
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < n; j++) {
            cin >> buf[j];
        }
        for (int j = 1; j + 1 < n; j++) {
            g[buf[j]].push_back(buf[j + 1]);
        }
    }
    bool cycle = false;
    for (int i = 1; i <= n; i++) if (!color[i]) {
        dfs(i, cycle);
        if (cycle) {
            cout << "NO" << nline;
            return;
        }
    }
    cout << "YES" << nline;
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