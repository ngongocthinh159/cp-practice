/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/contest/2123/problem/F
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
int buf[N];
int top;
bitset<N> prime;
void pre_compute() {
    prime.flip();
    prime[0] = prime[1] = 0;
    for (int i = 2; i * i < N; i++) if (prime[i])
        for (int j = i * i; j < N; j += i) prime[j] = 0;
}
void solve() {
    int n; cin >> n;
    int id = 0;
    vector<vector<int>> idToList(n);
    vector<int> numToId(n + 1, -1);
    for (int i = n; i >= 1; i--) if (prime[i]) {
        for (int j = i; j <= n; j += i) if (numToId[j] == -1) {
            idToList[id].push_back(j);
            numToId[j] = id;
        }
        id++;
    }
    for (int i = 1; i <= n; i++) if (numToId[i] == -1) {
        idToList[id].push_back(i);
        numToId[i] = id++;
    }
    vector<int> ans(n+1);
    for (int cid = 0; cid < n; cid++) {
        auto &list = idToList[cid];
        int m = list.size();
        for (int i = 0; i < m; i++) {
            ans[list[i]] = list[(i + 1) % m];
        }
    }    
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << ' ';
    }
    cout << nline;
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