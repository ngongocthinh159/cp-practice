/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/contest/888/problem/E
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

#define N 42
int n, m;
int a[N];
int L[300000], R[300000], topL = 0, topR = 0;
void pre_compute() {
    
}
void gen(int i, int len, int mod, int *L, int &top) {
    if (i == len) {
        L[top++] = mod; 
        return;
    }
    gen(i + 1, len, mod, L, top);
    gen(i + 1, len, (mod + a[i]) % m, L, top);
}
void solve() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) cin >> a[i];
    int half = (n + 1)/2;
    gen(0, half, 0, L, topL);
    gen(half, n, 0, R, topR);
    sort(R, R + topR);
    int ans = 0;
    for (int i = 0; i < topL; i++) {
        int lmod = L[i];
        int tar = m - lmod;
        auto it = lower_bound(R, R + topR, tar);
        int idx = it - R;
        if (idx != 0) {
            idx--;
            ans = max(ans, lmod + R[idx]);
        }
    }
    cout << ans << nline;
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