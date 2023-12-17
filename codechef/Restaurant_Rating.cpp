/*
    Solution for: https://www.codechef.com/problems/RRATING
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long

int n;
void solve() {
	cin >> n;
  priority_queue<int> rest2_3;
  priority_queue<int, vector<int>, greater<>> top1_3;
  int items = 0;
  for (int i = 0; i < n; i++) {
    int c; cin >> c;
    if (c == 1) items++;
    int cnt = items/3;
    
    if (c == 1) {
      int val; cin >> val;
      if (cnt == 0) {rest2_3.push(val); continue;}
      
      if ((int) top1_3.size() < cnt) {
        rest2_3.push(val);
        int tmp = rest2_3.top(); rest2_3.pop();
        top1_3.push(tmp);
      } else {
        int tmp = top1_3.top();
        if (tmp < val) {
          top1_3.pop();
          top1_3.push(val);
          rest2_3.push(tmp);
        } else rest2_3.push(val);
      }
    } else {
      if (cnt <= 0) {cout << "No reviews yet\n";}
      else cout << top1_3.top() << "\n";
    }
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  solve();
  return 0;
}