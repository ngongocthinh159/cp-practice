/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/contest/1715/problem/C
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

#define N 100005
int n, m;
int a[N];
void pre_compute() {
    
}
int cal(int x, int y) {
    if (x == y) return 1;
    return 2;
}
int cal3(int x, int y, int z) {
    if (x == y && y == z) return 1;
    if (y != x && y != z) return 3;
    return 2;
}
void solve() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    ll sum = 0, end = 0, prev = -1;
    for (int i = 0; i < n;) {
        ll cnt = 0, cur = a[i];
        while (i < n && a[i] == cur) {
            cnt++;
            i++;
        }
        sum += (end + (prev + 1)) * cnt + cnt * (cnt + 1) / 2;
        end += (prev + 1) + cnt;
        prev = i - 1;
    }
    for (int i = 0; i < m; i++) {
        ll idx, val; cin >> idx >> val;
        idx--;

        if (idx - 1 >= 0) {
            ll delta = -cal(a[idx - 1], a[idx]) + cal(a[idx - 1], val);
            sum += idx * delta;
        }
        if (idx + 1 < n) {
            ll delta = -cal(a[idx], a[idx + 1]) + cal(val, a[idx + 1]);
            sum += (n - (idx + 1)) * delta;
        }
        if (0 <= idx - 1 && idx + 1 < n) {
            ll delta = -cal3(a[idx - 1], a[idx], a[idx + 1]) 
                        + cal3(a[idx - 1], val, a[idx + 1]);
            sum += delta * idx * (n - (idx + 1));
        }
        
        a[idx] = val;
        cout << sum << nline;
    }
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