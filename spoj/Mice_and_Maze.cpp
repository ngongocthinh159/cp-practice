/*
    Solution for: https://www.spoj.com/problems/MICEMAZE/
*/

#include <bits/stdc++.h>
using namespace std;

const int N = 1e2 + 5;
int n, e, t, m;
vector<vector<pair<int,int>>> g;
vector<int> dist;
struct comparator {
  bool operator() (const pair<int,int> &a, const pair<int,int> &b) const {
    if (b.second > a.second) return true;
    return false;
  }
};
bool check(int i) {
  dist = vector<int>(n + 1, INT_MAX);
  priority_queue<pair<int,int>, vector<pair<int,int>>, comparator> pq;
  pq.push({i, 0});
  dist[i] = 0;
  while (pq.size()) {
    auto p = pq.top(); pq.pop();
    int u = p.first;
    int w = p.second;
    
    for (auto nei : g[u]) {
      int v = nei.first;
      int w_uv = nei.second;
      
      if (w + w_uv < dist[v]) {
        dist[v] = w + w_uv;
        pq.push({v, dist[v]});
      }
    }
  }
  
  if (dist[e] <= t) return true;
  return false;
}
void solve() {
  cin >> n >> e >> t >> m;
  g = vector<vector<pair<int,int>>>(n + 1);
  for (int i = 0; i < m; i++) {
    int u, v, w; cin >> u >> v >> w;
    g[u].push_back({v, w});
  }
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    if (check(i)) ans++;
  }
  cout << ans << "\n";
}

int main() {
  solve();
  return 0;
}