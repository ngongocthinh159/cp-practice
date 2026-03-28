/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/contest/2209/problem/C
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

struct ds {
    vector<int> a;
    ds() {
        a = {0, 0, 1, 0, 2};
    }
    int query(int i, int j) {
        return a[i] == a[j];
    }
};
int query(int i, int j) {
    cout << "? " << i << ' ' << j << endl;
    int res; 
    cin >> res;
    return res;

    // ds d;
    // return d.query(i, j);
}
void answer(int pos) {
    cout << "! " << pos << endl;
}
void pre_compute() {
    
}
void solve() {
    int n; 
    cin >> n;
    n = 2*n;
    for (int i = 1; i <= n - 4; i += 2) {
        int res = query(i, i + 1);
        if (res == 1) {
            answer(i);
            return;
        }
    }
    int res = query(n - 3, n - 1);
    if (res == 1) {
        answer(n - 3);
        return;
    }
    res = query(n - 3, n);
    if (res == 1) {
        answer(n - 3);
        return;
    }
    res = query(n - 3, n - 2);
    if (res == 1) {
        answer(n - 3);
        return;
    }
    answer(n - 2);
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