/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/contest/2227/problem/D
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

struct Manacher {
    string s;
    int n;
    vector<int> p; // p[i]: center i-th has palindrome bound [k,j] then p[i] = j - i + 1 = i - k + 1 (len of one side from center)
    Manacher(string &s) {
        this->s = s;
        n = s.size();
        _pre_process();
    }
    void _pre_process() {
        // transform orginal "ABA" => "#A#B#A#"
        string t;
        for (auto c : s) t += '#', t += c;
        t += '#';
        p = _manacher_odd(t); // p array is actually counted for transformed string
    }
    vector<int> _manacher_odd(string &str) {
        int n = str.size();
        string t = '^' + str + '$'; // "$" + s + "^": handle edge case when out of bound to compare
        vector<int> p(n + 2);
        for (int i = 1, l = 1, r = 1; i <= n; i++) {
            if (i <= r) p[i] = min(p[l + r - i], r - i + 1);
            while (t[i + p[i]] == t[i - p[i]]) ++p[i];
            if (i + p[i] - 1 > r) l = i - p[i] + 1,  r = i + p[i] - 1;
        }
        return vector<int>(p.begin() + 1, p.end() - 1);
    }

    int get_longest(int centerIdx, bool odd = true) {
        if (!odd) assert(centerIdx >= 1);
        
        int pidx = odd ? 2*centerIdx + 1 : 2*centerIdx; // convert from original to tranformed
        return p[pidx] - 1;
    }

    bool is_palindrome(int l, int r) {
        int centerIdx = (l + r + 1)/2;
        return get_longest(centerIdx, l%2==r%2) >= (r - l + 1);
    }

    // p[i]: center i-th has palindrome bound [k,j] then p[i] = j - i + 1 = i - k + 1 (len of one side from center)
    int get_p_at(int centerIdx, bool odd = true) {
        if (!odd) assert(centerIdx >= 1);
        int pidx = odd ? 2*centerIdx + 1 : 2*centerIdx;
        return p[pidx]/2;
    }
};

/**
 * Usage:
 *  int countSubstrings(string s) {
        Manacher mana(s);
        for (int i = 0; i < n; i++) {
            mana.get_longest(i);
            if (i >= 1) mana.get_longest(i, false);
            mana.get_p_at(i);
        }
        mana.is_palindrome(0, n - 1);
    }
*/
void pre_compute() {
    
}
void solve() {
    int n; cin >> n;
    n = 2*n;
    int a[n];
    string s;
    int pmn[n], pmn2[n];
    int prevMn = IINF, prevMn2 = IINF;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        s += a[i] + '0';

        if (a[i] < prevMn) {
            prevMn2 = prevMn;
            prevMn = a[i];
        } else if (a[i] < prevMn2) {
            prevMn2 = a[i];
        }

        pmn[i] = prevMn;
        pmn2[i] = prevMn2;
    }
    // cout << s << nline;

    int smn[n], smn2[n];
    int nxtMn = IINF, nxtMn2 = IINF;
    for (int i = n - 1; i >= 0; i--) {
        if (a[i] < nxtMn) {
            nxtMn2 = nxtMn;
            nxtMn = a[i];
        } else if (a[i] < nxtMn2) {
            nxtMn2 = a[i];
        }

        smn[i] = nxtMn;
        smn2[i] = nxtMn2;
    }

    int ans = 0;
    Manacher mana(s);
    for (int i = 0; i < n; i++) {
        {
            if (mana.get_longest(i) == n) {
                ans = n/2;
                break;
            }
            if (mana.get_longest(i) == n - 1) {
                ans = n/2;
                break;
            }

            int p = mana.get_p_at(i);
            int l = i - p + 1, r = i + p - 1;
            int mnL = l - 1 >= 0 ? (pmn[l - 1] != a[i] ? pmn[l - 1] : pmn2[l - 1]) : IINF;
            int mnR = r + 1 < n ? (smn[r + 1] != a[i] ? smn[r + 1] : smn2[r + 1]) : IINF;
            ans = max(ans, min(mnL, mnR));
        }


        if (i >= 1 && mana.get_longest(i, false) >= 2) {
            if (mana.get_longest(i, false) == n) {
                ans = n/2;
                break;
            }
            int p = mana.get_p_at(i, false);
            int l = i - p, r = i + p - 1;
            int mnL = l - 1 >= 0 ? pmn[l - 1] : IINF;
            int mnR = r + 1 < n ? smn[r + 1] : IINF;
            ans = max(ans, min(mnL, mnR));
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