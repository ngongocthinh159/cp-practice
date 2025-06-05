/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/problemset/problem/2006/A
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

#define N 100005
int n, cnt[4];
string color;
vector<int> g[N];
void pre_compute() {
    
}
void dfs(int u, int p) {
    if (g[u].size() == 1 && g[u][0] == p) {
        if (color[u] == '0') cnt[0]++;
        if (color[u] == '1') cnt[1]++;
        if (color[u] == '?') cnt[2]++;
    } else if (u != 1 && color[u] == '?') {
        cnt[3]++;
    }
    for (auto v : g[u]) if (v != p) {
        dfs(v, u);
    }
}
int cal_score() {
    int score = 0;
    if (color[1] != '?') {
        int root_color = color[1] - '0';
        score = cnt[root_color ^ 1] + (cnt[2] + 1)/2;
    } else {
        if (cnt[0] == cnt[1]) {
            if (cnt[3]&1)
                score = cnt[0] + (cnt[2] + 1)/2;
            else
                score = cnt[0] + cnt[2]/2;
        } else {
            int root_color = (cnt[0] > cnt[1]) ? 1 : 0;
            score = cnt[root_color ^ 1] + cnt[2]/2;
        }
    }
    return score;
}
void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++) g[i].clear();
    cnt[0] = cnt[1] = cnt[2] = cnt[3] = 0;
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    cin >> color;
    color = " " + color;
    dfs(1, -1);
    cout << cal_score() << nline;
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