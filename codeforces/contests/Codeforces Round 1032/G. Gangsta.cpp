/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/contest/2121/problem/g
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
int n;
int a[N];
ll pref0[N], pref1[N], p0[N], p1[N];
void pre_compute() {
    
}
void solve() {
    cin >> n;
    string s;
    cin >> s;
    for (int i = 0; i < n; i++) a[i] = s[i] - '0';
    for (int i = 0; i < n; i++) {
        p0[i + 1] = p0[i] + (a[i] == 0);
        p1[i + 1] = p1[i] + (a[i] == 1);
        pref0[i + 1] = pref0[i] + p0[i + 1];
        pref1[i + 1] = pref1[i] + p1[i + 1];
    }
    unordered_map<int,int,chash> difToIdx;
    difToIdx[0] = -1;
    vector<ll> dp(n + 1);
    int dif = 0;
    ll ans = 0;
    for (int i = 0; i < n; i++) {

        dif += (a[i] == 1 ? 1 : -1);
        int idx = -1;
        if (difToIdx.count(dif)) {
            idx = difToIdx[dif];
        }
        
        int l = idx + 1;
        int r = i;
        int len = r - l + 1;
        if (a[i] == 1) {
            dp[i + 1] = len * p1[i + 1] - (pref1[r] - (l - 1 < 0 ? 0 : pref1[l - 1]));
        } else {
            dp[i + 1] = len * p0[i + 1] - (pref0[r] - (l - 1 < 0 ? 0 : pref0[l - 1]));
        }
        dp[i + 1] += dp[idx + 1] + 1LL * (idx + 1) * len / 2; 
        
        ans += dp[i + 1];

        difToIdx[dif] = i;
    }
    cout << ans << nline;
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
