/**
 * Solution for: https://www.spoj.com/problems/TRVCOST/
*/

#include <bits/stdc++.h>
using namespace std;

const int N = 500 + 5;
int n, u, q, v, a, b, w;
vector<vector<pair<int,int>>> g;
vector<int> dist;
struct comparator {
  bool operator() (const pair<int,int> &a, const pair<int,int> &b) const {
    if (b.second < a.second) return true;
    return false;
  }
};
void solve() {
  cin >> n;
  g = vector<vector<pair<int,int>>>(N);
  dist = vector<int>(N, INT_MAX);
  for (int i = 0; i < n; i++) {
    cin >> a >> b >> w;
    g[a].push_back({b, w});
    g[b].push_back({a, w});
  }
  cin >> u;
  priority_queue<pair<int,int>, vector<pair<int,int>>, comparator> pq;
  pq.push({u, 0});
  dist[u] = 0;
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
  cin >> q;
  for (int i = 0; i < q; i++) {
    int tmp; cin >> tmp;
    if (dist[tmp] == INT_MAX) cout << "NO PATH\n";
    else cout << dist[tmp] << "\n";
  }
}

int main() {
  solve();
  return 0;
}