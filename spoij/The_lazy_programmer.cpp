#include <bits/stdc++.h>
using namespace std;

struct Contract {
  int a; int b; int d;
  Contract(int a, int b, int d) : a(a), b(b), d(d) {}
  bool operator< (const Contract& b) const {
    if (this->d < b.d) return true;
    return false;
  }
};
int n;
void solve() {
  cin >> n;
  vector<Contract> contracts;
  for (int i = 0; i < n; i++) {
    int a, b, d; cin >> a >> b >> d;
    contracts.push_back(Contract(a, b, d));
  }
  sort(contracts.begin(), contracts.end());
  int time = 0;
  priority_queue<pair<int,int>> pq;
  double money = 0;
  for (auto& contract : contracts) {
    time += contract.b; pq.push({contract.a, contract.b});
    if (time <= contract.d) continue;
    
    int needImprove = time - contract.d;
    while (needImprove > 0) {
      auto p = pq.top(); pq.pop();
      int canImprove = p.second;
      int willImprove = min(needImprove, canImprove);
      if (willImprove < canImprove) {
        pq.push({p.first, canImprove - willImprove});
      }
      needImprove -= willImprove;
      time -= willImprove;
      money += (double) willImprove/p.first;
    }
  }
  printf("%.2f\n", money);
}

int main() {
  int cases; cin >> cases;
  while (cases--) {
  	solve();
  }
  
  return 0;
}