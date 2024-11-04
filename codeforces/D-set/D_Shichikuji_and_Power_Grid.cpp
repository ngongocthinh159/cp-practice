/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/contest/1245/problem/D
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
#define LINF 1e18
#define IINF 1e9
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

// #define ThinhNgo
#ifdef ThinhNgo
#define debug(x) cerr << #x<<" "; _print(x); cerr << endl;
#else
#define debug(x);
#endif
 
using ll = long long;
using ull = unsigned long long;
using lld = long double;
typedef tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag, tree_order_statistics_node_update > pbds; // find_by_order, order_of_key
 
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
template <class T, class V> void _print(pair <T, V> p) {cerr << "{"; _print(p.ff); cerr << ","; _print(p.ss); cerr << "}";}
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
void extendgcd(ll a, ll b, ll*v) {if (b == 0) {v[0] = 1; v[1] = 0; v[2] = a; return ;} extendgcd(b, a % b, v); ll x = v[1]; v[1] = v[0] - v[1] * (a / b); v[0] = x; return;} //pass an arry of size1 3
ll mminv(ll a, ll b) {ll arr[3]; extendgcd(a, b, arr); return arr[0];} //for non prime b
ll mminvprime(ll a, ll b) {assert(gcd(a, b) == 1); return expo(a, b - 2, b);} // inverse mod: a^-1 % b = a^(b-2) % b. When gcd(a,b)=1 (or b prime)
bool revsort(ll a, ll b) {return a > b;}
ll combination(ll n, ll r, ll m, ll *fact, ll *ifact) {ll val1 = fact[n]; ll val2 = ifact[n - r]; ll val3 = ifact[r]; return (((val1 * val2) % m) * val3) % m;}
void google(int t) {cout << "Case #" << t << ": ";}
vector<ll> sieve(int n) {int*arr = new int[n + 1](); vector<ll> vect; for (int i = 2; i <= n; i++)if (arr[i] == 0) {vect.push_back(i); for (int j = 2 * i; j <= n; j += i)arr[j] = 1;} return vect;}
ll mod_add(ll a, ll b, ll m) {a = a % m; b = b % m; return (((a + b) % m) + m) % m;}
ll mod_mul(ll a, ll b, ll m) {a = a % m; b = b % m; return (((a * b) % m) + m) % m;}
ll mod_sub(ll a, ll b, ll m) {a = a % m; b = b % m; return (((a - b) % m) + m) % m;}
ll mod_div(ll a, ll b, ll m) {a = a % m; b = b % m; return (mod_mul(a, mminvprime(b, m), m) + m) % m;}  //only for prime m
ll phin(ll n) {ll number = n; if (n % 2 == 0) {number /= 2; while (n % 2 == 0) n /= 2;} for (ll i = 3; i <= sqrt(n); i += 2) {if (n % i == 0) {while (n % i == 0)n /= i; number = (number / i * (i - 1));}} if (n > 1)number = (number / n * (n - 1)) ; return number;} //O(sqrt(N))
ll getRandomNumber(ll l, ll r) {return uniform_int_distribution<ll>(l, r)(rng);} 
struct custom_hash {static uint64_t splitmix64(uint64_t x) {x += 0x9e3779b97f4a7c15;x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;x = (x ^ (x >> 27)) * 0x94d049bb133111eb;return x ^ (x >> 31);}size_t operator()(uint64_t x) const {static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();return splitmix64(x + FIXED_RANDOM);}}; // https://codeforces.com/blog/entry/62393
struct custom_hash_pair {static uint64_t splitmix64(uint64_t x) {x += 0x9e3779b97f4a7c15;x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;x = (x ^ (x >> 27)) * 0x94d049bb133111eb;return x ^ (x >> 31);}size_t operator()(pair<uint64_t,uint64_t> x) const {static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();return splitmix64(x.first + FIXED_RANDOM)^(splitmix64(x.second + FIXED_RANDOM) >> 1);}}; // https://codeforces.com/blog/entry/62393
/*--------------------------------------------------------------------------------------------------------------------------*/
// #define ThinhNgo_use_cases



