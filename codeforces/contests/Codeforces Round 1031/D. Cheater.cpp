/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/contest/2113/problem/D
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
int a[N], b[N], pref[N], pref2[N], prefb[N];
void pre_compute() {
    
}
void solve() {
    cin >> n;
    pref[0] = pref2[0] = IINF;
    for (int i = 0; i < n; i++) {
        cin >> a[i];

        pref[i + 1] = pref[i];
        pref2[i + 1] = pref2[i];

        if (a[i] < pref[i + 1]) {
            pref2[i + 1] = pref[i + 1];
            pref[i + 1] = a[i];
        } else if (a[i] < pref2[i + 1]) {
            pref2[i + 1] = a[i];
        }
    }
    prefb[0] = IINF;
    for (int i = 0; i < n; i++) cin >> b[i], prefb[i + 1] = min(prefb[i], b[i]);
    int surMax = -IINF;
    int point = 0;
    for (int i = n - 1; i >= 0; i--) {
        int acards = i + 1;
        int bcards = n - acards + 1;

        // no swap
        bool ok = false;
        if (pref[i + 1] > prefb[bcards]) {
            ok = true;
        }
        
        if (surMax > prefb[bcards] && pref2[i + 1] > prefb[bcards]) {
            ok = true;
        }

        if (ok) {
            point = i + 1;
            break;
        }

        surMax = max(surMax, a[i]);
    }
    cout << point << nline;
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