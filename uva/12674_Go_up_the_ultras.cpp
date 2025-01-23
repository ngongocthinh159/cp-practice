/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://vjudge.net/problem/UVA-12674/origin
*/

#include<bits/stdc++.h>
using namespace std;

#define MAXN 100005
#define D 150000
int n;
int a[MAXN];
void find_ans(vector<pair<bool,bool>> &ok, int mx, int mode = 0) {
  vector<pair<int,int>> st;
  for (int i = 0; i < n; i++) {
    int mn = INT_MAX;
    while (st.size() && a[st.back().first] <= a[i]) {
      mn = min(mn, st.back().second);
      st.pop_back();
    }
    int idx = mode == 0 ? i : (n - i - 1);
    if (a[i] != mx) {
      if (!st.size() || (st.size() && a[i] - mn >= D)) {
        if (mode == 0) ok[idx].first = true;
        else ok[idx].second = true;
      }
    }
    st.push_back({i, min(mn, a[i])});
  }
}
void solve() {
  int mx = -1;
  for (int i = 0; i < n; i++) cin >> a[i], mx = max(mx, a[i]);
  vector<pair<bool,bool>> ok(n, {false, false});
  for (int i = 0; i < n; i++) if (a[i] == mx && a[i] >= D) ok[i] = {true,true};
  find_ans(ok, mx);
  reverse(a, a + n);
  find_ans(ok, mx, 1);
  bool first = true;
  for (int i = 0; i < n; i++) if (ok[i].first && ok[i].second) {
    if (!first) cout << " ";
    cout << i + 1;
    first = false;
  }
  cout << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
  int cnt = 0;
  while (true) {
    if (!(cin >> n)) break;
    solve();
  }
  
  return 0;
}
