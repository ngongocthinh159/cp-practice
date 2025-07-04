/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/contest/2123/problem/G
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
#define M 500005
#define MX_DIV 305
int n, m, q;
vector<int> divs[M];
int a[MX_DIV][N];
int A[N];
int drop[MX_DIV];
void pre_compute() {
    for (int i = 1; i < M; i++)
        for (int j = 2*i; j < M; j += i)
            divs[j].push_back(i);
}
void solve() {
    cin >> n >> m >> q;
    for (int i = 0; i < n; i++) cin >> A[i];
    int D = divs[m].size();
    auto &list = divs[m];
    for (int i = 0; i < D; i++) {
        drop[i] = 0;
        for (int j = 0; j < n; j++) {
            a[i][j] = A[j] % list[i];
            if (j > 0 && a[i][j] < a[i][j - 1])
                drop[i]++;
        }x`
    }
    for (int i = 0; i < q; i++) {
        int t; cin >> t;
        if (t == 1) {
            int idx, val; cin >> idx >> val;
            idx--;
            for (int j = 0; j < D; j++) {
                int newVal = val % list[j];
                if (idx > 0) {
                    if (a[j][idx] < a[j][idx - 1])
                        drop[j]--;
                    if (newVal < a[j][idx - 1])
                        drop[j]++;
                }
                if (idx + 1 < n) {
                    if (a[j][idx] > a[j][idx + 1])
                        drop[j]--;
                    if (newVal > a[j][idx + 1])
                        drop[j]++;
                }
                a[j][idx] = newVal;
            }
        } else {
            int k;
            cin >> k;
            int g = __gcd(k, m);
            auto idx = lower_bound(all(list), g) - list.begin();
            if (drop[idx] <= m / g - 1) 
                cout << "YES" << nline;
            else
                cout << "NO" << nline;
        }
    }
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