/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/contest/13/problem/E
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
#define BLOCK_SIZE 300
int n, m;
int jump[N], to[N], a[N], block[N];
void pre_compute() {
    
}
void solve() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) cin >> a[i], block[i] = i / BLOCK_SIZE;
    auto update = [&](int i) {
        int j = i + a[i];
        if (j >= n) {
            jump[i] = 1;
            to[i] = j;
        } else {
            if (block[i] != block[j]) {
                jump[i] = 1;
                to[i] = j;
            } else {
                jump[i] = jump[j] + 1;
                to[i] = to[j];
            }
        }
    };
    for (int i = n - 1; i >= 0; i--) update(i);
        
    int type, x, y;
    for (int i = 0; i < m; i++) {
        cin >> type;
        if (type == 0) {
            cin >> x >> y;
            x--;
            
            a[x] = y;
            for (int j = x; j >= block[x] * BLOCK_SIZE; j--) update(j);

        } else {
            cin >> x;
            x--;
            int ans = 0, last = x;
            
            while (x < n) {
                last = x;
                ans += jump[x];
                x = to[x];
            }
            x = last;
            while (x < n) {
                last = x;
                x += a[x];
            }
            
            last++;
            cout << last << ' ' << ans << nline;

        }
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