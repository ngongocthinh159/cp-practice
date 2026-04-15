/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/contest/2220/problem/D1
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

struct myds {
    vector<int> a = {0, 1,1,1,2,2};
    myds() {}
    int query(string &s) {
        stringstream ss(s);
        char c; ss >> c;
        int k; ss >> k;
        int res = 0;
        unordered_map<int,int> M;
        for (int i = 1; i <= k; i++) {
            int idx; ss >> idx;
            M[a[idx]]++;
        }
        for (auto [val, cnt] : M) if (cnt == 1) res++;
        return res;
    }
} ds;
void pre_compute() {
    
}
int query(int l, int r, int L, int R) {
    int k = (r - l + 1);
    string q = "";
    if (L == -1) {
        q = "? " + to_string(k) + " ";
        for (int i = l; i <= r; i++) {
            q += to_string(i);
            if (i != r) q += " ";
        }
    } else {
        q = "? " + to_string(k + 2) + " ";
        q += to_string(L) + " ";
        for (int i = l; i <= r; i++) {
            q += to_string(i);
            q += " ";
        }
        q += to_string(R);
    }

    int res;

    // cout << q << endl;
    // res = ds.query(q);
    
    cout << q << endl;
    cin >> res;

    return k - res;
}
void answer(int x, int y, int z) {
    cout << "! " << to_string(x) << " " << to_string(y) << " " << to_string(z) << endl;
}
void solve() {
    int n; 
    cin >> n;

    int buf[3];
    
    {
        int l = 0, r = 2*n + 2;
        while (r - l > 1) {
            int m = l + (r - l)/2;
            if (query(m, 2*n + 1, -1, -1) & 1)
                l = m;
            else
                r = m;
        }
        buf[0] = l;
    }
    {
        int l = 0, r = 2*n + 2;
        while (r - l > 1) {
            int m = l + (r - l)/2;
            if (query(1, m, -1, -1) & 1)
                r = m;
            else
                l = m;
        }
        buf[1] = r;
    }
    {
        int l = buf[0], r = buf[1];
        while (r - l > 1) {
            int m = l + (r - l)/2;
            if (query(buf[0] + 1, m, buf[0], buf[1]) & 1)
                r = m;
            else
                l = m;
        }
        buf[2] = r;
    }

    answer(buf[0], buf[1], buf[2]);
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