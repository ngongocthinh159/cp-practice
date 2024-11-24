/*
    Solution for: https://www.spoj.com/problems/SHPATH/
*/

#include <bits/stdc++.h>
using namespace std;

int n;
vector<vector<pair<int,int>>> g;
vector<int> dist;
struct comparator {
  bool operator() (const pair<int,int> &a, const pair<int,int> &b) const {
    if (b.second < a.second) return true;
    return false;
  }
};
int shortestPath(int src, int tar) {
  dist = vector<int>(n + 1, INT_MAX);
  priority_queue<pair<int,int>, vector<pair<int,int>>, comparator> pq;
  pq.push({src, 0});
  dist[src] = 0;
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
  return dist[tar];
}
void solve() {
  cin >> n;
  g = vector<vector<pair<int,int>>>(n + 1);
  unordered_map<string,int> mp;
  for (int u = 1; u <= n; u++) {
    string name; cin >> name;
    mp[name] = u;
    int p; cin >> p;
    for (int j = 0; j < p; j++) {
      int v, w; cin >> v >> w;
      g[u].push_back({v, w});
    }
  }
  int r; cin >> r;
  for (int i = 0; i < r; i++) {
    string name1, name2; cin >> name1 >> name2;
    cout << shortestPath(mp[name1], mp[name2]) << "\n";
  }
}

int main() {
  int cases; cin >> cases;
  while (cases--) {
  	solve();  
  }
  return 0;
}