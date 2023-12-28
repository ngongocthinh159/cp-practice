/**
 * Solution for: https://vjudge.net/problem/UVA-12032
*/

#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
int n;
int a[N];
bool check(long long k) {
  long long cur = 0;
  for (int i = 0; i < n; i++) {
    long long need = 1LL*a[i] - cur;
    if (need > k) return false;
    else {
    	cur = a[i];
      if (need == k) k--;
    }
  }
  return true;
}
void solve() {
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  long long l = 1, r = 1e13, ans = -1;
  while (l <= r) {
    long long m = l + (r - l)/2;
    if (check(m)) {
      ans = m;
      r = m - 1;
    } else {
      l = m + 1;
  	}
  }
  cout << ans << "\n";
}

int main() {
  int cases; cin >> cases; int i = 1;
  while (cases--) {
    cout << "Case " << i++ << ": "; 
   	solve(); 
  }
  return 0;
}