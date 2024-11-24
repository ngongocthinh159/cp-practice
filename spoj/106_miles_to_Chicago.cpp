/**
 * Solution for: https://www.spoj.com/problems/CHICAGO/
*/

#include <bits/stdc++.h>
using namespace std;

struct Edge {
  double u, v, w;
  Edge(int _u, int _v, double _w): u(_u), v(_v), w(_w) {}
};
int n, m;
vector<vector<pair<int,double>>> g;
vector<double> dist;
struct comparator {
  bool operator() (const pair<int, double> &p1, const pair <int, double> &p2) const {
    if (p2.second > p1.second) return true;
    return false;
  }
};
void dijkstra(int s) {
  dist[s] = 1;
  priority_queue<pair<int, double>, vector<pair<int, double>>, comparator> pq;
  pq.push({s, 1});
  while (pq.size()) {
    auto p = pq.top(); pq.pop();
    int u = p.first;
    double w = p.second;
    for (auto &nei : g[u]) {
      int v = nei.first;
      double w_uv = nei.second;
      if (w*w_uv > dist[v]) {
        dist[v] = w*w_uv;
        pq.push({v, dist[v]});
      }
    }
  }
}
void solve() {
  g = vector<vector<pair<int, double>>>(n + 1);
  dist = vector<double>(n + 1, 0.0);
  for (int i = 0; i < m; i++) {
  	int u, v; cin >> u >> v;
    double w; cin >> w;
    g[u].push_back({v, w/100});
    g[v].push_back({u, w/100});
  }
  dijkstra(1);
  printf("%.6f percent\n", dist[n] * 100);
}

int main() {
  cin >> n;
  while (n) {
    cin >> m;
    solve();
    cin >> n;
  }
  return 0;
}