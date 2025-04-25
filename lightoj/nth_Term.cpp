/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://lightoj.com/problem/nth-term
*/

#include<bits/stdc++.h>
using namespace std;

#define nline '\n'
#define ll long long
#define MOD 10007
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


struct Matrix {
    vector<vector<ll>> a;
    int n, m;
    Matrix(int _n, int _m) : n(_n), m(_m) {
        a.assign(n, vector<ll>(m, 0));
    }
    Matrix(vector<vector<ll>> &v) {
        n = v.size();
        m = v[0].size();
        a.assign(n, vector<ll>(m, 0));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) 
                a[i][j] = v[i][j];
    }
    Matrix(const vector<vector<ll>> &v) {
        n = v.size();
        m = v[0].size();
        a.assign(n, vector<ll>(m, 0));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) 
                a[i][j] = v[i][j];
    }

    Matrix operator*(Matrix& b) {
        assert(m == b.n);
        int x = n, y = m, z = b.m;
        Matrix c(x, z);
        for (int i = 0; i < x; i++)
            for (int k = 0; k < y; k++)
                for (int j = 0; j < z; j++) {
                    c[i][j] += a[i][k] * b[k][j];
                    if (c[i][j] >= 1LL*MOD*MOD) c[i][j] -= 1LL * MOD * MOD;
                }
        for (int i = 0; i < x; i++)
            for (int j = 0; j < z; j++)
                c[i][j] %= MOD;
        return c;
    }

    Matrix pow(ll p) {
        assert(n == m);
        Matrix res = Matrix::Identity(n);
        Matrix cur = *this;
        for (; p; p >>= 1, cur = cur * cur) {
            if (p & 1)
                res = res * cur;
        }
        return res;
    }

    static Matrix Identity(int sz) {
        Matrix res(sz, sz);
        for (int i = 0; i < sz; i++)
            res[i][i] = 1;
        return res;
    }

    vector<ll>& operator[](int i) {
        return a[i];
    }
    const vector<ll>& operator[](int i) const {
        return a[i];
    }

    friend ostream& operator<<(ostream& os, Matrix &a) {
        for (int i = 0; i < a.n; i++) {
            for (int j = 0; j < a.m; j++)
                os << a[i][j] << " ";
            os << "\n";
        }
        return os;
    }
};

void pre_compute() {
    
}
void solve() {
    ll n, a, b, c;
    cin >> n >> a >> b >> c;
    if (n <= 2) {
        cout << 0 << nline;
        return;
    }
    Matrix mat({{a, 0, b, c},
                {1, 0, 0, 0},
                {0, 1, 0, 0},
                {0, 0, 0, 1}});
    Matrix base({{0},
                 {0},
                 {0},
                 {1}});
    ll k = (n - 3 + 1);
    Matrix res = mat.pow(k) * base;
    cout << res[0][0] << nline;
}

int main() {
    fastio();
    IN_OUT();
    int T = 1;
    cin >> T;
    pre_compute();
    for (int cases = 1; cases <= T; cases++) {
        cout << "Case " << cases << ": ";
        solve();
    }
    return 0;
}