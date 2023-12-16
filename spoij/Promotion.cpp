/*
    Solution for: https://www.spoj.com/problems/PRO/
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long

int n;
void solve() {
  cin >> n;
  multiset<int, greater<>> ms;
  ll res = 0;
  for (int i = 0; i < n; i++) {
    int p; cin >> p;
    for (int j = 0; j < p; j++) {
      int val; cin >> val;
      ms.insert(val);
    }
    res += 0LL + *ms.begin() - *(--ms.end());
    ms.erase(ms.begin()); ms.erase(--ms.end());
  }
  cout << res << "\n";
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  solve();
  return 0;
}