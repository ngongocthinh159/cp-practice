/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://www.spoj.com/status/GSWORDS/
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

ll n;
const int MOD = 1e9 + 7;
struct Matrix {
    int n, m;
    vector<vector<ll>> a;
    Matrix(int _n, int _m) : n(_n), m(_m) {
        a.assign(n, vector<ll>(m, 0));
    }
    Matrix operator * (Matrix &b) {
        assert(m == b.n);
        int x = n, y = m, z = b.m;
        Matrix c(x, z);
        for (int i = 0; i < x; i++)
            for (int k = 0; k < y; k++)
                for (int j = 0; j < z; j++) {
                    c[i][j] += a[i][k] * b[k][j];
                    if (c[i][j] >= 1LL * MOD * MOD) c[i][j] -= 1LL * MOD * MOD;  
                }
        for (int i = 0; i < x; i++)
            for (int j = 0; j < z; j++)
                c[i][j] %= MOD;
        return c;
    }
    
    Matrix pow(ll p) {
        Matrix res = identity(n);
        Matrix cur = *this;
        while (p) {
            if (p & 1) res = res * cur;
            cur = cur * cur;
            p >>= 1;
        }
        return res;
    }

    Matrix identity(int n) {
        Matrix res(n, n);
        for (int i = 0; i < n; i++)
            res[i][i] = 1;
        return res;
    }

    friend ostream& operator << (ostream& os, Matrix &a) {
        for (int i = 0; i < a.n; i++) {
            for (int j = 0; j < a.m; j++)
                os << a[i][j] << " ";
            os << "\n";
        }

        return os;
    }
    
    vector<ll>& operator [] (int i) {
        return a[i];
    }
    const vector<ll>& operator [] (int i) const {
        return a[i];
    }
};
void solve() {
    cin >> n;
    Matrix base(3, 3);
    base[0][0] = base[0][1] = base[1][2] = base[2][0] = 1;
    Matrix col(3, 1);
    col[0][0] = 1;
    col[1][0] = 1;
    col[2][0] = 1;
    Matrix res = base.pow(n - 1) * col;
    cout << (res[0][0] + res[1][0]) % MOD << "\n";
}

int main() {
    fastio();
    IN_OUT();
    solve();
    return 0;
}