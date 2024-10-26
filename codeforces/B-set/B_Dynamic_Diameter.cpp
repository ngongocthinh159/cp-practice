/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/gym/102694/problem/B
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


int _diameter;
// top sort
// 1 based-index vertice
// adjacency list should contain parent (as the indeg = 1 meaning leaf node)
// result: res[0] = diameter len, res[1] = first center, res[2] = second center (-1 when there is no second)
vector<int> findCenters(vector<vector<int>> &g) {
    vector<int> indeg(g.size());
    for (int u = 1; u < g.size(); u++) {
        for (auto v : g[u]) {
            indeg[v]++;
        }
    }
    deque<int> q;
    vector<bool> visited(g.size());
    for (int i = 1; i < g.size(); i++) {
        if (indeg[i] <= 1) { // case graph only one node indeg = 0
            q.push_back(i);
            visited[i] = true;
        }
    }
    int half_diameter = 0;
    int remain = g.size() - 1;
    while (q.size() && remain > 2) {
        int size = q.size();
        for (int i = 0; i < size; i++) {
            int u = q.back(); q.pop_back();
            remain--;
            for (auto v : g[u]) {
                if (!visited[v]) {
                    if (--indeg[v] == 1) {
                        visited[v] = true;
                        q.push_front(v);
                    }
                }
            }
        }
        half_diameter++;
    }
    
    vector<int> ans(3, -1);
    bool twoCenters = q.size() == 2;
    ans[0] = half_diameter*2 + (twoCenters ? 1 : 0);
    ans[1] = q.back(); q.pop_back();
    if (twoCenters) ans[2] = q.back();
    return ans;
}
vector<int> findDiameterEndNodes(vector<vector<int>> &g) {
    auto res = findCenters(g);
    int diameter = res[0];
    _diameter = diameter;
    int firstCenter = res[1];
    int secondCenter = res[2];

    // edge cases
    if (diameter == 0) {
        return {firstCenter};
    } else if (diameter == 1) {
        return {firstCenter, secondCenter};
    }

    deque<int> q;
    vector<bool> visited(g.size());
    if (firstCenter != -1 && secondCenter != -1) { // two centers push all nearby center points to queue then bfs from that
        visited[firstCenter] = visited[secondCenter] = true;
        for (auto v : g[firstCenter]) {
            if (v == secondCenter) continue;
            q.push_front(v);
            visited[v] = true;
        }
        for (auto v : g[secondCenter]) {
            if (v == firstCenter) continue;
            q.push_front(v);
            visited[v] = true;
        }
    } else {
        visited[firstCenter] = true;
        for (auto v : g[firstCenter]) {
            q.push_front(v);
            visited[v] = true;
        }
    }
    vector<int> ans;
    while (q.size()) { // expand from 1 or 2 centers
        int size = q.size();
        vector<int> vec;
        for (int i = 0; i < size; i++) {
            int u = q.back(); q.pop_back();
            vec.push_back(u);
            for (auto v : g[u]) {
                if (!visited[v]) {
                    visited[v] = true;
                    q.push_front(v);
                }
            }
        }

        if (q.size() == 0) { // last level
            ans = vec;
        }
    }
    return ans;
}
int n;
void pre_compute() {

}
void solve() {
    cin >> n;
    vector<vector<int>> g(n + 1);
    for (int i = 1; i <= n -1 ; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<int> endPoints = findDiameterEndNodes(g);
    
    unordered_set<int> S;
    for (int x : endPoints) {
        S.insert(x);
        // cout << x << nline;
    }
    for (int i = 1; i <= n; i++) {
        if (S.count(i)) {
            cout << _diameter + 1 << nline;
        } else {
            cout << _diameter << nline;
        }
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
