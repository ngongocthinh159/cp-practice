/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/contest/2117/problem/B
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
int a[N];
void pre_compute() {
    
}
void solve() {
    int n; cin >> n;
    cout << 1 << ' ';
    for (int i = 3; i <= n; i++) cout << i << ' ';
    cout << 2 << ' ';
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