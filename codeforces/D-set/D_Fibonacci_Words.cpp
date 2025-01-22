/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/gym/101205/attachments
 * D - Fibonacci Words
*/
#include<bits/stdc++.h>
 
using namespace std;

#define fastio() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
void IN_OUT() {
#ifndef ONLINE_JUDGE
freopen("Input.txt", "r", stdin);
freopen("Output.txt", "w", stdout);
#endif
}
#define MOD 1000000007
#define MOD1 998244353
#define LINF ((long long)1e18)
#define IINF ((int)1e9)
#define nline "\n"
#define pb push_back
#define ppb pop_back
#define mp make_pair
#define ff first
#define ss second
#define PI 3.141592653589793238462
#define set_bits(x) __builtin_popcountll(x)
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define rep(i,a,n) for (int i=(a);i<(n);i++)
 
using ll = long long;
using ull = unsigned long long;
using lld = long double;
 

#define MAX_N 105
#define MAX_LEN 100005

ull dp[MAX_N];
int match[MAX_LEN*10];
void pre_compute() {
}
int k, n;
string s;
vector<int> kmp(string &s) {
    int n = sz(s);
    vector<int> pref(n);
    int j = 0;
    for (int i = 1; i < n; i++) {
        while (j > 0 && s[i] != s[j]) j = pref[j - 1];
        pref[i] = s[i] == s[j] ? ++j : 0;
    }
    return pref;
}
vector<int> match_func(string &t, string &s, vector<int> &pref_s) {
    int n = sz(t);
    int j = 0;
    vector<int> match(n);
    for (int i = 0; i < n; i++) {
        while (j > 0 && t[i] != s[j]) j = pref_s[j - 1];
        match[i] = t[i] == s[j] ? ++j : 0;
    }
    return match;
}
void solve() {
    cin >> s;
    cin.ignore();
    n = sz(s);
    s += '$';
    ull ans = 0;
    if (k == 0) {
        if (n == 1 && (s[0] == '0')) cout << 1 << nline;
        else cout << 0 << nline;
        return;
    }
    if (k == 1) {
        if (n == 1 && (s[0] == '1')) cout << 1 << nline;
        else cout << 0 << nline;
        return;
    }
    vector<int> pref_s = kmp(s);
    string pp = "0"; // previous of previous
    string p = "1"; // previous
    int j = (s[0] == '1' ? 1 : 0);
    match[0] = (s[0] == '1' ? 1 : 0);
    int i = 1;
    ull cnt = 0;
    if (n == 1 && s[0] == '1') cnt++;
    for (int m = 2; m <= 26; m++) {
        string cur = p + pp;
        while (i < sz(cur)) {
            while (j > 0 && s[j] != cur[i]) j = pref_s[j - 1];
            match[i] = s[j] == cur[i] ? ++j : 0;
            if (match[i] == n) cnt++;
            i++;
        }
        dp[m] = cnt;
        swap(pp, p);
        swap(p, cur);
    }
    if (k <= 26) {
        cout << dp[k] << nline;
        return;
    }
    
    ull extra_ab = 0, extra_aa = 0, extra_ba = 0;
    string ab = p + pp;
    string aa = p + p;
    string ba = pp + p;
    vector<int> match_ab = match_func(ab, s, pref_s);
    vector<int> match_aa = match_func(aa, s, pref_s);
    vector<int> match_ba = match_func(ba, s, pref_s);
    int len_a = sz(p);
    int len_b = sz(pp);
    for (int i = len_a; i < len_a + n - 1; i++) if (match_ab[i] == n) extra_ab++;
    for (int i = len_a; i < len_a + n - 1; i++) if (match_aa[i] == n) extra_aa++;
    for (int i = len_b; i < len_b + n - 1; i++) if (match_ba[i] == n) extra_ba++;
    
    dp[27] = dp[26] + dp[25] + extra_ab;
    for (int m = 28; m <= k; m++) {
        dp[m] = dp[m - 1] + dp[m - 2] + (m&1 ? extra_aa : extra_ba);
    }
    cout << dp[k] << nline;
}

int main() {
    fastio();
    IN_OUT();
    pre_compute();
    int cnt = 0;
    string ss;
    while (true) {
        if (!getline(cin, ss)) break;
        k = stoi(ss);
        cout << "Case " << (++cnt) << ": ";
        solve();
    }
}
