/**
 * Author: Thinh Ngo Ngoc
 * Solution for: 
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
/*--------------------------------------------------------------------------------------------------------------------------*/
#define ThinhNgo_use_cases

void pre_compute() {

}


string s;
char var;
bool is_var(char c) {
    return 'a' <= c && c <= 'z';
}
unordered_map<ll, ll> extract(string &s) {
    ll i = 0;
    ll n = s.size();
    unordered_map<ll, ll> res;
    while (i < n) {
        char sign = '+';
        if (s[i] == '+' || s[i] == '-') {
            if (s[i] == '-') sign = '-';
            i++;
        }

        ll a = 1;
        ll pow = 0;
        if (i < n && '0' <= s[i] && s[i] <= '9') {
            string curA = "";
            while (i < n && '0' <= s[i] && s[i] <= '9') {
                curA += s[i];
                i++;
            }
            a = stoi(curA);
        }
        
        if (i < n && s[i] == var) {
            if (i + 1 < n && s[i + 1] == '^') {
                i += 2;
                char sign2 = '+';
                if (s[i] == '+' || s[i] == '-') {
                    if (s[i] == '-') sign2 = '-';
                    i++;
                }
                string curPow = "";
                while (i < n && '0' <= s[i] && s[i] <= '9') {
                    curPow += s[i];
                    i++;
                }
                pow = stoi(curPow);
                if (sign2 == '-') pow *= -1;
            } else {
                pow = 1;
                i++;
            }
        } 

        if (sign == '-') a *= -1;
        res[pow] += a;
    }
    return res;
}
void solve() {
    cin >> s;
    var = '#';
    ll i = 0;
    ll n = s.size();
    vector<unordered_map<ll, ll>> v;
    while (i < n) {
        if (s[i] == '(') i++;
        string cur = "";
        while (i < n && s[i] != ')') {
            if (is_var(s[i])) var = s[i];
            cur += s[i++];
        }
        v.push_back(extract(cur));
        i++;
    }
    map<ll,ll, greater<ll>> M;
    for (auto [pow1, a1] : v[0]) {
        for (auto [pow2, a2] : v[1]) {
            ll pow = pow1 + pow2;
            ll a = a1*a2;
            M[pow] += a;
        }
    }
    string res = "";
    bool first = true;
    for (auto [pow, a] : M) {
        if (pow == 0) {
            if (a == 0) continue;
            else {
                if (a < 0) res += '-';
                else if (!first) res += '+';
                res += to_string(abs(a));
                first = false;
            }
        } else {
            if (a == 0) continue;
            else {
                if (a < 0) res += '-';
                else if (!first) res += '+';
                if (a != 1) res += to_string(abs(a));
                res += var;
                if (pow != 1) {
                    res += '^';
                    res += to_string(pow);
                }
                first = false;
            }
        }
    }
    cout << res << nline;
}

// This challenge will require knowledge of polynomial expansion.
/*
have the function PolynomialExpansion(str) take str which will be a string representing a polynomial containing only (+/-) integers, a letter, parenthesis, and the symbol "^", and return it in expanded form. For example: if str is "(2x^2+4)(6x^3+3)", then the output should be "12x^5+24x^3+6x^2+12". Both the input and output should contain no spaces. The input will only contain one letter, such as "x", "y", "b", etc. There will only be four parenthesis in the input and your output should contain no parenthesis. The output should be returned with the highest exponential element first down to the lowest.

More generally, the form of str will be: ([+/-]{num}[{letter}[{^}[+/-]{num}]]...[[+/-]{num}]...)(copy) where "[]" represents optional features, "{}" represents mandatory features, "num" represents integers and "letter" represents letters such as "x".


Input:
3
(2x^2+4)(6x^3+3)
(1x)(2x^-2+1)
(-1x^3)(3x^3+2)

Output:
12x^5+24x^3+6x^2+12
x+2x^-1
-3x^6-2x^3
*/
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
