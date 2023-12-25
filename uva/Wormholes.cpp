/*
    Solution for: https://vjudge.net/problem/UVA-558
*/

#include <bits/stdc++.h>
using namespace std;

struct Edge {
  int u; int v; int w;
  Edge(int _u, int _v, int _w): u(_u), v(_v), w(_w) {}
};
const int N = 1e3 + 5;
int n, m;
vector<Edge> g;
bool bellman(int s, vector<Edge> &g, vector<int> &dist, int n) {
  bool negativeCyclce = false;
  int u, v, w_uv;
  dist = vector<int>(n + 1, INT_MAX);
  dist[s] = 0;
  
  bool stopEarly = false;
  for (int i = 1; i <= n - 1; i++) {
    bool atLeast1 = false;
    for (auto &edge : g) {
      u = edge.u; v = edge.v; w_uv = edge.w;
      if (dist[u] != INT_MAX && dist[u] + w_uv < dist[v]) {
        dist[v] = dist[u] + w_uv;
        atLeast1 = true;
      }
    }
    if (!atLeast1) {stopEarly = true; break;}	// stop early
  }
  if (stopEarly) return false;
  
  // Not stop early, relax 1 more checking negative cycle
  for (auto &edge : g) {
    u = edge.u; v = edge.v; w_uv = edge.w;
    if (dist[u] != INT_MAX && dist[u] + w_uv < dist[v]) {
      negativeCyclce = true; break;
    }
  }
  return negativeCyclce;
}
void solve() {
  g.clear();
  cin >> n >> m;
  for (int i = 0; i < m; i++) {
    int u, v, w; cin >> u >> v >> w;
    g.push_back(Edge(u, v, w));
  }
  vector<int> dist;
  bool ans = bellman(0, g, dist, n);
  cout << (ans ? "possible" : "not possible") << "\n";
}

int main() {
  int cases; cin >> cases;
  while (cases--) {
  	solve();
  }
  return 0;
}