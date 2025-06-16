/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/contest/2118/problem/D2
*/

#include<bits/stdc++.h>
using namespace std;

#define nline '\n'
#define ll long long
#define MOD 1000000007
#define MOD1 998244353
#define LINF ((long long)1e18)
#define IINF ((int)1e9)
#define MASK(i) (1LL << (i))

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

#define N 200005
ll n, k, q;
ll p[N], d[N], a[N], order[N];
bool ans[N];
vector<pair<int,int>> g[N][2];

void pre_compute() {
    
}
bool isCycleFrom(int u, int dir, vector<vector<int>> &color, vector<vector<int>> &cycle) {
    if (cycle[u][dir] != -1) 
        return cycle[u][dir];
    color[u][dir] = 1;

    bool res = 1;
    if (!g[u][dir].size()) {
        res = 0;
    } else {
        for (auto [v, v_dir] : g[u][dir]) {
            if (color[v][v_dir] != 1) {
                if (color[v][v_dir] == 0) {
                    res &= isCycleFrom(v, v_dir, color, cycle);
                } else if (color[v][v_dir] == 2) {
                    res &= cycle[v][v_dir];
                }
            }
        }
    }
    
    color[u][dir] = 2;

    return cycle[u][dir] = res;
}
void solve() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        g[i][0].clear();
        g[i][1].clear();
        cin >> p[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> d[i];
    }
    unordered_map<ll,int,chash> difToIdx;
    for (int i = n; i >= 1; i--) {
        ll dif = ((d[i] - p[i]) % k + k) % k;
        if (difToIdx.count(dif)) {
            g[i][1].push_back({difToIdx[dif], 0});
        }
        difToIdx[dif] = i;
    }
    difToIdx.clear();
    for (int i = 1; i <= n; i++) {
        ll dif = (d[i] + p[i]) % k;
        if (difToIdx.count(dif)) {
            g[i][0].push_back({difToIdx[dif], 1});
        }
        difToIdx[dif] = i;
    }

    cin >> q;
    for (int i = 0; i < q; i++) cin >> a[i];
    iota(order, order + q, 0);
    sort(order, order + q, [&](int i, int j){
        return a[i] < a[j];
    });
    int j = n;
    difToIdx.clear();
    vector<vector<int>> color(n + 1, vector<int>(2));
    vector<vector<int>> cycle(n + 1, vector<int>(2, -1));
    for (int i = q - 1; i >= 0; i--) {
        ll x = a[order[i]];
        while (j >= 1 && p[j] >= x) {
            difToIdx[((p[j] - d[j]) % k + k) % k] = j;
            j--;
        }

        bool ok = true;
        if (difToIdx.count(x % k)) {
            ll u = difToIdx[x % k];
            if (isCycleFrom(u, 0, color, cycle))
                ok = false;
        }
        
        ans[order[i]] = ok;
    }
    for (int i = 0; i < q; i++) {
        if (ans[i])
            cout << "YES" << nline;
        else
            cout << "NO" << nline;
    }
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