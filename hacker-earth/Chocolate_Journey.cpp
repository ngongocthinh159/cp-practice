/**
 * Solution for: https://www.hackerearth.com/practice/algorithms/graphs/shortest-path-algorithms/practice-problems/algorithm/successful-marathon-0691ec04/
*/

#include <bits/stdc++.h>
using namespace std;

int n, m, k, x, a, b;
vector<bool> hasChoco;
vector<vector<pair<int,int>>> g;
struct comparator {
  bool operator() (const pair<int,int> &a, const pair<int,int> &b) const {
    if (b.second < a.second) return true;
    return false;
  }
};
void shortestPath(int s, vector<int> &dist) {
  priority_queue<pair<int,int>, vector<pair<int,int>>, comparator> pq;
  pq.push({s, 0});
  dist[s] = 0;
  while (pq.size()) {
    auto cur = pq.top(); pq.pop();
    int u = cur.first;
    int w = cur.second;
    
    for (auto nei : g[u]) {
      int v = nei.first;
      int w_uv = nei.second;
      if (w + w_uv < dist[v]) {
        dist[v] = w + w_uv;
        pq.push({v, dist[v]});
      }
    }
  }
}
void solve() {
  cin >> n >> m >> k >> x;
  hasChoco.assign(n + 1, false);
  g.assign(n + 1, vector<pair<int,int>>());
  for (int i = 0; i < k; i++) {
    int val; cin >> val;
    hasChoco[val] = true;
  }
	for (int i = 0; i < m; i++) {
    int u, v, d; cin >> u >> v >> d;
    g[u].push_back({v, d});
    g[v].push_back({u, d});
  }
  cin >> a >> b;
  vector<int> distB(n + 1, INT_MAX);
  vector<int> distA(n + 1, INT_MAX);
  shortestPath(b, distB);
  vector<int> valid;
  for (int i = 1; i <= n; i++) {
    if (hasChoco[i] && distB[i] < x) valid.push_back(i);
  }
  if (!valid.size()) {cout << -1 << "\n"; return;}
  shortestPath(a, distA);
  int ans = INT_MAX;
  for (int i = 0; i < valid.size(); i++) {
    if (distA[valid[i]] == INT_MAX) continue;
    ans = min(ans, distA[valid[i]] + distB[valid[i]]);
  }
  cout << (ans == INT_MAX ? -1 : ans) << "\n";
}

int main() {
  solve();
  return 0;
}