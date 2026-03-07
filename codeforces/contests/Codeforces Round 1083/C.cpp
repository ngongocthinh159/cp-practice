/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/contest/2205/problem/C
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
#define MX 1000005
bool vis[MX], lvis[MX], used[N];
vector<int> a[N];
int n;
void pre_compute() {
    
}
void change(vector<int> &now) {
    vector<int> nw;
    for (auto c : now) if (!vis[c] && !lvis[c]) {
        nw.push_back(c);
        lvis[c] = 1;
    }
    for (auto c : now) lvis[c] = 0;
    now = nw;
}
void solve() {
    cin >> n;
    for (int i = 0; i < n;i++) {
        int sz; 
        cin >> sz;
        a[i].resize(sz);
        for (int j = 0; j < sz; j++) cin >> a[i][j], vis[a[i][j]] = 0;
        reverse(all(a[i]));
        change(a[i]);
        used[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        int id = -1;
        for (int j = 0; j < n; j++) if (!used[j]) {
            id = j;
            break;
        }
        for (int j = id + 1; j < n; j++) if (!used[j] && a[j] < a[id]) id = j;
        for (auto x : a[id]) {
            cout << x << ' ';
            vis[x] = 1;
        }
        used[id] = 1;
        for (int j = 0; j < n; j++) if (!used[j]) change(a[j]);
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