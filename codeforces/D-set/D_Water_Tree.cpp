/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/problemset/problem/343/D
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

// T: the data type 1 that stored in the Node, might change
// T also used for update query in this implementation
template <typename Node, typename T>
struct SegmentTree {
    int n;
    vector<Node> segtree;

    void build(int idx, int s, int e, ll defaultValue) {
        if (s == e) {
            segtree[idx] = Node(defaultValue);
            return;
        }
        int m = (s + e)/2;
        build(2*idx, s, m, defaultValue);
        build(2*idx, m + 1, e, defaultValue);
        segtree[idx] = Node::merge(segtree[2*idx], segtree[2*idx + 1]);
    }

    void build(int idx, int s, int e, vector<T>& arr) {
        if (s == e) {
            segtree[idx] = Node(arr[s]);
            return;
        }
        int m = (s + e)/2;
        build(2*idx, s, m, arr);
        build(2*idx, m + 1, e, arr);
        segtree[idx] = Node::merge(segtree[2*idx], segtree[2*idx + 1]);
    }

    void build(int idx, int s, int e, T *arr) {
        if (s == e) {
            segtree[idx] = Node(arr[s]);
            return;
        }
        int m = (s + e)/2;
        build(2*idx, s, m, arr);
        build(2*idx, m + 1, e, arr);
        segtree[idx] = Node::merge(segtree[2*idx], segtree[2*idx + 1]);
    }

    void push_down(int idx, int s, int e) {
        if (segtree[idx].lazyType != Node::EMPTY) {
            int m = (s + e)/2;
            segtree[2*idx].apply(s, m, segtree[idx].lazyVal, segtree[idx].lazyType);
            segtree[2*idx + 1].apply(m + 1, e, segtree[idx].lazyVal, segtree[idx].lazyType);
            segtree[idx].clearLazy();
        }
    }

    void update(int idx, int s, int e, int l, int r, T updateVal, typename Node::LazyType lazyType) {
        if (s > r || l > e || s > e || l > r) return;
        if (l <= s && e <= r) {
            segtree[idx].apply(s, e, updateVal, lazyType);
            return;
        }
        push_down(idx, s, e);
        int m = (s + e)/2;
        update(2*idx, s, m, l, r, updateVal, lazyType);
        update(2*idx + 1, m + 1, e, l, r, updateVal, lazyType);
        segtree[idx] = Node::merge(segtree[2*idx], segtree[2*idx + 1]);
    }

    Node query(int idx, int s, int e, int l, int r) {
        if (s > r || l > e || s > e || l > r) 
            return Node::sentinal_query_value();
        if (l <= s && e <= r) 
            return segtree[idx];
        push_down(idx, s, e);
        int m = (s + e)/2;
        Node lans = query(2*idx, s, m, l, r);
        Node rans = query(2*idx + 1, m + 1, e, l, r);
        return Node::merge(lans, rans);
    }
public:
    SegmentTree() {}

    SegmentTree(int _n, ll defaultValue = 0) : n(_n) {
        segtree.resize((n&(n - 1)) == 0 ? 2 * n : 4 * n);
        if (defaultValue)
            build(1, 0, n - 1, defaultValue);
    }

    SegmentTree(vector<T>& arr) {
        n = arr.size();
        segtree.resize((n&(n - 1)) == 0 ? 2 * n : 4 * n);
        build(1, 0, n - 1, arr);
    }

    SegmentTree(int _n, T *arr) : n(_n) {
        segtree.resize((n&(n - 1)) == 0 ? 2 * n : 4 * n);
        build(1, 0, n - 1, arr);
    }

    void update(int l, int r, T updateVal, typename Node::LazyType lazyType) {
        update(1, 0, n - 1, l, r, updateVal, lazyType);
    }

    Node query(int l, int r) {
        return query(1, 0, n - 1, l, r);
    }
};

struct Node {
    enum LazyType { EMPTY, PLUS, SET }; // update type might change

    // Type 1 data might change
    ll sum = 0;

    // Type 2 data might change
    LazyType lazyType = EMPTY;
    ll lazyVal = 0;

    Node() {}

    // constructor for type 1 data might change
    Node(ll x) {
        sum = x;
    }

