/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/contest/2113/problem/B
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

struct Rec {
    int t, b, l, r;
    Rec(int t, int b, int l, int r) : t(t), b(b), l(l), r(r) {

    }
    int distH(const Rec &p) {
        return min(abs(t - p.b), abs(b - p.t));
    }
    int distW(const Rec &p) {
        return min(abs(l - p.r), abs(r - p.l));
    }
};
void pre_compute() {
    
}
bool intersect(int x1, int y1, int x2, int y2) {
    return !(x1 > y2 || x2 > y1);
}
void solve() {
    int w, h, a, b; cin >> w >> h >> a >> b;
    int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
    Rec r1(y1 + b - 1, y1, x1, x1 + a - 1);
    Rec r2(y2 + b - 1, y2, x2, x2 + a - 1);
    bool ok = false;
    if (intersect(r1.b, r1.t, r2.b, r2.t)) {
        if ((r1.distW(r2) - 1) % a == 0) ok = true;
    } else if (intersect(r1.l, r1.r, r2.l, r2.r)) {
        if ((r1.distH(r2) - 1) % b == 0) ok = true;
    } else {
        if ((r1.distW(r2) - 1) % a == 0) ok = true;
        if ((r1.distH(r2) - 1) % b == 0) ok = true;
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