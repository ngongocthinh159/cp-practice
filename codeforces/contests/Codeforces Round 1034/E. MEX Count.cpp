/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/contest/2123/problem/E
*/

#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
 
using namespace std;
using namespace chrono;
using namespace __gnu_pbds;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update > pbds; // find_by_order, order_of_key

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
#define N 200005
int n;
int a[N];
void pre_compute() {
    
}
void solve() {
    cin >> n;
    unordered_map<int,int,chash> freq;
    for (int i = 0; i < n; i++) cin >> a[i], freq[a[i]]++;
    unordered_map<int,vector<int>,chash> cntToNum;
    for (auto [num, cnt] : freq)
        cntToNum[cnt].push_back(num);
    int cmex = n;
    for (int i = 0; i <= n; i++) if (!freq.count(i)) {
        cmex = i;
        break;
    }
    sort(a, a + n);
    vector<int> mex(n);
    int need = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] == need) need++;
        mex[i] = need;
    }
    cout << 1 << ' ';
    pbds S;
    for (int k = 1; k < n; k++) {
        for (auto x : cntToNum[k])
            S.insert(x);
        int remain = n - k;
        int mxmex = min(cmex, remain);
        S.insert(mxmex);
        auto it = S.lower_bound(mxmex);
        cout << (S.order_of_key(*it)) + 1 << ' ';
    }
    cout << 1 << nline;
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