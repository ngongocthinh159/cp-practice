/*
    Solution for: https://lightoj.com/problem/extended-traffic
*/

#include <bits/stdc++.h>
using namespace std;
struct Edge {
	int u, v, w;
  Edge(int _u, int _v, int _w): u(_u), v(_v), w(_w) {}
};

const int N = 2*1e2 + 5;
int n, m, q;
int b[N];
vector<Edge> g;
void bellman(int s, int n, vector<Edge> &g, vector<int> &dist, vector<bool> &hasPath) {
  dist = vector<int>(n + 1, INT_MAX);
  hasPath = vector<bool>(n + 1, false);
  
  dist[s] = 0;
  hasPath[s] = true;
  int u, v, w_uv;
  bool stopEarly = false;
  for (int i = 1; i <= n - 1; i++) {
    bool atLeat1 = false;
    for (auto &edge : g) {
      u = edge.u; v = edge.v; w_uv = edge.w;
      if (dist[u] != INT_MAX && dist[u] + w_uv < dist[v]) {
        dist[v] = dist[u] + w_uv;
        hasPath[v] = true;
        atLeat1 = true;
      }
    }
    if (!atLeat1) {stopEarly = true; break;}
  }
  if (stopEarly) return;
  
  for (int i = 1; i <= n; i++) {
    for (auto &edge : g) {
      u = edge.u; v = edge.v; w_uv = edge.w;
      if (dist[u] != INT_MAX && dist[u] + w_uv < dist[v]) {
        dist[v] = dist[u] + w_uv;
        hasPath[v] = false;
      }
    }
  }
}
void solve() {
  g.clear();
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> b[i];
  }
  cin >> m;
  for (int i = 0; i < m; i++) {
    int u, v; cin >> u >> v;
    int cost_uv = (b[v] - b[u])*(b[v] - b[u])*(b[v] - b[u]);
    g.push_back(Edge(u, v, cost_uv));
  }
  cin >> q; 
  
  vector<int> dist;
  vector<bool> hasPath;
  bellman(1, n, g, dist, hasPath);
  for (int i = 0; i < q; i++) {
    int val; cin >> val;
    if (!hasPath[val] || dist[val] < 3) cout << "?" << "\n";
    else cout << dist[val] << "\n";
  }
}

int main() {
  int cases; cin >> cases; int i = 1;
  while (cases--) {
    cout << "Case " << i++ << ":\n";
    solve();
  }
  return 0;
}