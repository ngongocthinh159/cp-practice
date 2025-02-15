#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define nline "\n"

struct DSU {
    unordered_map<int,int> parent, size, parity;
    DSU() {}
    void make_set(int x) {
        if (size[x] == 0) {
            parent[x] = x;
            size[x] = 1;
        }
    }
    int find(int x) {
        if (x == parent[x]) return x;
        int par = find(parent[x]);
        parity[x] = parity[parent[x]]^parity[x];
        return parent[x] = par;
    }
    void unite(int a, int b) {
        int ra = find(a);
        int rb = find(b);
        if (ra != rb) {
            if (size[ra] < size[rb]) swap(ra,rb), swap(a, b);
            size[ra] += size[rb];
            parent[rb] = ra;
            parity[rb] = parity[a]^parity[b]^1;
        }
    }
    int get_parity(int x) {
        find(x);
        return parity[x];
    }
    int get_size(int x) {
        return size[find(x)];
    }
};
int m;
void solve() {
    cin >> m;
    DSU dsu;
    unordered_set<int> S;
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        dsu.make_set(u);
        dsu.make_set(v);
        dsu.unite(u, v);
        S.insert(u);
        S.insert(v);
    }
    unordered_map<int,int> par_to_same;
    unordered_map<int,int> par_to_size;

    for (auto x : S) {
        int px = dsu.find(x);
        if (dsu.get_parity(x) == 0) par_to_same[px]++;
        par_to_size[px] = dsu.get_size(px);
    }
    ll ans = 0;
    for (auto [par, cnt] : par_to_same) {
        ans += max(cnt, par_to_size[par] - cnt);
    }
    cout << ans << nline;
}

int main() {
	ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
	int T = 1;
	cin >> T;
	int cases = 0;
	while (T--) {
        cout << "Case " << ++cases << ": ";
        solve();
    }
}
