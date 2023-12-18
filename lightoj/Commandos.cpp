/**
 * Solution for: https://lightoj.com/problem/commandos
*/

#include <bits/stdc++.h>
using namespace std;

int n, r, s, d;
vector<vector<int>> g;
void bfs(int s, vector<int> &dist) {
  vector<bool> visited(n, false);
  deque<int> dq;
  dq.push_front(s);
  visited[s] = true;
  while (dq.size()) {
    int size = dq.size();
    for (int i = 0; i < size; i++) {
      int u = dq.back(); dq.pop_back();
      for (auto v : g[u]) {
        if (!visited[v]) {
          dist[v] = dist[u] + 1;
          visited[v] = true;
          dq.push_front(v);
        }
      }
    }
  }
}
void solve() {
  cin >> n >> r;
  vector<int> ds(n, 0);
  vector<int> dd(n, 0);
  g = vector<vector<int>>(n);
  for (int i = 0; i < r; i++) {
    int u,v; cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  cin >> s >> d;
  bfs(s, ds);
  bfs(d, dd);
  int ans = INT_MIN;
  for (int i = 0; i < n; i++) {
    ans = max(ans, ds[i] + dd[i]);
  }
	cout << ans << "\n";
}

int main() {
  int cases; cin >> cases; int i = 1;
  while (cases--) {
    cout << "Case " << i << ": "; i++;
    solve();
  }
  return 0;
}