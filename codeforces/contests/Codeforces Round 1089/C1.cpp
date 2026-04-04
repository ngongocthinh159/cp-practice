/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/contest/2210/problem/C1
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

#define MX 200005
int divisor[MX];
bool prime[MX];
void pre_compute() {
    for (int i = 1; i < MX; i++)
        for (int j = i; j < MX; j += i) divisor[j] ++;
    for (int i = 0; i < MX; i++) prime[i] = 1;
    prime[0] = prime[1] = 0;
    for (int i = 2; i * i < MX; i++)
        for (int j = i * i; j < MX; j += i) prime[j] = 0;
}
ll lcm(ll a, ll b) {
    return a / gcd(a, b) * b;
}
void solve() {
    int n; cin >> n;
    ll a[n + 1], b[n + 1];
    for (int i= 1; i <= n; i++) cin >> a[i];
    for (int i= 1; i <= n; i++) cin >> b[i];
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        ll prv = i == 1 ? 1 : a[i - 1];
        ll nxt = i == n ? 1 : a[i + 1];
        ll g1 = gcd(a[i], prv);
        ll g2 = gcd(a[i], nxt);
        ll remain = a[i] / lcm(g1,g2);
        // cout << i << ' ' << remain << nline;
        if (remain != 1) ans++;
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