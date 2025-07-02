/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://oj.vnoi.info/problem/lqddiv
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

#define N 35
int a[N];
void pre_compute() {
    
}
void gen(int i, int len, vector<ll> &L, ll curSum, ll cnt) {
    if (i == len) {
        L.push_back(curSum);
        return ;
    }
    gen(i + 1, len, L, curSum, cnt);
    gen(i + 1, len, L, curSum + a[i], cnt + 1);
}
vector<pair<ll,int>> compress(vector<ll> &a) {
    vector<pair<ll,int>> res;
    int i = 0;
    while (i < (int) a.size()) {
        int s = i, e = i;
        int x = a[i];
        while (i < (int) a.size() && a[i] == x) e = i, i++;
        res.push_back({x, e - s + 1});
    }
    return res;
}
void solve() {
    int n; cin >> n;
    ll tot = 0;
    for (int i = 0; i < n; i++) cin >> a[i], tot += a[i];
    int half = (n + 1)/2;
    vector<ll> L, R;
    gen(0, half, L, 0, 0);  
    gen(half, n, R, 0, 0);  
    sort(all(L));
    sort(all(R));
    auto l = compress(L);
    auto r = compress(R);
    ll mn = LINF, cnt = 0;
    int i = 0, j = r.size() - 1;
    while (i < (int) l.size() && j >= 0) {
        ll dif = 2 * (l[i].first + r[j].first) - tot;

        ll D = abs(dif);
        if (mn > D) {
            mn = D;
            cnt = 1LL * l[i].second * r[j].second;
        } else if (mn == D) {
            cnt += 1LL * l[i].second * r[j].second;
        }

        if (dif < 0) {
            i++;
        } else if (dif > 0) {
            j--;
        } else {
            i++, j--;
        }
    }
    cout << mn << ' ' << cnt/2 << nline;
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