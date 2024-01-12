/**
 * Solution for: https://codeforces.com/problemset/problem/68/B
*/

#include <bits/stdc++.h>
using namespace std;

const int N = 1e4 + 5;
int n;
double k;
double a[N];
bool check(double x) {
	double can = 0;
  double need = 0;
  for (int i = 0; i < n; i++) {
  	if (a[i] > x) {
      double xx = a[i] - x;
      can += (double) (xx - (double) xx*k/100);
    }
    else need += x - a[i];
  }  
  return can >= need;
}
void solve() {
  cin >> n >> k;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  double l = 0, r = 1e5, err = 1e-10, ans;
  for (int i = 0; i < 70; i++) {
    double m = l + (r - l)/2;
    if (check(m)) {
      ans = m;
      l = m + err;
    } else {
      r = m - err;
    }
  }
  printf("%.9f\n", ans);
}

int main() {
  solve();
  return 0;
}