/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/contest/1326/problem/D2
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
ll randint(ll l, ll r) {return uniform_int_distribution<ll>(l, r)(rng);} 
struct custom_hash {static uint64_t splitmix64(uint64_t x) {x += 0x9e3779b97f4a7c15;x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;x = (x ^ (x >> 27)) * 0x94d049bb133111eb;return x ^ (x >> 31);}size_t operator()(uint64_t x) const {static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();return splitmix64(x + FIXED_RANDOM);}}; // https://codeforces.com/blog/entry/62393
struct custom_hash_pair {static uint64_t splitmix64(uint64_t x) {x += 0x9e3779b97f4a7c15;x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;x = (x ^ (x >> 27)) * 0x94d049bb133111eb;return x ^ (x >> 31);}size_t operator()(pair<uint64_t,uint64_t> x) const {static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();return splitmix64(x.first + FIXED_RANDOM)^(splitmix64(x.second + FIXED_RANDOM) >> 1);}}; // https://codeforces.com/blog/entry/62393
/*--------------------------------------------------------------------------------------------------------------------------*/
#define ThinhNgo_use_cases


struct Manacher {
    string s;
    int n;
    vector<int> p; // p[i]: center i-th has palindrome bound [k,j] then p[i] = j - i + 1 = i - k + 1 (len of one side from center)
    Manacher(string &s) {
        this->s = s;
        n = s.size();
        _pre_process();
    }
    void _pre_process() {
        // transform orginal "ABA" => "#A#B#A#"
        string t;
        for (auto c : s) t += '#', t += c;
        t += '#';
        p = _manacher_odd(t); // p array is actually counted for transformed string
    }
    vector<int> _manacher_odd(string &str) {
        int n = str.size();
        string t = '^' + str + '$';
        vector<int> p(n + 2);
        for (int i = 1, l = 1, r = 1; i <= n; i++) {
            if (i <= r) p[i] = min(p[l + r - i], r - i + 1);
            while (t[i + p[i]] == t[i - p[i]]) ++p[i];
            if (i + p[i] - 1 > r) l = i - p[i] + 1,  r = i + p[i] - 1;
        }
        return vector<int>(p.begin() + 1, p.end() - 1);
    }

    int get_longest(int centerIdx, bool odd = true) {
        if (!odd) assert(centerIdx >= 1);
        
        int pidx = odd ? 2*centerIdx + 1 : 2*centerIdx; // convert from original to tranformed
        return p[pidx] - 1;
    }

    bool is_palindrome(int l, int r) {
        int centerIdx = (l + r + 1)/2;
        return get_longest(centerIdx, l%2==r%2) >= (r - l + 1);
    }

    // p[i]: center i-th has palindrome bound [k,j] then p[i] = j - i + 1 = i - k + 1 (len of one side from center)
    int get_p_at(int centerIdx, bool odd = true) {
        int pidx = odd ? 2*centerIdx + 1 : 2*centerIdx;
        return p[pidx]/2;
    }
};
vector<int> z_function(string s) {
    int n = s.size();
    vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; i++) {
        if (i <= r) z[i] = min(z[i - l], r - i + 1);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
        if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
    }
    return z;
}
void pre_compute() {

}
string s;
void solve() {
    cin >> s;
    int n = s.size();
    string rs = s;
    reverse(ALL(rs));
    auto z = z_function(rs + '#' + s);
    Manacher mana(s);
    int len = 1, _i = 0, _j = n;
    for (int i = 0; i < n; i++) {
        {   
            int len_k = mana.get_longest(i);
            int mxk = i + mana.get_p_at(i) - 1;
            int mnp = n - z[n + 1];
            if (mnp <= mxk + 1) {
                int len_p = n - (mxk + 1);
                int new_len = 2*len_p + len_k;
                if (new_len <= n && maximize(len, new_len)) {
                    _i = len_p - 1, _j = i - mana.get_p_at(i) + 1;
                }
            }

            int mnk = i - mana.get_p_at(i) + 1;
            int mxp = z[n + 1] - 1;
            if (mnk - 1 <= mxp) {
                int len_p = mnk;
                int new_len = 2*len_p + len_k;
                if (new_len <= n && maximize(len, new_len)) {
                    _i = i + mana.get_p_at(i) - 1, _j = n - len_p;
                }
            }
        }
        {
            if (i >= 1) {
                int len_k = mana.get_longest(i, false);
                int mxk = i + mana.get_p_at(i, false) - 1;
                int mnp = n - z[n + 1];
                if (mnp <= mxk + 1) {
                    int len_p = n - (mxk + 1);
                    int new_len = 2*len_p + len_k;
                    if (new_len <= n && maximize(len, new_len)) {
                        _i = len_p - 1, _j = i - mana.get_p_at(i, false);
                    }
                }

                int mnk = i - mana.get_p_at(i, false);
                int mxp = z[n + 1] - 1;
                if (mnk - 1 <= mxp) {
                    int len_p = mnk;
                    int new_len = 2*len_p + len_k;
                    if (new_len <= n && maximize(len, new_len)) {
                        _i = i + mana.get_p_at(i, false) - 1, _j = n - len_p;
                    }
                }
            }
        }
    }
    cout << (s.substr(0, _i + 1) + s.substr(_j, n - _j)) << nline;
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
