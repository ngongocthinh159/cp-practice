/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/contest/1213/problem/G
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
int n, q;
struct DSU {
    vector<int> parent;
    vector<int> size;
    DSU(int n, bool auto_make_set = true) {
        parent.resize(n + 1);
        size.resize(n + 1);
        if (auto_make_set) {
            for (int i = 0; i <= n; i++) parent[i] = i, size[i] = 1;
        }
    }
    void make_set(int x) {
        parent[x] = x;
        size[x] = 1;
    }
    int find(int x) {
        return x == parent[x] ? x : parent[x] = find(parent[x]);
    }
    bool same_set(int a, int b) {
        return find(a) == find(b);
    }
    void unite(int a, int b) {
        int ra = find(a);
        int rb = find(b);
        if (ra != rb) {
            if (size[ra] < size[rb]) swap(ra,rb);
            size[ra] += size[rb];
            parent[rb] = ra;
        }
    }
    int find_size(int x) {
        return size[find(x)];
    }
};
struct Edge {
    int u, v, w;
};
Edge e[N];
int order[N], queries[N];
ll ans[N];
void pre_compute() {
    
}
void solve() {
    cin >> n  >> q;
    for (int i = 0; i < n - 1; i ++) {
        cin >> e[i].u >> e[i].v >> e[i].w;
    }
    for (int i = 0; i < q; i++) {
        cin >> queries[i];
    }
    sort(e, e + n - 1, [&](Edge &e1, Edge &e2) {
        return e1.w < e2.w;
    });
    iota(order, order + q, 0);
    sort(order, order + q, [&](int i, int j) {
        return queries[i] < queries[j];
    });
    DSU dsu(n + 5);
    int j = 0;
    ll tot = 0;
    for (int i = 0; i < q; i++) {
        while (j < n - 1 && e[j].w <= queries[order[i]]) {
            int u = e[j].u;
            int v = e[j].v;
            if (!dsu.same_set(u, v)) {
                tot += 1LL * dsu.find_size(u) * dsu.find_size(v);
                dsu.unite(u, v);
            }
            j++;
        }
        ans[order[i]] = tot;
    }
    for (int i = 0; i < q; i++) cout << ans[i] << ' ';
    cout << nline;
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