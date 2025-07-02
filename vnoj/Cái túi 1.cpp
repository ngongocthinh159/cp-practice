/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://oj.vnoi.info/problem/dttui1
 * 
 * Topic: https://wiki.vnoi.info/algo/basic/meet-in-the-middle.md
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

#define N 45
ll n, M;
ll w[N], v[N];
void pre_compute() {
    
}
void gen(int i, int len, vector<pair<ll,ll>> &A, ll cur_w, ll cur_v) {
    if (i == len) {
        A.push_back({cur_w, cur_v});
        return;
    }
    gen(i + 1, len, A, cur_w, cur_v);
    if (cur_w + w[i] <= M) gen(i + 1, len, A, cur_w + w[i], cur_v + v[i]);
}
void solve() {
    cin >> n >> M;
    for (int i = 0; i < n; i++) cin >> w[i] >> v[i];
    vector<pair<ll,ll>> A, B;
    A.reserve(1e6 + 1e5);
    B.reserve(1e6 + 1e5);
    int half = (n + 1)/2;
    gen(0, half, A, 0, 0);
    gen(half, n, B, 0, 0);
    sort(A.begin(), A.end());
    sort(B.begin(), B.end());
    vector<ll> mx(B.size());
    for (int i = 0; i < (int) B.size(); i++) {
        mx[i] = B[i].second;
        if (i != 0)
            mx[i] = max(mx[i], mx[i - 1]);
    }
    ll ans = 0;
    for (int i = 0, j = (int) B.size() - 1; i < (int) A.size(); i++) {
        while (A[i].first + B[j].first > M) j--;
        ans = max(ans, A[i].second + mx[j]);
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