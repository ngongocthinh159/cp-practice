/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1680
*/

#include <bits/stdc++.h>
using namespace std;

string s;
int dfs(int l, int r, string &s, vector<vector<int>> &dp) {
  if (l >= r) return 0;
  if (dp[l][r] != -1) return dp[l][r];
  int res;
  if (s[l] == s[r])
    res = dfs(l + 1, r - 1, s, dp);
  else
    res = 1 + min(dfs(l + 1, r, s,dp), 
             min(dfs(l, r - 1, s, dp), dfs(l + 1, r - 1, s, dp)));
  return dp[l][r] = res;
}
void solve() {
  cin >> s;
  int n = s.size();
  vector<vector<int>> dp(n, vector<int>(n, -1));
  cout << dfs(0, n - 1, s, dp) << '\n';
}
int main() {
  int T; cin >> T;
  for (int i = 1; i <= T; i++) {
    cout << "Case " << i << ": ";
    solve();
  }
  return 0;
}