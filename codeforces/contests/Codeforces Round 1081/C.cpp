/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/contest/2192/problem/C
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

#define N 200005
ll n, h, k;
ll a[N];
void pre_compute() {
    
}
void solve() {
    cin >> n >> h >> k;
    ll sum = 0;
    for (int i= 0; i < n;i++) cin >> a[i], sum+= a[i];
    ll time = h / sum;
    ll remain = h - time * sum;

    vector<ll> surf(n + 1);
    vector<ll> pref(n);
    surf[n - 1] = a[n - 1];
    for (int i = n - 2; i >= 0; i --) surf[i] = max(surf[i + 1], a[i]);
    pref[0] = a[0];
    for (int i= 1; i <n; i++) pref[i] = pref[i - 1] + a[i];

    ll ans = time * n + max(0ll, time - 1) * k;
    if (remain) {
        if (ans != 0) ans += k;
        ll mn = IINF;
        ll cur_mn = IINF;
        for (int i = 0; i < n;i++) {
            if (pref[i] >= remain) mn = min(mn, 1ll * i + 1);
            
            cur_mn = min(cur_mn, a[i]);
            if (i != n - 1) {
                ll delta = -cur_mn + surf[i + 1];
                if (pref[i] + delta >= remain) mn = min(mn, 1ll*i + 1);
            }
        }
        ans += mn;
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