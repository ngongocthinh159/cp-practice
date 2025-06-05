/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/problemset/problem/2041/D
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

int n, m;
vector<pair<int,int>> moves = {{1,0},{0,1},{-1,0},{0,-1}};
void pre_compute() {
    
}
void solve() {
    cin >> n >> m;
    vector<string> g(n, string(m, ' '));
    int xs, ys, xd, yd;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            cin >> g[i][j];
            if (g[i][j] == 'S') xs = i, ys = j;
            if (g[i][j] == 'T') xd = i, yd = j;
        }
    vector<vector<vector<vector<int>>>> dp(n,
        vector<vector<vector<int>>>(m, 
            vector<vector<int>>(4,
                vector<int>(4, IINF))));
    deque<pair<pair<int,int>,pair<int,int>>> q;
    for (int i = 0; i < 4; i++) {
        dp[xs][ys][i][0] = 0;
        q.push_front({{xs, ys}, {i, 0}});
    }
    int level = 0;
    while (q.size()) {
        for (int sz = q.size(); sz; sz--) {
            auto p = q.back();
            q.pop_back();
            int i, j, lastC, rep;
            tie(i, j) = p.first;
            tie(lastC, rep) = p.second;
            for (int k = 0; k <(int) moves.size(); k++) {
                int I = i + moves[k].first;
                int J = j + moves[k].second;
                if (0 <= I && I < n && 0 <= J && J < m && g[I][J] != '#') {
                    int nrep = k == lastC ? rep + 1 : 1;
                    if (nrep <= 3) {
                        if (dp[I][J][k][nrep] > dp[i][j][lastC][rep] + 1) {
                            dp[I][J][k][nrep] = dp[i][j][lastC][rep] + 1;
                            q.push_front({{I, J}, {k, nrep}});
                            if (I == xd && J == yd) {
                                cout << dp[I][J][k][nrep] << nline;
                                return;
                            }
                        }
                    }
                }
            }
        }
        level++;
    }
    cout << -1 << nline;
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