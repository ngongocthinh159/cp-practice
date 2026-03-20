/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/problemset/problem/1912/K
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

#define N 200005
int n;
int a[N];
void pre_compute() {
    
}
void add(int &x, int y) {
    x += y;
    if (x >= MOD1) x -= MOD1;
}
void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    vector<int> dp1(2);
    vector<vector<int>> dp2(2, vector<int>(2));
    vector<vector<int>> dp3(2, vector<int>(2));
    dp1[a[1]&1]++;
    dp1[a[2]&1]++;
    dp2[a[1]&1][a[2]&1]++;
    for (int i = 3; i <= n; i++) {
        auto ndp3 = dp3;
        int p = a[i] & 1;
        if (p) {
            add(ndp3[1][1], dp3[0][1]);
            add(ndp3[0][1], dp3[1][0]);
            add(ndp3[1][1], dp2[0][1]);
            add(ndp3[0][1], dp2[1][0]);
        } else {
            add(ndp3[0][0], dp3[0][0]);
            add(ndp3[1][0], dp3[1][1]);
            add(ndp3[0][0], dp2[0][0]);
            add(ndp3[1][0], dp2[1][1]);
        }
        swap(dp3, ndp3);
        add(dp2[0][a[i]&1], dp1[0]);
        add(dp2[1][a[i]&1], dp1[1]);
        dp1[a[i]&1]++;

    }
    int ans = 0;
    add(ans, dp3[0][0]);
    add(ans, dp3[0][1]);
    add(ans, dp3[1][0]);
    add(ans, dp3[1][1]);
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