int n;
const int mxn = 2e3 + 5;
pair<int,int> cities[mxn];
ll cost[mxn];
ll k[mxn];
ll mst_w;
void pre_compute() {

}
ll get_edge_weight(int i, int j) {
    return 1LL*(abs(cities[i].first - cities[j].first) + abs(cities[i].second - cities[j].second))
        *(k[i] + k[j]);
}
pair<ll,int> dfs(int u, int par, vector<bool> &build, vector<unordered_set<int>> &g) {
    if (build[u]) return {0, u};
    pair<ll,int> res = {cost[u], u};
    for (auto &v : g[u]) {
        if (v != par) {
            auto p = dfs(v, u, build, g);
            if (res.first > p.first) {
                res = p;
            }
        }
    }
    return res;
}
vector<pair<int,int>> prim() {
    set<pair<ll,int>> S;
    vector<pair<ll,int>> min_e(n, {LINF,-1});
    vector<bool> visited(n);
    S.insert({0,0});
    min_e[0] = {0,-1};
    set<pair<ll,pair<int,int>>,greater<pair<ll,pair<int,int>>>> mst;
    ll weight = 0;
    while (S.size()) {
        auto p = *S.begin();
        S.erase(S.begin());
        ll w_par_u = p.first;
        int u = p.second;
        int par = min_e[u].second;

        visited[u] = true;
        weight += w_par_u;
        if (par != -1) mst.insert({w_par_u,{par,u}});

        for (int v = 0; v < n; v++) {
            if (v != u) {
                ll w_uv = get_edge_weight(u,v);
                if (!visited[v] && min_e[v].first > w_uv) {
                    S.erase({min_e[v].first, v});
                    min_e[v] = {w_uv, u};
                    S.insert({min_e[v].first, v});
                }
            }
        }
    }
    vector<pair<int,int>> res;
    for (auto p : mst) res.push_back(p.second);
    mst_w = weight;
    return res;
}
void solve() {
    cin >> n;
    int mnBuild = -1;
    ll mnBuildCost = LINF;
    for (int i = 0; i < n; i++) {
        int x, y; cin>> x >> y;
        cities[i] = {x, y};
    }
    for (int i = 0; i < n; i++) {
        cin >> cost[i];
        if (mnBuildCost > cost[i]) {
            mnBuildCost = cost[i];
            mnBuild = i;
        }
    }
    for (int i = 0; i < n; i++) {
        cin >> k[i];
    }
    auto edges = prim();
    vector<bool> build(n);
    vector<unordered_set<int>> g;
    vector<bool> deleted(edges.size());
    int deleted_cnt = 0;        
    g.resize(n);
    for (auto &e : edges) {
        g[e.first].insert(e.second);
        g[e.second].insert(e.first);
    }
    int idx = 0;
    for (auto &e : edges) {
        ll w = get_edge_weight(e.first, e.second);
        auto p1 = dfs(e.first, e.second, build, g);
        auto p2 = dfs(e.second, e.first, build, g);
        if (max(p1.first,p2.first) < w) {
            mst_w -= w;
            build[p1.second] = true;
            build[p2.second] = true; 
            g[e.first].erase(e.second);
            g[e.second].erase(e.first);
            deleted[idx] = true;
            deleted_cnt++;
        }
        idx++;
    }
    for (int i = 0; i < n; i++) if (build[i]) mst_w += cost[i];
    if (deleted_cnt == 0) {
        cout << mst_w + mnBuildCost << nline;
        cout << 1 << nline;
        cout << mnBuild + 1 << nline;
        cout << edges.size() << nline;
        for (auto e : edges) cout << e.first + 1 << " " << e.second + 1 << nline; 
    } else {
        int build_cnt = 0;
        for (int i = 0; i < n; i++) if (build[i]) build_cnt++;
        cout << mst_w << nline;
        cout << build_cnt << nline;
        for (int i = 0; i < n; i++) if (build[i]) cout << i + 1 << " ";
        cout << nline;
        cout << sz(edges) - deleted_cnt << nline;
        for (int i = 0; i < edges.size(); i++) if (!deleted[i]) cout << edges[i].first + 1 << " " << edges[i].second + 1 << nline; 
    }
}

int main() {
#ifdef ThinhNgo
    freopen("Error.txt", "w", stderr);
#endif
    fastio();
    IN_OUT();
    auto start1 = high_resolution_clock::now();
    int T = 1;
#ifdef ThinhNgo_use_cases
    cin >> T;
#endif
    pre_compute();
    while (T--) {
        solve();
    }
    auto stop1 = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop1 - start1);
#ifdef ThinhNgo
    cerr << "Time: " << duration . count() / 1000 << " ms" << endl;
#endif
}
