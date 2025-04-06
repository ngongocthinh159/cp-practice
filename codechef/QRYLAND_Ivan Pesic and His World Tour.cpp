/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://www.codechef.com/problems/QRYLAND?tab=statement
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
#define LINF ((long long)1e18)
#define IINF ((int)1e9)
#define nline "\n"
#define pb push_back
#define ppb pop_back
#define mp make_pair
#define fi first
#define se second
#define PI 3.141592653589793238462
#define SET_BITS(x) __builtin_popcountll(x)
#define MASK(i) (1LL << (i))
#define BIT(x, i) (((x) >> (i)) & 1)
#define SZ(x) ((int)(x).size())
#define ALL(v) (v).begin(), (v).end()
#define FOR(i, a, b) for (int i = (a), _b = (b); i <= _b; i++)
#define FORD(i, b, a) for (int i = (b), _a = (a); i >= _a; i--)
#define REP(i, n) for (int i = 0, _n = (n); i < _n; i++)
#define FORE(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); i++)

// #define ThinhNgo_debug
#ifdef ThinhNgo_debug
#define debug(x) cerr << #x<<" "; _print(x); cerr << endl;
#else
#define debug(x);
#endif
 
using ll = long long;
using ull = unsigned long long;
using lld = long double;
typedef tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag, tree_order_statistics_node_update > pbds; // find_by_order, order_of_key
 
template<class X, class Y>
    bool minimize(X &x, const Y &y) {
        if (x > y) {
            x = y;
            return true;
        } else return false;
    }
template<class X, class Y>
    bool maximize(X &x, const Y &y) {
        if (x < y) {
            x = y;
            return true;
        } else return false;
    }

void _print(ll t) {cerr << t;}
void _print(int t) {cerr << t;}
void _print(string t) {cerr << t;}
void _print(char t) {cerr << t;}
void _print(lld t) {cerr << t;}
void _print(double t) {cerr << t;}
void _print(ull t) {cerr << t;}
 
