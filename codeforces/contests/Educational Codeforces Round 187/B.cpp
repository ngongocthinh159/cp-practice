/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/contest/2203/problem/B
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

#define BIT 31
#define MX 200
bool ok[MX];
int sum_digit(ll x) {
    int res = 0;
    while (x) {
        res += x % 10;
        x /= 10;
    }
    return res;
}
void pre_compute() {
    for (int i = 1; i < MX; i++) {
        if (sum_digit(i) == i) ok[i] = 1;
    }
}
int try_to(ll x, int sdigit, int tar) {
    if (sdigit < tar) {
        vector<int> v;
        while (x) {
            int d = x % 10; 
            v.push_back(9 - d);
            x/=10;
        }
        sort(all(v));
        int cnt = 0;
        for (int i= (int) v.size() - 1; i >= 0; i-- ) {
            sdigit += v[i];
            cnt++;
            if (sdigit >= tar) return cnt;
        }
        return -1;
    } else {
        vector<int>v;
        while (x) {
            int d = x % 10;
            v.push_back(d);
            x /= 10;
        }
        v.back() -= 1;
        sort(all(v));
        int cnt = 0; 
        for (int i= (int) v.size() - 1; i >= 0; i-- ) {
            sdigit -= v[i];
            cnt++;
            if (sdigit <= tar) return cnt;
        }
        return -1;
    }
}
void solve() {
    ll x; cin >> x;
    int ans = IINF;
    int sdigit = sum_digit(x);
    if (ok[sdigit]) {
        cout << 0 << nline;
        return;
    }
    for (int i = sdigit - 1; i >= 1; i--) if (ok[i]) {
        int t = try_to(x, sdigit, i) ;
        if (t != -1) {
            ans = min(ans, t);
            break;
        }
    }
    for (int i = sdigit + 1; i < MX; i++) if (ok[i]) {
        int t = try_to(x, sdigit, i) ;
        if (t != -1) {
            ans = min(ans, t);
            break;
        }
    }
    if (ans == IINF) ans = -1;
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