/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://www.spoj.com/problems/MMASS/
*/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> ii;
typedef unsigned long long ull;

#define X first
#define Y second
#define pb push_back
#define mp make_pair
#define ep emplace_back
#define EL printf("\n")
#define sz(A) (int) A.size()
#define FOR(i,l,r) for (int i=l;i<=r;i++)
#define FOD(i,r,l) for (int i=r;i>=l;i--)
#define fillchar(a,x) memset(a, x, sizeof (a))
#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

string s;
stack<int> st;
map<char, int> val;
unordered_map<int, vector<int>> M; // {orgR, r with num, repeat}
vector<vector<ll>> dp(105, vector<ll>(105, -1));

ll dfs(int _l, int r, string &s) {
  if (_l > r) return 0;
  if (dp[_l][r] != -1) return dp[_l][r];
  
  ll res = 0;
  int l = _l;
	while (l <= r) {
    if (s[l] == 'C' || s[l] == 'O' || s[l] == 'H') {
      int value = val[s[l]];
      int repeat = 1;
      string re_s = "";
      if (l + 1 <= r && '0' <= s[l + 1] && s[l + 1] <= '9') {
        re_s += s[l + 1];
      }
      if (re_s != "") repeat = stoi(re_s);
      res += 1LL*repeat*value;
    } else if (s[l] == '(') {
      auto cur = M[l];
      int orgR = cur[0];
      int r_with_num = cur[1];
      int repeat = cur[2];
      res += 1LL*repeat*dfs(l + 1, orgR - 1, s);
      res += dfs(r_with_num + 1, r, s);
      break;
    }
    l++;
  }
  return dp[_l][r] = res;
}
int main() {
//  freopen("INP.TXT", "r", stdin);
//  freopen("OUT.TXT", "w", stdout);

	cin >> s;
  int n = s.size();

	val['C'] = 12;
	val['H'] = 1;
	val['O'] = 16;

	int h = 0;
  stack<int> S;
  int i = 0;
  while (i < n) {
    if (s[i] == '(') S.push(i);
    else if (s[i] == ')') {
      string num = "";
      int orgR = i;
      if (i + 1 < n &&  '0' <= s[i + 1] && s[i + 1] <= '9') {
        num += s[i + 1];
        i++;
      }
      int repeat = 1;
      if (num != "") repeat = stoi(num);
      int l = S.top();
      int r = i;
      M[l] = {orgR, r, repeat};
      S.pop();
    }
    i++;
  }
  dfs(0, n - 1, s);
	cout << dp[0][n - 1] << "\n";
	return 0;
}