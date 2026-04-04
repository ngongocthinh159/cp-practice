/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/contest/2210/problem/D
*/

// #include<bits/stdc++.h>
#include "bits/stdc++.h"
using namespace std;

#define nline '\n'
#define ll long long
#define MOD 1000000007
#define MOD1 998244353
#define LINF ((long long)1e18)
#define IINF ((int)1e9)
#define MASK(i) (1LL << (i))
#define all(v) (v).begin(), (v).end()


template<class X, class Y>
bool minimize(X &x, const Y &y) {
    if (x > y) {
        x = y;
        return true;
    } else return false;
}
template<class X, class Y>
bool maximize(X &x, const Y &y) {
    if (x < y) {
        x = y;
        return true;
    } else return false;
}

#define fastio() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
void IN_OUT() {
#ifndef ONLINE_JUDGE
freopen("Input.txt", "r", stdin);
freopen("Output.txt", "w", stdout);
#endif
}
struct chash {static uint64_t splitmix64(uint64_t x) {x += 0x9e3779b97f4a7c15;x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;x = (x ^ (x >> 27)) * 0x94d049bb133111eb;return x ^ (x >> 31);}size_t operator()(uint64_t x) const {static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();return splitmix64(x + FIXED_RANDOM);}}; // https://codeforces.com/blog/entry/62393
struct chashp {static uint64_t splitmix64(uint64_t x) {x += 0x9e3779b97f4a7c15;x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;x = (x ^ (x >> 27)) * 0x94d049bb133111eb;return x ^ (x >> 31);}size_t operator()(pair<uint64_t,uint64_t> x) const {static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();return splitmix64(x.first + FIXED_RANDOM)^(splitmix64(x.second + FIXED_RANDOM) >> 1);}}; // https://codeforces.com/blog/entry/62393
/*--------------------------------------------------------------------------------------------------------------------------*/

#define N 500005
int buf[N];
struct Node {
    int l, r;
    vector<Node*> child;
};
void pre_compute() {
    
}
Node* dfs(int l, int r) {
    Node* root = new Node;
    root->l = l;
    root->r = r;
    int cl = l + 1;
    while (cl < r) {
        int cr = buf[cl];
        root->child.push_back(dfs(cl, cr));
        cl = cr + 1;
    }
    return root;
}
Node* buildTree(string &ss) {
    string s = "(" + ss + ")";
    int n = s.size();
    vector<int> st;
    for (int i = 0; i < n; i++) {
        if (s[i] == '(') st.push_back(i);
        else {
            buf[st.back()] = i;
            st.pop_back();
        }
    }
    return dfs(0, n - 1);
}
void dfs2(Node* root, int &d, int &leave, int curd, bool ok) {
    if (ok) d = max(d, curd);
    if (root->child.empty()) leave++;
    for (auto c : root->child) {
        dfs2(c, d, leave, curd + 1, ok & (root->child.size() <= 1));
    }
}
void solve() {
    int n; cin >> n;
    string s, t;
    cin >> s >> t;
    auto rs = buildTree(s);
    auto rt = buildTree(t);
    int ds = 0, ls = 0, dt = 0, lt = 0;
    dfs2(rs, ds, ls, 0, true);
    dfs2(rt, dt, lt, 0, true);
    if (ls == lt && ds == dt) {
        cout << "YES" << nline;
    } else 
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