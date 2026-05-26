/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/contest/2229/problem/C2
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
int p(int x) {
    if (x >= 0) return 1;
    return -1;
}
void solve() {
    int n; cin >> n;
    ll a[n + 1]{};
    ll allPos = 0;
    ll pref[n + 1]{};
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (a[i] >= 0) allPos += a[i];
        pref[i] = pref[i - 1] + abs(a[i]);
    }

    vector<pair<int,int>> v;
    vector<int> parity;
    int lastidx = -1;
    int cntpos = 0;
    for (int i = 1; i <= n;) {
        int curp = p(a[i]);
        int st = i, end = i;
        while (i <= n && p(a[i]) == curp) {
            end = i;
            i++;
        }
        if (curp == 1) {
            v.push_back({st, end});
        }
    }
    if (int(v.size()) == 0) {
        // cout << "a" << nline;
        cout << 0 << nline;
        cout << nline;
        return;
    }
    ll mx = -1, mxIdx;
    ll sur = 0;
    vector<int> idx;
    for (int i = int(v.size()) - 1; i >= 0; i--) {
        int l = v[i].first;
        int r = v[i].second;
        ll mn = LINF, mnidx;
        for (int j = l; j <= r; j++) {
            if (minimize(mn, a[j])) mnidx = j;
        }

        ll cur = sur + pref[r] - mn;
        if (maximize(mx, cur)) {
            mxIdx = i;
            idx.clear();
            if (mnidx == l) {
                idx.push_back(l); 
            } else {
                idx.push_back(mnidx - 1);
                if (l - 1 >= 1) idx.push_back(l - 1);
                idx.push_back(mnidx);
            }
        }
        sur += pref[r] - pref[l - 1];
    }
    if (mx <= allPos) {

        cout << 0 << nline;
        cout << nline;
        return;
    }
    vector<int> res;
    if (mxIdx >= 1) {
        int curpar = -1;
        for (int j = v[mxIdx - 1].second; j >= 1; j--) {
            if (p(a[j]) != curpar) {
                res.push_back(j);
                curpar = p(a[j]);
            }
        }
    }
    for (auto i : idx) res.push_back(i);
    cout << int(res.size()) << nline;
    for (auto i : res) cout << i << ' ';
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