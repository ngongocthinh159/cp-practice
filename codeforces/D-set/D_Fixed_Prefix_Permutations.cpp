/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/problemset/problem/1792/D
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

struct Node {
    vector<Node*> child;
    Node() {
        child.assign(11, nullptr);
    }
};
#define N 50005
#define M 10
int a[N][M], order[M], ans[N];

void pre_compute() {
    
}
void solve() {
    int n, m;
    cin >> n >> m;
    Node* root = new Node();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
        iota(order, order + m, 1);
        sort(order, order + m, [&](int k, int j) {
            return a[i][k - 1] < a[i][j - 1];
        });
        Node *p = root;
        for (int j = 0; j < m; j++) {
            if (!p->child[order[j]]) p->child[order[j]] = new Node();
            p = p->child[order[j]];
        }
    }
    for (int i = 0; i < n; i++) {
        Node *p = root;
        int cnt = 0;
        for (int j = 0; j < m; j++) {
            if (!p->child[a[i][j]]) break;
            p = p->child[a[i][j]];
            cnt++;
        }
        cout << cnt << ' ';
    }
    cout << nline;
}

int main() {
    fastio();
    IN_OUT();
    int T = 1;
    cin >> T;
    pre_compute();
    for (int cases = 1; cases <= T; cases++) {

        solve();
    }
    return 0;
}