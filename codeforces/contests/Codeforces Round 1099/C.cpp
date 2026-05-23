/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/contest/2231/problem/C
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


void pre_compute() {
    
}
void solve() {
    int n; cin >> n;
    int a[n + 1]; 
    for (int i = 1; i <= n; i++) cin >> a[i];
    unordered_map<int,int,chash> f;
    f.reserve(60*n);
    unordered_map<int,ll,chash> tot;
    tot.reserve(60*n);
    for (int i = 1; i <= n; i++) {
        int x = a[i];
        int step = 0;
        bool vis2 = false;
        while (x != 1) {
            if (i == 1 || (i != 1 && f.count(x))) { // optimization only take numbers in sequence of a[1]
                f[x]++;
                tot[x] += step;
                if (x == 2) vis2 = true;
            }

            step++;
            if (x&1) x++;
            else x /= 2;
        }
        f[1]++;
        tot[1] += step;
        if (!vis2) {
            f[2]++;
            tot[2] += step + 1;
        }
    }   
    ll ans = LINF;
    for (auto [x, cnt] : f) if (cnt == n) {
        ans = min(ans, tot[x]);
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