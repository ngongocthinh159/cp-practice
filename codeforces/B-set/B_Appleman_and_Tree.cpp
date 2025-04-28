/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/problemset/problem/461/B
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
int n, c[N];
ll dp[N][2];
vector<int> g[N];

/*  reference: https://abitofcs.blogspot.com/2014/12/dynamic-programming-on-tree-forming-up.html

    Solution:
    The dynamic programming approach to this tree problem is quite interesting. The focus of the problem is to find the number of ways such that the subtrees formed have one and only one black node each. The idea behind the DP might not be that intuitive though, and in a sense its implementation is also not as straight forward, although its final implementation looks very simple.

    
    Let's consider node u
    . Node u
    has a few children vi
    . To solve the problem, we need to keep track of two information:
    1. The number of ways such that the subtree that is rooted at u
    has no black nodes at all, while the remaining subtrees formed have exactly one black node each. Call this W[u].
    2. Symmetrically, the number of ways such that the subtree that is rooted at u
    has exactly one black nodes, and the remaining subtrees formed have also exactly one black node each. Call this B[u].

    Now, to compute W[u] and B[u], initialize W[u] = 1, B[u] = 0 if color[u] is white, otherwise W[u] = 0, B[u] = 1. Then, we iterate through the children of u one by one, for each vi
    for i=1…n
    :
    1. Suppose we already know what is W[v] and B[v].
    2. Let W' and B' be W[u] and B[u] after we consider node v. Set W' = 0 and B' = 0.
    3. We have two case to consider:
    Case 1: v is included in the subtree rooted at u.
        then W' += W[u] * W[v] (so that the subtree has no black node)
        and B' += B[u] * W[v] + B[v] * W[u] (since the subtree must only have one black node).
    Case 2: v forms a separate subtree rooted at v that is not a part of subtree rooted at u.
        then W' += W[u] * B[v] (since the subtree rooted at v must have one black node)
        and B' += B[u] * B[v] (same reason. all other subtree must have one black node).
    4. Finally update W[u] = W', B[u] = B'.
*/

void pre_compute() {
    
}
void dfs(int u, int p) {
    dp[u][0] = !c[u];
    dp[u][1] = c[u];

    for (auto v : g[u]) if (v != p) {
        dfs(v, u);

        ll W = 0, B = 0;

        W += dp[u][0] * dp[v][0] % MOD;
        W %= MOD;
        W += dp[u][0] * dp[v][1] % MOD;
        W %= MOD;

        B += dp[u][0] * dp[v][1] % MOD;
        B %= MOD;
        B += dp[u][1] * dp[v][0] % MOD;
        B %= MOD;
        B += dp[u][1] * dp[v][1] % MOD;
        B %= MOD;

        dp[u][0] = W;
        dp[u][1] = B;
    }
}
void solve() {
    cin >> n;
    for (int i = 2; i <= n; i++) {
        int p; cin >> p;
        p++;
        g[i].push_back(p);
        g[p].push_back(i);
    }
    for (int i = 1; i <= n; i++) cin >> c[i];
    dfs(1, -1);
    cout << dp[1][1] << nline;
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