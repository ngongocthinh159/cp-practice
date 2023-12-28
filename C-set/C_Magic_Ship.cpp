/**
 * Solution for: https://codeforces.com/problemset/problem/1117/C
*/

#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
int n;
pair<int,int> st, fi;
string s;
int prex[N];
int prey[N];
string tmp = "UDLR";
vector<pair<int,int>> moves = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
bool check(long long x) {
   long long x3 = st.first + (x/n)*prex[n - 1] + prex[x%n - 1];
   long long y3 = st.second + (x/n)*prey[n - 1] + prey[x%n - 1];
   return abs(fi.first - x3) + abs(fi.second - y3) <= x; 
}
void solve() {
    cin >> st.first >> st.second >> fi.first >> fi.second;
    cin >> n;
    cin >> s;
    if (st.first == fi.first && st.second == fi.second) {cout << 0 << "\n"; return;}
    for (int i = 0; i < n; i++) {
        int idx;
        for (int j = 0; j < tmp.size(); j++) {
            if (s[i] == tmp[j]) {idx = j; break;}
        }
        int dx = moves[idx].first; int dy = moves[idx].second;
        prex[i] = i == 0 ? dx : dx + prex[i - 1];
        prey[i] = i == 0 ? dy : dy + prey[i - 1];
    }

    long long l = 0, r = 2e14 + 5;
    long long ans = -1;
    while (l <= r) {
        long long m = l + (r - l)/2;

        if (check(m)) {
            ans = m;
            r = m - 1;
        } else  {
            l = m + 1;
        }
    }
    cout << ans << "\n";
}

int main() {
    solve();
    return 0;
}