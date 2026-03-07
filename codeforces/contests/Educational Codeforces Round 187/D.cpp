/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/contest/2203/problem/D
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

#define N 2000005
int n, m;
int a[N], b[N], fa[N], fb[N], d[N], bufa[N], bufb[N];
bool vis[N];
void pre_compute() {
    
}
void solve() {
    cin >> n >> m;
    for (int i=0; i < n;i++) cin >> a[i], fa[a[i]]++;
    for (int i=0; i < m;i++) cin >> b[i], fb[b[i]]++;

    for (int i = 0; i < n; i++) if (!vis[a[i]]) {
        vis[a[i]] = 1;
        for (int j = a[i]; j <= m + n; j += a[i]) if (fb[j]) d[j] += fa[a[i]];
    }
    int x = 0, y = 0, z = 0;
    for (int i =0;i < m; i++) {
        if (d[b[i]] == 0) x ++;
        else if (d[b[i]] == n) z ++;
        else y ++;
    }

    if ((!(y&1) && z > x) || ((y&1) && z >= x)) {
        cout << "Alice" << nline;
    } else {
        cout << "Bob" << nline;
    }

    for (int i= 0; i < n;i++) fa[a[i]] = 0, vis[a[i]] = 0;
    for (int i = 0; i < m; i++) fb[b[i]] = 0, d[b[i]] = 0;
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