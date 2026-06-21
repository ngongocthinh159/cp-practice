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

#define N 200005
ll fact[N];
void pre_compute() {
    fact[0] = 1;
    for (int i = 1; i < N; i++) fact[i] = fact[i - 1] * i % MOD1;
}
vector<ll> findDivisors(ll n) {
    vector<ll> res;
    ll bound = sqrt(n);
    for (int i = 2; i <= bound; i++) if (n % i == 0) {
        ll d1 = i;
        res.push_back(d1);

        ll d2 = n / i;
        if (d2 != d1) {
            res.push_back(d2);
        }
    }
    res.push_back(1);
    res.push_back(n);
    sort(all(res));
    return res;
}
void add(ll &x, ll y) {
    x += y;
    if (x >= MOD1) x -= MOD1;
}
void solve() {
    ll n; cin >> n;
    if (n == 1) {
        cout << 1 << nline;
        return;
    }
    auto divisors = findDivisors(n);
    int sz = int(divisors.size());
    unordered_map<ll,int> toIdx;
    unordered_map<int,ll> toVal;
    int idx = 0;
    for (auto x : divisors) {
        toIdx[x] = idx;
        toVal[idx] = x;
        idx++;
    }

    int D = 17; // max distinct length of divisor sequence 
    vector<vector<ll>> dpCnt(D + 1, vector<ll>(sz + 1)); // dp[len][productIdx]: number of subsequence of divisors that has len divisors and product = productIdx
    vector<vector<ll>> dpSum(D + 1, vector<ll>(sz + 1)); // sum of such those subsequence
    
    dpCnt[0][0] = 1;
    dpCnt[1][0] = 1;
    dpSum[1][0] = 1;

    for (int i = 1; i < sz; i++) {
        auto ndpCnt = dpCnt;
        auto ndpSum = dpSum;
        ll curVal = toVal[i];

        for (int len = 0; len <= D - 1; len++) {
            for (int productIdx = 0; productIdx < sz; productIdx++) {
                ll curProd = toVal[productIdx];
                ll nProduct = curProd * curVal;

                if (nProduct > n) break;
                if (dpCnt[len][productIdx] == 0) continue;
                
                if (n % nProduct == 0) {
                    int nProductIdx = toIdx[nProduct];
                    
                    ll tmp = dpCnt[len][productIdx] * curVal % MOD1;
                    add(tmp, dpSum[len][productIdx]);

                    add(ndpSum[len + 1][nProductIdx], tmp);
                    add(ndpCnt[len + 1][nProductIdx], dpCnt[len][productIdx]);
                }
            }
        }

        swap(ndpCnt, dpCnt);
        swap(ndpSum, dpSum);
    }

    ll ans = 0;
    for (int len = 1; len <= D; len++) {
        add(ans, dpSum[len][sz - 1] * fact[len] % MOD1);
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