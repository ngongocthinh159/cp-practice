/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/contest/2226/problem/D
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
    int oddMax = -1, oddMin = IINF, evenMax = -1, evenMin = IINF;
    vector<int> odds, evens;
    for (int i = 1; i <= n; i++) {
        if (a[i]&1) {
            odds.push_back(a[i]);
            oddMax = max(oddMax, a[i]);
            oddMin = min(oddMin, a[i]);
        }
        else {
            evens.push_back(a[i]);
            evenMax = max(evenMax, a[i]);
            evenMin = min(evenMin, a[i]);
        }
    }
    bool ok = true;
    if (odds.size() > 1) {
        int mx = odds[0];
        for (int i = 1; i < int(odds.size()); i++) {
            if (odds[i] >= mx) {
                mx = odds[i];
            } else {
                if (evenMin > odds[i] && evenMax < mx) {
                    ok = false;
                    break;
                }
            }
        }
    }
    if (evens.size() > 1) {
        int mx = evens[0];
        for (int i = 1; i < (evens.size()); i++) {
            if (evens[i] >= mx) {
                mx = evens[i];
            } else {
                if (oddMin > evens[i] && oddMax < mx) {
                    ok = false;
                    break;
                }
            }
        }
    }
    if (ok)
        cout << "YES" << nline;
    else
        cout << "NO" << nline;
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