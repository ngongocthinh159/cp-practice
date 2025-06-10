/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/problemset/problem/1777/C
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

#define N 100005
int n, m;
int a[N];
vector<int> divisors[N];
void pre_compute() {
    for (int i = 1; i < N; i++)
        for (int j = i; j < N; j += i)
            divisors[j].push_back(i);
}
void solve() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) cin >> a[i];
    sort(a, a + n);
    vector<int> freq(m + 1);
    bool found = false;
    int not_ok = m;
    int ans = IINF;
    for (int r = 0, l = 0; r < n; r++) {
        for (auto d : divisors[a[r]]) {
            if (d > m) break;
            if (++freq[d] == 1) not_ok--;
        }
        
        while (l <= r && not_ok == 0) {
            found = true;
            for (auto d : divisors[a[l]]) {
                if (d > m) break;
                if (--freq[d] == 0) not_ok++;
            }

            l++;
        }

        if (found) {
            ans = min(ans, a[r] - a[l - 1]);
        }
    }
    if (ans == IINF)
        cout << -1 << nline;
    else
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