/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://oj.vnoi.info/problem/mbipalin
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

#define N 1000005
#define M 12
int n, m;
int cntL[N], cntR[N];
int _10powmod[12];
void pre_compute() {
    
}
void add(int &x, int y) {
    x += y;
    if (x >= m) x -= m;
}
void gen(int i, int hlen, int flen, int *cnt, int mod, int mnZero, bool mul) {
    if (i == hlen) {
        if (mul)
            cnt[1LL * mod * _10powmod[flen] % m] ++;
        else
            cnt[mod] ++;
        return;
    }
    int lower = i == 0 ? mnZero : 0;
    for (int j = lower; j <= 9; j++) {
        int nmod = mod;
        add(nmod, j * _10powmod[flen - i - 1] % m);
        if (flen - i - 1 != i)
            add(nmod, j * _10powmod[i] % m);
            
        gen(i + 1, hlen, flen, cnt, nmod, mnZero, mul);
    }
}
void solve() {
    cin >> n >> m;
    int half = n / 2;
    _10powmod[0] = 1 % m;
    for (int i = 1; i <= half; i++) {
        _10powmod[i] = _10powmod[i - 1] * 10 % m;
    }
    gen(0, (half + 1)/2, half, cntL, 0, 1, 1);
    gen(0, (half + 1)/2, half, cntR, 0, 0, 0);
    ll cnt = 0;
    for (int lmod = 0; lmod < m; lmod++) {
        int rmod = (-lmod + m) % m;
        cnt += 1LL * cntL[lmod] * cntR[rmod];
    }
    cout << cnt << nline;
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