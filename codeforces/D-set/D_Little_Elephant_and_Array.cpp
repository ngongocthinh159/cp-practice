/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/problemset/problem/221/D
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
#define BLOCK_SIZE 350
int n, m;
int a[N], ans[N];
struct query {
    int l, r, idx;
};
query qs[N];
void pre_compute() {
    
}
void solve() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < m; i++) {
        cin >> qs[i].l >> qs[i].r;
        qs[i].l--;
        qs[i].r--;
        qs[i].idx = i;
    }
    sort(qs, qs + m, [&](auto &q1, auto &q2){
        int b1 = q1.l / BLOCK_SIZE;
        int b2 = q2.l / BLOCK_SIZE;
        if (b1 < b2) return true;
        if (b1 == b2 && q1.r < q2.r) return true;
        return false;
    });
    unordered_map<int,int> f;
    f.reserve(2*n);
    int cnt = 0;
    auto add = [&](int x) {
        if (f[x] == x) cnt--;
        if (++f[x] == x) cnt++;
    };
    auto remove = [&](int x) {
        if (f[x] == x) cnt--;
        if (--f[x] == x) cnt++;
    };
    {
        int l = 0, r = -1, i = 0;
        while (i < m) {
            int B = qs[i].l / BLOCK_SIZE;
            while (i < m && qs[i].l / BLOCK_SIZE == B) {
                while (l > qs[i].l) { 
                    l--;
                    add(a[l]);
                }
                while (r < qs[i].r) {
                    r++;
                    add(a[r]);
                }
                while (l < qs[i].l) {
                    remove(a[l]);
                    l++;
                }
                while (r > qs[i].r) {
                    remove(a[r]);
                    r--;
                }

                ans[qs[i].idx] = cnt;

                i++;
            }
            
        }
    }
    for (int i = 0; i < m; i++)
        cout << ans[i] << nline;
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