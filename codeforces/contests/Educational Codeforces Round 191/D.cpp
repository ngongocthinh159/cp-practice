/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/contest/2233/problem/D
*/

// #include<bits/stdc++.h>
#include "bits/stdc++.h"
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


void pre_compute() {
    
}
void solve() {
    int n; cin >> n;
    int a[n + 1];
    for (int i = 1; i <= n; i++) cin >> a[i];
    unordered_map<int,vector<array<int,2>>,chash> f;
    for (int i = 1; i <= n;) {
        int start = i, end = i, cur = a[i];
        while (i <= n && cur == a[i]) {
            end = i;
            i++;
        }
        f[cur].push_back({start,end});
    }
    bool ok = true;
    for (auto &[x, list] : f) {
        if (list.size() > 3) {
            cout << "no" << nline;
            return;
        }
        if (list.size() != 1) ok = false;
    }
    if (ok) {
        cout << "yes" << nline;
        return;
    }
    for (auto &[x, list] : f) if (int(list.size()) != 1){
        set<int> endPoints;
        set<int> swapCandidates;
        for (auto &a : list) {
            endPoints.insert(a[0]);
            endPoints.insert(a[1]);
            if (a[0] - 1 >= 1) swapCandidates.insert(a[0] - 1);
            if (a[1] + 1 <= n) swapCandidates.insert(a[1] + 1);
        }
        bool found = false; 
        for (auto x : endPoints) {
            for (auto y : swapCandidates) if (x != y) {
                swap(a[x], a[y]);
                set<int> S;
                bool ok = true;
                for (int i = 1; i <= n;) {
                    if (S.count(a[i])) {
                        ok = false;
                        break;
                    }
                    S.insert(a[i]);
                    int cur = a[i];
                    while (i <= n && cur == a[i]) i++;
                }
                swap(a[x], a[y]);
                if (ok) {
                    found = true;
                }
            }
            if (found) break; 
        }
        if (found) {
            cout << "yes" << nline;
        } else
            cout << "no" << nline;
        break;
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