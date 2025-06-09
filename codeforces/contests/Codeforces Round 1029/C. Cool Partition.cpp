/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/contest/2117/problem/C
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
/*--------------------------------------------------------------------------------------------------------------------------*/

#define N 200005
int n;
int a[N];
void pre_compute() {
    
}
void solve() {
    cin >> n;
    unordered_map<int,int> freq;
    for (int i = 0; i < n;  i++) {
        cin >> a[i];
        freq[a[i]]++;
    }
    
    int ans = 0;
    for (int i = n - 1; i >= 0;) {
        int required_match = (int) freq.size();
        unordered_set<int> S;
        while (i >= 0 && required_match) {
            if (--freq[a[i]] == 0) {
                freq.erase(a[i]);
                if (!S.count(a[i]))
                    required_match--;
            } else {
                if (!S.count(a[i])) {
                    S.insert(a[i]);
                    required_match--;
                }
            }
            i--;
        }
        ans++;
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