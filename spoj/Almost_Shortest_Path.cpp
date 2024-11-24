/**
 * Solution for: https://bigocoder.com/courses/196/lectures/2854/problems/1070
*/

#include <bits/stdc++.h>
using namespace std;

int n, m, s, d;
struct comparator {
  bool operator() (const pair<int,int> &a, const pair<int,int> &b) const {
    if (b.second < a.second) return true;
    return false;
  }
};
void shortestPath(int s, vector<vector<pair<int,int>>>& g, vector<int> &dist) {
    // setup
    dist = vector<int>(g.size() + 1, INT_MAX);
    priority_queue<pair<int,int>, vector<pair<int,int>>, comparator > pq; // min pq
    
    pq.push({s, 0});
    dist[s] = 0;
    while (pq.size()) {
        auto best = pq.top(); pq.pop();
        int u = best.first;
        int w = best.second;

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
  cin >> s >> d;
  vector<vector<pair<int,int>>> g(n);
  vector<vector<pair<int,int>>> rg(n);
  for (int i = 0; i < m; i++) {
    int u, v, w; cin >> u >> v >> w;
    g[u].push_back({v, w});
    rg[v].push_back({u, w});
  }
  vector<int> dist_s;
  shortestPath(s, g, dist_s);
  if (dist_s[d] == INT_MAX) {cout << "-1" << "\n"; return;}
  
  vector<int> dist_to_d;
  shortestPath(d, rg, dist_to_d);
  
  vector<vector<pair<int,int>>> g1(n);
  for (int u = 0; u < n; u++) {
  	for (auto &edge : g[u]) {
      int v = edge.first;
      int w_uv = edge.second;
      if (dist_s[u] != INT_MAX && 
          dist_to_d[v] != INT_MAX && 
          w_uv == dist_s[d] - dist_s[u] - dist_to_d[v]) continue;
      g1[u].push_back({v, w_uv});
    }
  }
  vector<int> dist;
  shortestPath(s, g1, dist);
  if (dist[d] == INT_MAX) cout << "-1" << "\n";
  else cout << dist[d] << "\n";
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  
  cin >> n >> m;
  while (n && m) {
    solve();
    cin >> n >> m;
  }
  return 0;
}