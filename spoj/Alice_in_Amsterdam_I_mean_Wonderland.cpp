/**
 * Solution for: https://www.spoj.com/problems/UCV2013B/
*/

#include <bits/stdc++.h>
using namespace std;

int n, q;
string name;
unordered_map<int, string> iToName;
vector<vector<pair<long long,long long>>> g;
vector<vector<long long>> dists;
vector<bool> has;
void bellman(int s) {
  dists[s][s] = 0;
  for (int i = 1; i <= n - 1; i++) {
    for (int u = 0; u < n; u++) {
      for (auto &nei : g[u]) {
        long long v = nei.first;
        long long w_uv = nei.second;
        if (dists[s][u] != INT_MAX && dists[s][u] + w_uv < dists[s][v]) {
          dists[s][v] = dists[s][u] + w_uv;
        }
      }
    }
  }

  for (int i = 1; i <= n; i++) {
    for (int u = 0; u < n; u++) {
      for (auto &nei : g[u]) {
        long long v = nei.first;
        long long w_uv = nei.second;

        if (dists[s][u] != INT_MAX && dists[s][u] + w_uv < dists[s][v]) {
          has[s] = true; break;
        }
      }
    }
  }
}
void solve() {
  iToName.clear();
  g = vector<vector<pair<long long,long long>>>(n);
  dists = vector<vector<long long>>(n, vector<long long>(n, INT_MAX));
  has = vector<bool>(n, false);
  
  for (int i = 0; i < n; i++) {
    cin >> name;
    iToName[i] = name;
    for (int j = 0; j < n; j++) {
      int w; cin >> w;
      if (w == 0) continue;
      if (i == j && w > 0) w = 0;
      g[i].push_back({j, w});
    }
  }
  
  for (int i = 0; i < n; i++) {
    bellman(i);
  }
  
  cin >> q;
  for (int i = 0; i < q; i++) {
  	int u, v; cin >> u >> v;
   	string nameU = iToName[u];
    string nameV = iToName[v];
    
   	if (has[u]) cout << "NEGATIVE CYCLE" << "\n";
    else {
      cout << nameU << "-" << nameV;
      if (dists[u][v] == INT_MAX) cout << " NOT REACHABLE" << "\n";
      else cout << " " << dists[u][v] << "\n";
    }
  }
}


int main() {
  cin >> n; int i = 1;
  while (n) {
    cout << "Case #" << i++ << ":" << "\n";
    solve();
		cin >> n;
  }
  return 0;
}