/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/problemset/problem/1709/D
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

#define M 200005
#define LOG 19
int n, m, q;
int a[M];
int rmq[LOG][M];
void pre_compute() {
    
}
void solve() {
    cin >> n >> m;
    for (int i =0; i < m;i ++) cin>> a[i], rmq[0][i] = a[i];
    for (int j = 1; j < LOG; j++)
        for (int i = 0; i + MASK(j) - 1 < m; i++) rmq[j][i] = max(rmq[j - 1][i], rmq[j - 1][i + MASK(j - 1)]);
    auto query = [&](int l,int r) -> int {
        int msb = 32 - __builtin_clz(r - l + 1) - 1;
        return max(rmq[msb][l], rmq[msb][r - MASK(msb) + 1]);
    };
    cin >> q;
    int x1, y1, x2, y2, k;
    for (int i = 0;i < q;i++) {
        cin >> x1 >> y1 >> x2 >> y2 >> k;
        y1--, y2--;
        if (y1 > y2) {
            swap(x1, x2);
            swap(y1, y2);
        }
        if (x1%k != x2%k || y1%k != y2%k) {
            cout << "NO" << nline;
            continue;
        }
        ll mul = (n - x1) / k;
        x1 += mul * k;
        if (query(y1, y2) < x1) {
            cout << "YES" << nline;
        } else 
            cout << "NO" << nline;
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