template <class T, class V> void _print(pair <T, V> p);
template <class T> void _print(vector <T> v);
template <class T> void _print(set <T> v);
template <class T, class V> void _print(map <T, V> v);
template <class T> void _print(multiset <T> v);
template <class T, class V> void _print(pair <T, V> p) {cerr << "{"; _print(p.fi); cerr << ","; _print(p.se); cerr << "}";}
template <class T> void _print(vector <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T> void _print(set <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T> void _print(multiset <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T, class V> void _print(map <T, V> v) {cerr << "[ "; for (auto i : v) {_print(i); cerr << " ";} cerr << "]";}
void _print(pbds v) {cerr << "[ "; for (auto i : v) {_print(i); cerr << " ";} cerr << "]";}
 
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
/*---------------------------------------------------------------------------------------------------------------------------*/
ll __gcd__(ll a, ll b) {if (!a || !b) return a | b; unsigned shift = __builtin_ctz(a | b); a >>= __builtin_ctz(a); do { b >>= __builtin_ctz(b); if (a > b) swap(a, b); b -= a; } while (b); return a << shift;} // only a >= 0 && b >= 0
ll gcd(ll a, ll b) {a = abs(a); b = abs(b); return __gcd__(a, b);} // get abs(a), abs(b) in case a < 0 || b < 0
ll expo(ll a, ll b, ll mod) {if (a==0) return 1%mod; ll res = 1; while (b > 0) {if (b & 1)res = (res * a) % mod; a = (a * a) % mod; b = b >> 1;} return res;} // a = 0 return 0 | b = 0 return 1
ll expo(ll a, ll b) {ll res = 1; while (b > 0) {if (b & 1)res = res * a; a = a * a; b = b >> 1;} return res;} // a = 0 return 0 | b = 0 return 1
void extendgcd(ll a, ll b, ll*v) {if (b == 0) {v[0] = 1; v[1] = 0; v[2] = a; return ;} extendgcd(b, a % b, v); ll x = v[1]; v[1] = v[0] - v[1] * (a / b); v[0] = x; return;} //pass an arry of size1 3, calculate modular invese a^-1 % b, only work with a and b coprime
ll modinv(ll a, ll m) {ll arr[3]; extendgcd(a, m, arr); return arr[0];} // inverse mod: a^-1 % m for non prime m, and gcd(a,m)=1
ll modinvprime(ll a, ll m) {assert(gcd(a, m) == 1); return expo(a, m - 2, m);} // inverse mod: a^-1 % m = a^(m-2) % m. When gcd(a,m)=1 and m prime
bool revsort(ll a, ll b) {return a > b;}
ll combination(ll n, ll r, ll m, ll *fact, ll *ifact) {ll val1 = fact[n]; ll val2 = ifact[n - r]; ll val3 = ifact[r]; return (((val1 * val2) % m) * val3) % m;}
void google(int t) {cout << "Case #" << t << ": ";}
vector<ll> sieve(int n) {int*arr = new int[n + 1](); vector<ll> vect; for (int i = 2; i <= n; i++)if (arr[i] == 0) {vect.push_back(i); for (int j = 2 * i; j <= n; j += i)arr[j] = 1;} return vect;}
ll mod_add(ll a, ll b, ll m) {a = a % m; b = b % m; return (((a + b) % m) + m) % m;}
ll mod_mul(ll a, ll b, ll m) {a = a % m; b = b % m; return (((a * b) % m) + m) % m;}
ll mod_sub(ll a, ll b, ll m) {a = a % m; b = b % m; return (((a - b) % m) + m) % m;}
ll mod_div(ll a, ll b, ll m) {a = a % m; b = b % m; return (mod_mul(a, modinvprime(b, m), m) + m) % m;}  //only for prime m
ll phin(ll n) {ll number = n; if (n % 2 == 0) {number /= 2; while (n % 2 == 0) n /= 2;} for (ll i = 3; i <= sqrt(n); i += 2) {if (n % i == 0) {while (n % i == 0)n /= i; number = (number / i * (i - 1));}} if (n > 1)number = (number / n * (n - 1)) ; return number;} //O(sqrt(N))
ll randint(ll l, ll r) {return uniform_int_distribution<ll>(l, r)(rng);} 
struct custom_hash {static uint64_t splitmix64(uint64_t x) {x += 0x9e3779b97f4a7c15;x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;x = (x ^ (x >> 27)) * 0x94d049bb133111eb;return x ^ (x >> 31);}size_t operator()(uint64_t x) const {static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();return splitmix64(x + FIXED_RANDOM);}}; // https://codeforces.com/blog/entry/62393
struct custom_hash_pair {static uint64_t splitmix64(uint64_t x) {x += 0x9e3779b97f4a7c15;x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;x = (x ^ (x >> 27)) * 0x94d049bb133111eb;return x ^ (x >> 31);}size_t operator()(pair<uint64_t,uint64_t> x) const {static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();return splitmix64(x.first + FIXED_RANDOM)^(splitmix64(x.second + FIXED_RANDOM) >> 1);}}; // https://codeforces.com/blog/entry/62393
/*--------------------------------------------------------------------------------------------------------------------------*/


#define N 250005
int n, q, T = -1;
int big[N], chain[N], sz[N], par[N], depth[N], pos[N];
int segtree[4*N], mapped[N], phash[N], euler[N], val[N];
vector<int> g[N];

void build(int idx, int s, int e, int *arr) {
    if (s == e) {
        segtree[idx] = arr[s];
        return;
    }
    int m = (s + e)/2;
    build(2*idx, s, m, arr);
    build(2*idx + 1, m + 1, e, arr);
    segtree[idx] = segtree[2*idx] ^ segtree[2*idx + 1];
}
void update(int idx, int s, int e, int pos, int val) {
    if (s == e) {
        segtree[idx] = val;
        return;
    }
    int m = (s + e)/2;
    if (pos <= m)
        update(2*idx, s, m, pos, val);
    else 
        update(2*idx + 1, m + 1, e, pos, val);
    segtree[idx] = segtree[2*idx] ^ segtree[2*idx + 1];
}
ll query(int idx, int s, int e, int l, int r) {
    if (s > r || l > e || s > e || l > r) return 0;
    if (l <= s && e <= r) return segtree[idx];
    int m = (s + e)/2;
    return query(2*idx, s, m, l, r) ^ query(2*idx + 1, m + 1, e, l, r);
}

void dfs_sz(int u, int p) {
    sz[u] = 1;
    big[u] = -1;
    int mxc = 0;
    for (auto v : g[u]) if (v != p) {
        depth[v] = depth[u] + 1;
        par[v] = u;
        dfs_sz(v, u);
        sz[u] += sz[v];
        if (mxc < sz[v]) 
            mxc = sz[v], big[u] = v;
    }
}
void dfs_chain(int u, int p, int top) {
    chain[u] = top;
    euler[++T] = val[u];
    pos[u] = T;
    if (big[u] != -1) 
        dfs_chain(big[u], u, top);
    for (auto v : g[u]) if (v != p && v != big[u])
        dfs_chain(v, u, v);
}
bool query_hld(int u, int v) {
    int L = depth[v] + depth[u];

    ll cur = 0;
    while (chain[u] != chain[v]) {
        if (depth[chain[u]] < depth[chain[v]]) swap(u, v);
        cur ^= query(1, 0, n - 1, pos[chain[u]], pos[u]);
        u = par[chain[u]];
    }
    if (depth[u] > depth[v]) swap(u, v);
    cur ^= query(1, 0, n - 1, pos[u], pos[v]);

    L = L - 2*depth[u] + 1;
    return cur == phash[L];
}

void pre_compute() {

}
void solve() {
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        // mapping number from 1 -> N to random number from 1 -> 1e9
        // then calculate prefix hash [1->N] as xor of prefix mapped numbers
        mapped[i] = randint(1, (int) 1e9);
        phash[i] = phash[i - 1] ^ mapped[i];
    }
    for (int i = 1; i <= n; i++) {
        int x; cin >> x;
        val[i] = mapped[x];
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs_sz(1, -1);
    dfs_chain(1, -1, 1);
    build(1, 0, n - 1, euler);
    int t, x, y, z;
    for (int i = 0; i < q; i++) {
        cin >> t;
        if (t == 1) {
            cin >> x >> y;
            if (query_hld(x, y))
                cout << "Yes" << nline;
            else
                cout << "No" << nline;
        } else {
            cin >> x >> z;
            update(1, 0, n - 1, pos[x], mapped[z]);
        }
    }

    T = -1;
    for (int i = 1; i <= n; i++) g[i].clear();

}

int main() {
#ifdef ThinhNgo
    freopen("Error.txt", "w", stderr);
#endif
    fastio();
    IN_OUT();
    auto start1 = high_resolution_clock::now();
    
    pre_compute();
    int T = 1;
    cin >> T;
    for (int cases = 1; cases <= T; cases++) {

        solve();
    }
    
    auto stop1 = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop1 - start1);
#ifdef ThinhNgo
    cerr << "Time: " << duration . count() / 1000 << " ms" << endl;
#endif
}
