/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/contest/2022/problem/C
*/

#include<bits/stdc++.h>
using namespace std;

#define nline '\n'
#define ll long long
#define MOD 1000000007
#define MOD1 998244353
#define LINF ((long long)1e18)
#define IINF ((int)1e9)

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
/*--------------------------------------------------------------------------------------------------------------------------*/

//0
//+
//+

//1
//+
//++

//2
//++
//+

void pre_compute() {
    
}
int cal(int x, int y, int z) {
    return (x + y + z) >= 2;
}
void solve() {
    int n;
    string s1,s2;
    cin >> n >> s1 >> s2;
    vector<int> val1(n + 10), val2(n + 10);
    for (int i = 0; i < n; i++) {
        val1[i + 1] = s1[i] == 'A' ? 1 : 0;
        val2[i + 1] = s2[i] == 'A' ? 1 : 0;
    }
    vector<vector<int>> dp(n + 10, vector<int>(3, -IINF));
    dp[0][0] = 0;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j < 3; j++) if (dp[i][j] != -IINF) {
            if (j == 0) {
                maximize(dp[i + 3][0], dp[i][j] + cal(val1[i + 1], val1[i + 2], val1[i + 3]) +
                                                    cal(val2[i + 1], val2[i + 2], val2[i + 3]));
                                                    
                maximize(dp[i + 2][1], dp[i][j] + cal(val1[i + 1], val2[i + 1], val2[i + 2]));

                maximize(dp[i + 2][2], dp[i][j] + cal(val2[i + 1], val1[i + 1], val1[i + 2]));
            } else if (j == 1) {
                maximize(dp[i + 1][0], dp[i][j] + cal(val1[i], val1[i + 1], val2[i + 1]));
                
                maximize(dp[i + 3][1], dp[i][j] + cal(val1[i], val1[i + 1], val1[i + 2]) +
                                                    cal(val2[i + 1], val2[i + 2], val2[i + 3]));
            } else if (j == 2) {
                maximize(dp[i + 1][0], dp[i][j] + cal(val2[i], val2[i + 1], val1[i + 1]));

                maximize(dp[i + 3][2], dp[i][j] + cal(val2[i], val2[i + 1], val2[i + 2]) +
                                                    cal(val1[i + 1], val1[i + 2], val1[i + 3]));
            }
        }
    }
    cout << dp[n][0] << nline;
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
