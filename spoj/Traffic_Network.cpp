/**
 * Solution for: https://vn.spoj.com/problems/TRAFFICN/
*/

#include <bits/stdc++.h>
using namespace std;

int n, m, k, s, t;
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
  cin >> n >> m >> k >> s >> t;
  vector<vector<pair<int,int>>> g(n + 1);
  vector<vector<pair<int,int>>> rg(n + 1);
  for (int i = 0; i < m; i++) {
    int d, c, l; cin >> d >> c >> l;
    g[d].push_back({c, l});
    rg[c].push_back({d, l});
  }
  vector<int> dist_s;
  shortestPath(s, g, dist_s);
  
  int ans = dist_s[t]; 
  
  vector<int> dist_to_t;
  shortestPath(t, rg, dist_to_t);
  
  for (int j = 0; j < k; j++) {
    int u, v, q; cin >> u >> v >> q;
    if (dist_s[u] != INT_MAX && dist_to_t[v] != INT_MAX) {
      ans = min(ans, dist_s[u] + q + dist_to_t[v]);
    }
    if (dist_s[v] != INT_MAX && dist_to_t[u] != INT_MAX) {
      ans = min(ans, dist_s[v] + q + dist_to_t[u]);
    }
  } 
  cout << (ans == INT_MAX ? -1 : ans) << "\n";
}

int main() {
  int cases; cin >> cases;
  while (cases--) {
  	solve();
  }
  return 0;
}