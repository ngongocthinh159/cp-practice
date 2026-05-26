/**
 * Author: Thinh Ngo Ngoc
 * Solution for: 
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
    string s; cin >> s;
    int n = int(s.size());
    s = " " + s;
    int cnt[26]{};
    int mx = 0;
    for (int i = 1; i <= n; i++) {
        cnt[s[i] - 'a']++;
        mx = max(mx, cnt[s[i] - 'a'])
    }
    
    auto [ok, res] = find(cnt);
    // cout << n << nline;
    // for (int i = 0; i < 26; i++) {
    //     cout << cnt[i] << ' ';
    // }
    // cout << nline;
    if (n&1) {
        if (mx * 2 - 1 > n) {
            cout << "No" << nline;
            return;
        }
    } else {
        if (mx * 2 > n) {
            cout << "No" << nline;
            return;
        }
    }
    priority_queue<pair<int,char>> q;
    for (int i = 0; i < 26; i++) if (cnt[i]) q.push({cnt[i], i + 'a'});
    string t = "";
    while (q.size()) {
        auto p1 = q.top();
        q.pop();
        p1.first--;
        t += p1.second;
        if (q.size()) {
            auto p2 = q.top();
            q.pop();
            t += p2.second;
            p2.first--;
            if (p2.first) q.push(p2);
        }
        if (p1.first) q.push(p1);
    }
    cout << "Yes" << nline; 
    cout << t << nline;
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