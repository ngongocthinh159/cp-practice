/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/problemset/problem/1735/D
*/

#include<bits/stdc++.h>
using namespace std;

#define nline '\n'
#define ll long long
#define MOD 1000000007
#define MOD1 998244353
#define LINF ((long long)1e18)
#define IINF ((int)1e9)

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

#define N 1005
#define K 25
int n, k;
int a[N][K], freq[N];
void pre_compute() {
    
}
string build_target(int i, int j) {
    string res = "";
    for (int p = 0; p < k; p++) {
        res += (a[i][p] == a[j][p] ? a[i][p] : (0^1^2^a[i][p]^a[j][p])) + '0'; 
    }
    return res;
}
string build(int i) {
    string res = "";
    for (int p = 0; p < k; p++) res += a[i][p] + '0';
    return res;
}
void solve() {
    cin >> n >> k;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < k; j++) 
            cin >> a[i][j];
    ll ans = 0;
    for (int i = n - 1; i >= 0; i--) {
        unordered_map<string,int> S;
        for (int j = n - 1; j > i; j--) {
            if (S.count(build_target(i, j))) {
                freq[i]++;
                freq[j]++;
                freq[S[build_target(i, j)]]++;
            }
            S[build(j)] = j;
        }
    }
    for (int i = 0; i < n; i++)
        if (freq[i] >= 2) ans += 1LL * freq[i] * (freq[i] - 1) /2;
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