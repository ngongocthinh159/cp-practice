/**
 * Author: Thinh Ngo Ngoc
 * Solution for: 
*/

#include "bits/stdc++.h"
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

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
ll expo(ll a, ll b, ll mod = MOD) {if (a==0) return 1%mod; ll res = 1; while (b > 0) {if (b & 1)res = (res * a) % mod; a = (a * a) % mod; b = b >> 1;} return res;} // a = 0 return 0 | b = 0 return 1
ll __gcd__(ll a, ll b) {if (!a || !b) return a | b; unsigned shift = __builtin_ctz(a | b); a >>= __builtin_ctz(a); do { b >>= __builtin_ctz(b); if (a > b) swap(a, b); b -= a; } while (b); return a << shift;} // only a >= 0 && b >= 0
ll gcd(ll a, ll b) {a = abs(a); b = abs(b); return __gcd__(a, b);} // get abs(a), abs(b) in case a < 0 || b < 0
typedef tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag, tree_order_statistics_node_update > pbds; // find_by_order, order_of_key
/*--------------------------------------------------------------------------------------------------------------------------*/

ll dp[505][1 << 10][3][2][2];
void pre_compute() {
    
}
void solve() {
    string s;
    cin >> s;
    int n = s.size();
    s = " " + s;
    int b[n + 1]{};
    for (int i = 1; i <= n; i++) b[i] = s[i] - '0';
    vector<ll> _10powmod(n + 1);
    _10powmod[0] = 1;
    for (int i = 1; i <= n; i++) _10powmod[i] = _10powmod[i - 1] * 10 % 3;

    dp[0][0][0][0][0] = 1;

    for (int i = 0; i < n; i++)
        for (int mask = 0; mask < (1 << 10); mask++) {
            for (int cmod = 0; cmod < 3; cmod++)
                for (int smaller = 0; smaller < 2; smaller++)
                    for (int start = 0; start < 2; start++) if (dp[i][mask][cmod][smaller][start]) {
                        int upper = smaller ? 9 : b[i + 1];
                        for (int j = 0; j <= upper; j++) {
                            int nmask = mask;
                            if (j == 0) {
                                if (start) nmask |= (1 << j);
                            } else nmask |= (1 << j);

                            int nsmaller = smaller | (j < b[i + 1]);
                            int nmod = (cmod + _10powmod[n - 1 - i] * j) % 3;
                            int nstart = start | (j != 0);
                            
                            dp[i + 1][nmask][nmod][nsmaller][nstart] += dp[i][mask][cmod][smaller][start];
                            if (dp[i + 1][nmask][nmod][nsmaller][nstart] >= MOD1) 
                                dp[i + 1][nmask][nmod][nsmaller][nstart] -= MOD1;
                        }
                    }
        }
    ll ans = 0;
    for (int mask = 0; mask < (1 << 10); mask++) {
        for (int cmod = 0; cmod < 3; cmod++) {
            int cnt = 0;
            if (cmod == 0) cnt++;
            if ((mask >> 3) & 1) cnt++;
            if (__builtin_popcount(mask) == 3) cnt++;

            if (cnt == 1) {
                ans += dp[n][mask][cmod][0][1];
                if (ans >= MOD1) ans -= MOD1;
                ans += dp[n][mask][cmod][1][1];
                if (ans >= MOD1) ans -= MOD1;
            }
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