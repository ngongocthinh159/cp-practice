/**
 * Solution for: https://bigocoder.com/courses/196/lectures/2926/problems/817
*/

#include <bits/stdc++.h>
using namespace std;
#define fastio() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)

const int N = 5e4 + 4;
int n, q;
int h[N];
void solve() {
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> h[i];
  }
  cin >> q;
  for (int i = 0; i < q; i++) {
    int target; cin >> target;
    int index = lower_bound(h, h + n, target) - h;
    if (index == 0) cout << "X" << " ";
    else if (index <= n) cout << h[index - 1] << " ";
    
    index = upper_bound(h, h + n, target) - h;
    if (index == n) cout << "X" << "\n";
    else cout << h[index] << "\n";
  }
}

int main() {
  fastio();
  solve();
  return 0;
}