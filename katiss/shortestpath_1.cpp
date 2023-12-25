/**
 * Solution for: https://open.kattis.com/problems/shortestpath1
*/

#include <bits/stdc++.h>
using namespace std;

int n, m, q, s;
vector<vector<pair<int,int>>> g;
vector<int> dist;
vector<bool> affected;
void bellman(int s) {
  dist = vector<int>(n, INT_MAX);
  affected = vector<bool>(n, false);
  
  dist[s] = 0;
  bool stopEarly = false;
	for (int i = 0; i < n - 1; i++) {
    bool atLeast1 = false;
    for (int u = 0; u < n; u++) {
      for (auto &nei : g[u]) {
        int v = nei.first;
        int w_uv = nei.second;
        if (dist[u] != INT_MAX && dist[u] + w_uv < dist[v]) {
          dist[v] = dist[u] + w_uv;
          atLeast1 = true;
        }
      } 
    }
    if (!atLeast1) {stopEarly = true; break;}
  }
  if (stopEarly) return;
  
  for (int i = 0; i < n; i++) {
    for (int u = 0; u < n; u++) {
      for (auto &nei : g[u]) {
        int v = nei.first;
        int w_uv = nei.second;
        if (dist[u] != INT_MAX && dist[u] + w_uv < dist[v]) {
          dist[v] = dist[u] + w_uv;
          affected[v] = true;
        }
      }
    }
  }
}
void solve() {
  g = vector<vector<pair<int,int>>>(n);
  for (int i = 0; i < m; i++) {
    int u, v, w; cin>> u >> v >> w;
    g[u].push_back({v, w});
  }

  bellman(s);
  for (int i = 0; i < q; i++) {
  	int d; cin >> d;
    if (affected[d]) cout << "-Infinity" << "\n";
    else if (dist[d] == INT_MAX) cout << "Impossible" << "\n";
    else cout << dist[d] << "\n";
  }
}

int main() {
  cin >> n >> m >> q >> s;
  while (n || m || q || s) {
    solve();
    cout << "\n";
    cin >> n >> m >> q >> s;
  }
  return 0;
}