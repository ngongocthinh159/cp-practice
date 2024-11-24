/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://www.spoj.com/problems/HS08PAUL/
*/
#pragma GCC optimize("O3,unroll-loops")
 
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
 
using namespace std;
using namespace chrono;
using namespace __gnu_pbds;

#define fastio() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
void IN_OUT() {
#ifndef ONLINE_JUDGE
freopen("Input.txt", "r", stdin);
freopen("Output.txt", "w", stdout);
#endif
}
#define MOD 1000000007
#define MOD1 998244353
#define INF 1e18
#define nline "\n"
#define pb push_back
#define ppb pop_back
#define mp make_pair
#define ff first
#define ss second
#define PI 3.141592653589793238462
#define set_bits(x) __builtin_popcountll(x)
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define ll long long
ll expo(ll a, ll b, ll mod) {if (a==0) return 1%mod; ll res = 1; while (b > 0) {if (b & 1)res = (res * a) % mod; a = (a * a) % mod; b = b >> 1;} return res;} // a = 0 return 0 | b = 0 return 1


const int mxN = 1e7 + 5;
bool isPrime[mxN + 1];
void sieve() {
    memset(isPrime, true, sizeof(isPrime));
    isPrime[0] = false;
    isPrime[1] = false;
    for (ll i = 2; i <= sqrt(mxN); i++) {
        if (isPrime[i]) {
            for (ll j = i*i; j <= mxN; j += i) {
                isPrime[j] = false;
            }
        }
    }
}

ll n;
vector<ll> a;
void solve() {
    ll n; cin >> n;
    sieve();
    ll mx = LONG_MIN;
    for (int i = 0; i < n; i++) {
        ll num; cin >> num; 
        a.push_back(num);
        mx = max(mx, num);
    }
    vector<ll> ans(mx + 1);
    ll j = 0;
    for (ll i = 0; i <= sqrt(mx); i++) {
        for (ll y = 0; y <= sqrt(sqrt(mx)); y++) {
            ll cur = i*i + pow(y,4);
            if (cur <= mx && isPrime[cur]) ans[cur] = 1;
        }
    }
    for (int i = 1; i < ans.size(); i++) {
        ans[i] = ans[i] + ans[i - 1];
    }
    for (int i = 0; i < n; i++) {
        cout << ans[a[i]] << nline;
    }
}

int main() {
#ifdef ThinhNgo
    freopen("Error.txt", "w", stderr);
#endif
    fastio();
    IN_OUT();
    auto start1 = high_resolution_clock::now();
    solve();
    auto stop1 = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop1 - start1);
#ifdef ThinhNgo
    cerr << "Time: " << duration . count() / 1000 << " ms" << endl;
#endif
}
