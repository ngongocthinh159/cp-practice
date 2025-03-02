/**
 * Author: Thinh Ngo Ngoc
 * Solution for: 
*/

#include<bits/stdc++.h>
using namespace std;

#define fastio() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
void IN_OUT() {
#ifndef ONLINE_JUDGE
freopen("Input.txt", "r", stdin);
freopen("Output.txt", "w", stdout);
#endif
}
/*--------------------------------------------------------------------------------------------------------------------------*/

#define ll long long
const int MOD = 1e9 + 7;
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

ll k;
void solve() {
    Matrix base({{1, 2, 0, 5, 1},
                {1, 0, 0, 0, 0},
                {0, 1, 0, 0, 0},
                {0, 0, 1, 0, 0},
                {0, 0, 0, 1, 0}});
    Matrix col(5, 1);
    for (int i = 0; i < 5; i++) 
        cin >> col[5 - 1 - i][0];
    cin >> k;
    k++;
    if (k <= 5) {
        k--;
        cout << col[5 - 1 - k][0] << "\n";
        return;
    }
    Matrix res = base.pow(k - 5)*col;
    cout << res[0][0] << "\n";
}

int main() {
    fastio();
    IN_OUT();
    int T; cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}