    // push up logic might change
    static Node merge(Node& l, Node& r) {
        Node res;
        res.sum = l.sum + r.sum;
        return res;
    }

    // default value when query out of range might change
    static Node sentinal_query_value() {
        Node res;
        res.sum = 0;
        return res;
    }

    // apply range update to current node
    // put a lazy tag on current node (later push down)
    // might change
    void apply(int s, int e, ll updateVal, LazyType _type) {
        if (_type == SET) {
            sum = updateVal * (e - s + 1);
            lazyVal = updateVal;
            lazyType = SET;
        }
    }

    // clear lazy value after pushing down lazy val from current node
    void clearLazy() {
        lazyType = EMPTY;
        lazyVal = 0;
    }
};

// SegmentTree must support lazy propagation (if HLD requires segment update on chains)
template <typename SegmentTree>
struct HLD {
    int n, T;
    vector<int> big, chain, par, depth, euler, pos, out;
    SegmentTree segtree;

    int dfs_sz(int u, int p, vector<vector<int>>& g) {
        big[u] = -1;
        int mxc = 0;
        int u_sz = 1;
        for (auto v : g[u]) if (v != p) {
            par[v] = u;
            depth[v] = depth[u] + 1;
            int v_sz = dfs_sz(v, u, g);
            u_sz += v_sz;
            if (mxc < v_sz)
                mxc = v_sz, big[u] = v;
        }
        return u_sz;
    }

    void dfs_chain(int u, int p, int top, vector<int>& val, vector<vector<int>> &g) {
        euler[++T] = val[u];
        pos[u] = T;
        chain[u] = top;
        if (big[u] != -1)
            dfs_chain(big[u], u, top, val, g);
        for (auto v : g[u]) if (v != p && v != big[u])
            dfs_chain(v, u, v, val, g);
        out[u] = T;
    }

public:
    HLD(vector<vector<int>>& g, vector<int> &val, int root = 1) {
        n = g.size();
        T = -1;
        big.resize(n + 1);
        chain.resize(n + 1);
        par.resize(n + 1);
        depth.resize(n + 1);
        pos.resize(n + 1);
        euler.resize(n + 1);
        out.resize(n + 1);

        dfs_sz(root, -1, g);
        dfs_chain(root, -1, root, val, g);
        segtree = SegmentTree(euler);
    }

    int query_lca(int u, int v) {
        while (chain[u] != chain[v]) {
            if (depth[chain[u]] < depth[chain[v]]) swap(u, v);
            u = par[chain[u]];
        }
        if (depth[u] > depth[v]) swap(u, v);
        return u;
    }

    int query(int u, int v) {
        int res = 0;
        while (chain[u] != chain[v]) {
            if (depth[chain[u]] < depth[chain[v]]) swap(u, v);
            res += segtree.query(pos[chain[u]], pos[u]).sum;
            u = par[chain[u]];
        }
        if (depth[u] > depth[v]) swap(u, v);
        res += segtree.query(pos[u], pos[v]).sum;
        
        // u is LCA now

        return res;
    }

    void update_path(int u, int v, int val) {
        while (chain[u] != chain[v]) {
            if (depth[chain[u]] < depth[chain[v]]) swap(u, v);
            segtree.update(pos[chain[u]], pos[u], val, Node::SET);
            u = par[chain[u]];
        }
        if (depth[u] > depth[v]) swap(u, v);
        segtree.update(pos[u], pos[v], val, Node::SET);

        // u is LCA now
    }

    void update_subtree(int u, int val) {
        segtree.update(pos[u], out[u], val, Node::SET);
    }

    int query_vertex(int u) {
        return segtree.query(pos[u], pos[u]).sum;
    }
};

int n, q;
void pre_compute() {
    
}
void solve() {
    cin >> n;
    vector<vector<int>> g(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<int> val(n + 1, 0);
    HLD<SegmentTree<Node, int>> hld(g, val);
    cin >> q;
    int t, v;
    for (int i = 0; i < q; i++) {
        cin >> t >> v;
        if (t == 1) {
            hld.update_subtree(v, 1);
        } else if (t == 2) {
            hld.update_path(v, 1, 0);
        } else {
            cout << hld.query_vertex(v) << nline;
        }
    }
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