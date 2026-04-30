/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/contest/2226/problem/C
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
void test(int x) {
    set<int> S;
    for (int i = 1; i <= x; i++) S.insert(x % i);
    for (auto s : S) cout << s << ' ';
    cout << nline;
}
bool check(int m, vector<int> &a) {
    int n = a.size();
    vector<int> v;
    vector<bool> vis(m + 1);
    int j = 0;
    for (int i = 0; i <= m; i++) {
        while (j < n && a[j] < i) {
            v.push_back(a[j]);
            j++;
        }
        if (j < n) {
            if (a[j] == i) {
                vis[i] = 1;
                j++;
            }
        }
        else break;
    }
    while (j < n) v.push_back(a[j++]);
    // for (auto x : v) cout << x << ' ';    
    // cout << nline;
    // for (int i = 0; i <= m; i++) cout << vis[i] << ' ';
    // cout << nline;
    j = 0;
    for (int i = 0; i <= m; i++) if (!vis[i]) {
        while (j < int(v.size()) && (v[j] - 1)/2 < i) {
            j++;
        }
        if (j < int(v.size())) {
            vis[i] = 1;
            j++;
        } else return false;
    }
    return true;
}
void solve() {
    int n; cin >> n;
    vector<int> a(n);
    int mx = -1;
    unordered_map<int,int> f;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        mx = max(mx, a[i]);
        f[a[i]]++;
    }
    sort(a.begin(), a.end());
    multiset<int> S(all(a));
    int mex = 0;
    while (1) {
        if (f[mex]) {
            f[mex]--;
            S.erase(S.find(mex));
            mex++;
            continue;
        }

        auto it = S.upper_bound(2*mex);
        if (it == S.end()) break;
        f[*it]--;
        S.erase(it);
        mex++;
    }
    cout << mex << nline;

    // int l = -1, r = mx + 2;
    // // cout << check(2, a) << nline;
    // while (r - l > 1) {
    //     int m = l + (r - l)/2; 
    //     // cout << m << ' ' << check(m,a) << nline;
    //     if (check(m, a))
    //         l = m;
    //     else
     
    //     r = m;
    // }
    // cout << (l + 1) << nline;
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