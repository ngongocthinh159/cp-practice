/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/contest/1999/problem/G1
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


int query(int a, int b) {
    cout << "? " << a << ' ' << b << endl;
    int res; cin >> res;
    if (res == -1) exit(0);
    return res;
}
int x = 111, cnt;
int fquery(int a, int b) {
    cnt++;
    if (a >= x) a++;
    if (b >= x) b++;
    return a*b; 
}
void pre_compute() {
    
}
void solve() {
    int l = 1, r = 1000;
    cnt = 0;
    while (r - l > 1) {
        int m = l + (r - l)/2;
        int res = query(1, m);
        // int res = fquery(1, m);
        if (res == m) 
            l = m;
        else
            r = m;
    }
    cout << "! " << r << endl;
    // cout << cnt << endl;
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