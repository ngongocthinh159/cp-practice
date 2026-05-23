/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/contest/2231/problem/D
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
    string s; cin >> s;
    s = " " + s;
    ll r[n + 1];
    for (int i = 1; i <= n; i++) r[i] = s[i] - '0';
    ll a[n + 1];
    ll c[n + 1];
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> c[i];
    if (r[1]) {
        if (a[1] != c[1]) {
            cout << "no" << nline;
            return;
        }
    } else {
        a[1] = c[1];
    }
    bool vis[n + 1]{};
    vis[1] = 1;
    ll last = 1, mx = a[1];
    for (int i = 2; i <= n; i++) {
        if (c[i] < mx) {
            cout << "no" << nline;
            return;
        }

        if (mx == c[i]) continue;

        int start = last + 1;
        int end = i;

        ll desired = c[i] - mx;
        int cnt = 0;
        ll delta = 0;
        for (int j = start; j <= end; j++) {
            if (r[j] == 0) cnt++;
            else
                delta += a[j];
        }
        if (cnt == 0) {
            if (delta != desired) {
                cout << "no" << nline;
                return;
            }
        } else {
            int idx;
            ll sur = 0;
            for (int j = end; j >= start; j--) {
                if (r[j] == 0) {
                    idx = j;
                    break;
                } else
                    sur += a[j];
            }
            bool first = true;
            ll pref = 0;
            for (int j = start; j < idx; j++) {
                if (r[j] == 0) {
                    if (first) {
                        a[j] = -(3e12);
                    } else {
                        a[j] = 0;
                    }
                    vis[j] = 1;
                    first = false;
                }
                pref += a[j];
            }
            a[idx] = desired - sur - pref;
            vis[idx] = 1;
        }

        mx = c[i];
        last = i;
    }
    for (int i = 1; i <= n; i++) if (r[i] == 0 && !vis[i]) {
        a[i] = -(3e12);
    }

    ll pref = 0, pmx = -LINF;
    for (int i = 1; i <= n; i++) {
        pref += a[i];
        pmx = max(pmx, pref);
        if (pmx != c[i]) {
            cout << "no" << nline;
            return;
        }
    }

    cout << "yes" << nline;
    for (int i = 1; i <= n; i++) {
        cout << a[i] << ' ';
    }
    cout << nline;
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