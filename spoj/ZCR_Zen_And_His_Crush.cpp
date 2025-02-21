#include <bits/stdc++.h>
using namespace std;

#define MAXN 1005
int n, k;
double dp[MAXN][MAXN], a[MAXN]; // dp[i][j]: total probability of all configs has j head coins if only consider until i-th element

void solve() {
  cin >> n >> k;
  for (int i = 1; i <= n; i++) cin >> a[i];
  dp[0][0] = 1;
  for (int i = 1; i <= n; i++) dp[i][0] = 1.00*(1 - a[i])*dp[i - 1][0];
  for (int i = 1; i <= n; i++)
    	for (int j = 1; j <= k; j++) {
        dp[i][j] = dp[i - 1][j]*(1 - a[i]) + dp[i - 1][j - 1]*a[i];
      }
  printf("%.11f\n", dp[n][k]);
}

int main() {
  ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
  int t; cin >> t;
  while (t--) {
  	solve();  
  }
  return 0;
}
