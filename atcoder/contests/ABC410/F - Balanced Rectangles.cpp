/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://atcoder.jp/contests/abc410/tasks/abc410_f
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

int n, m;
void pre_compute() {
    
}
int query(int x1, int y1, int x2, int y2, vector<vector<int>> &pref) {
    return pref[x2 + 1][y2 + 1] - pref[x2 + 1][y1] - pref[x1][y2 + 1] + pref[x1][y1];
}
void solve() {
    cin >> n >> m;
    vector<vector<int>> mat(n, vector<int>(m));
    vector<vector<int>> pref(n + 1, vector<int>(m + 1));
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        for (int j = 0; j < m; j++) {
            if (s[j] == '#') mat[i][j] = 1;
            else mat[i][j] = -1;
            pref[i + 1][j + 1] = pref[i + 1][j] + pref[i][j + 1] - pref[i][j] + mat[i][j];
        }
    }
    ll ans = 0;
    int offset = n * m  + 3;
    vector<int> freq(2*(n * m + 5));
    if (n <= m) {
        for (int u = 0; u < n; u++)
            for (int d = u; d < n; d++) {
                freq[0 + offset]++;
                int dif = 0;
                for (int j = 0; j < m; j++) {
                    dif += query(u, j, d, j, pref);
                    ans += freq[dif + offset];
                    freq[dif + offset]++;
                }
                dif = 0;
                freq[0 + offset] = 0;
                for (int j = 0; j < m; j++) {
                    dif += query(u, j, d, j, pref);
                    freq[dif + offset] = 0;
                }
            }
    } else {
        for (int l = 0; l < m; l++)
            for (int r = l; r < m; r++) {
                freq[0 + offset]++;
                int dif = 0;
                for (int i = 0; i < n; i++) {
                    dif += query(i, l, i, r, pref);
                    ans += freq[dif + offset];
                    freq[dif + offset]++;
                }
                dif = 0;
                freq[0 + offset] = 0;
                for (int i = 0; i < n; i++) {
                    dif += query(i, l, i, r, pref);
                    freq[dif + offset] = 0;
                }
            }
    }
    
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