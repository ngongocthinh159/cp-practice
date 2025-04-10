/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/problemset/problem/166/B
*/

#include<bits/stdc++.h>
using namespace std;

#define nline '\n'
#define ll long long
#define MOD 1000000007
#define MOD1 998244353
#define LINF ((long long)1e18)
#define IINF ((int)1e9)

#define fastio() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
void IN_OUT() {
#ifndef ONLINE_JUDGE
freopen("Input.txt", "r", stdin);
freopen("Output.txt", "w", stdout);
#endif
}
/*--------------------------------------------------------------------------------------------------------------------------*/

#define pll pair<ll,ll>
#define fi first
#define se second
int n, m;

void pre_compute() {
    
}
pll operator - (const pll& a, const pll &b) {
    return {a.fi - b.fi, a.se - b.se};
}
long long cross(const pll& a, const pll& b) {
    return a.fi * b.se - b.fi * a.se;
}
int ccw(pll& A, pll& B, pll& C) {
    ll res = cross(B - A, C - A);
    if (res < 0) return -1;
    return res > 0;
}
bool isInPolygon(pll &p, vector<pll>& P) {
    int n = P.size();
    if (P.size() <= 2)
        return false;
    if (ccw(P[0], P[n - 1], p) >= 0 || ccw(P[0], P[1], p) <= 0)
        return false;
    int l = 0, r = n;
    while (r - l > 1) {
        int m = l + (r - l)/2;
        if (ccw(P[0], P[m], p) > 0)
            l = m;
        else
            r = m;
    }
    return ccw(P[l], P[l + 1], p) > 0;
}
void convexHull(vector<pll>& P) {
    sort(P.begin(), P.end());
    P.erase(unique(P.begin(), P.end()), P.end());

    int n = P.size();
    vector<pll> up, down;
    for (int i = 0; i < n; i++) {
        while (up.size() >= 2 && ccw(up[up.size() - 2], up[up.size() - 1], P[i]) >= 0) up.pop_back();
        up.push_back(P[i]);
        while (down.size() >= 2 && ccw(down[down.size() - 2], down[down.size() - 1],  P[i]) <= 0) down.pop_back();
        down.push_back(P[i]);
    }
    P = down;
    for (int i = (int) up.size() - 2; i > 0; i--) P.push_back(up[i]);
}
void solve() {
    cin >> n;
    vector<pll> A(n);
    for (int i = 0; i < n; i++) {
        cin >> A[i].fi >> A[i].se;
    }
    convexHull(A);
    cin >> m;
    vector<pll> B(m);
    for (int i = 0; i < m; i++) {
        cin >> B[i].fi >> B[i].se;
    }
    convexHull(B);
    bool ok = true;
    for (auto &p : B) {
        if (!isInPolygon(p, A)) {
            ok = false;
            break;
        }
    }
    if (ok)
        cout << "YES" << nline;
    else
        cout << "NO" << nline;
}

int main() {
    fastio();
    IN_OUT();
    int T = 1;
    // cin >> T;
    pre_compute();
    for (int cases = 1; cases <= T; cases++) {

        solve();
    }
    return 0;
}