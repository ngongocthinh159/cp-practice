/**
 * Solution for: https://vjudge.net/problem/UVA-10557
*/

#include <bits/stdc++.h>
using namespace std;

int n;
vector<vector<pair<int,int>>> g;
vector<int> energy;
vector<bool> visited;
vector<int> dist;
bool dfs(int u) {
	if (u == n) return true;
  bool res = false;
  for (auto &nei : g[u]) {
    int v = nei.first;
    if (!visited[v]) {
      visited[v] = true;
      res = res || dfs(v);
    }
  }
  return res;
}
bool bellman(int s) {
  dist = vector<int>(n + 1, INT_MAX);
  dist[s] = -100;
  int u, v, w_uv;
  bool stopEarly = false;
  for (int i = 1; i <= n - 1; i++) {
    bool atLeast1 = false;
    for (int j = 1; j <= n; j++) {
      for (auto &nei : g[j]) {
        u = j; v = nei.first; w_uv = nei.second;
        if (dist[u] != INT_MAX && dist[u] + w_uv < 0 && dist[u] + w_uv < dist[v]) {
          dist[v] = dist[u] + w_uv;
          atLeast1 = true;
        }
      }
      
    }
    if (!atLeast1) {stopEarly = true; break;}
  }
  if (dist[n] <= 0) return true;
  if (stopEarly) return false;

  // find all vertices affected by negative cycle
  // if from any can reach d => ok
  visited = vector<bool>(n + 1, false);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      for (auto &nei : g[j]) {
        u = j; v = nei.first; w_uv = nei.second;
        if (dist[u] != INT_MAX && dist[u] + w_uv < 0 && dist[u] + w_uv < dist[v]) {
          if (!visited[v]) {
            visited[v] = true;
            if (dfs(v)) return true;
          }
        }
      }
    }
  }
  
	return false;
}
void solve() {
  energy = vector<int>(n + 1);
  g = vector<vector<pair<int,int>>>(n + 1);
  
  for (int i = 1; i <= n; i++) {
    int e, m;
    cin >> e >> m;
    energy[i] = -e;
    for (int j = 0; j < m; j++) {
      int v; cin >> v;
      g[i].push_back({v, 0});
    }
  }
  for (int i = 1; i <= n; i++) {
  	for (auto &p : g[i]) {
      p.second = energy[p.first];
    }
  }
  bool ans = bellman(1);
  if (ans) cout << "winnable" << "\n";
  else cout << "hopeless" << "\n";
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  
  cin >> n;
  while (n != -1) {
  	solve();
    cin >> n;
  }
  return 0;
}