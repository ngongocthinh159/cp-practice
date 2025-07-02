/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/contest/1006/problem/F
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

#define N 22
ll n, m, k;
vector<ll> L[N][N], R[N][N];
ll a[N][N];
vector<pair<int,int>> m1 = {{1,0},{0,1}};
vector<pair<int,int>> m2 = {{-1,0},{0,-1}};
ll ans = 0;
void gen(int i, int j, int curMove, int mxMove, ll cxor, vector<pair<int,int>> &moves, vector<ll> L[N][N], vector<ll> R[N][N], bool check) {
    if (curMove == mxMove) {
        L[i][j].push_back(cxor);
        if (check) {
            ll tar = cxor ^ k ^ a[i][j];
            auto pit = equal_range(R[i][j].begin(), R[i][j].end(), tar);
            ans += pit.second - pit.first;
        }
        return;
    }
    for (auto &move : moves) {
        int I = i + move.first;
        int J = j + move.second;
        if (0 <= I && I < n && 0 <= J && J < m) {
            gen(I, J, curMove + 1, mxMove, cxor ^ a[I][J], moves, L, R, check);
        }
    }
}
void pre_compute() {
    
}
void solve() {
    cin >> n >> m >> k;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) cin >> a[i][j];
    int totMove = n - 1 + m - 1;
    int half = (totMove + 1)/2;
    gen(0, 0, 0, half, a[0][0], m1, L, R, 0);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) 
            sort(L[i][j].begin(), L[i][j].end());
    gen(n - 1, m - 1, 0, totMove - half, a[n - 1][m - 1], m2, R, L, 1);
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