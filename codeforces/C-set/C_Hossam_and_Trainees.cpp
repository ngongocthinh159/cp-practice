/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/contest/1771/problem/C
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
using ll = long long;
#define nline "\n"
/*--------------------------------------------------------------------------------------------------------------------------*/

const int mxN = 1e5 + 5;
ll n;
ll a[mxN];
vector<bool> isPrime(mxN+1,true);
vector<ll> primes;
void sieve() {
    isPrime[0]=false;isPrime[1]=false;
    for (ll i = 2; i<=mxN;i++) {
        if (isPrime[i]) {
            primes.push_back(i);
            for (ll j = i*i; j <=mxN; j+=i) {
                isPrime[j] = false;
            }
        }
    }
}

void solve() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >>a[i];
    }
    unordered_set<ll> S;
    for (int i = 0; i<n; i++) {
        for (auto j : primes) {
            if (j*j > a[i]) break;
            if (a[i]%j==0) {
                if (S.count(j)){cout << "YES"<<nline; return;}
                S.insert(j);
                while (a[i]%j==0) a[i]/=j;
            }
        }
        if (a[i]!=1) {
            if (S.count(a[i])){cout << "YES"<<nline; return;}
            S.insert(a[i]);
        }
    }
    cout << "NO" <<nline;
}

int main() {
    fastio();
    IN_OUT();
    sieve();
    int cases; cin >> cases;
    while (cases--) {
        solve();
    }
    return 0;
}