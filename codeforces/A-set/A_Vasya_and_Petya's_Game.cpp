/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/problemset/problem/576/A
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

struct PFOption {
    long long mxN;
    bool pre_cal_SPF;
    bool pre_cal_phi1ToN;
    PFOption() {
        this->mxN = 0;
        this->pre_cal_SPF = true;
        this->pre_cal_phi1ToN = false;
    }
    PFOption(long long mxN, bool pre_cal_SPF = true, bool pre_cal_phi1ToN = false) {
        this->mxN = mxN;
        this->pre_cal_SPF = pre_cal_SPF;
        this->pre_cal_phi1ToN = pre_cal_phi1ToN;
    }
};
struct PF {
    vector<bool> isPrime;   // isPrime[N]
    vector<long long> spf;  // smallest prime factor of N
    vector<long long> phi;  // phi of N
    PFOption options;       // options to Sieve pre compute 

    PF(PFOption options) {
        this->options = options;
        if (options.pre_cal_SPF) {
            this->isPrime = vector<bool>(options.mxN + 1, true);
            this->spf.resize(options.mxN + 1);
            pre_compute_spf();
        }
        if (options.pre_cal_phi1ToN) {
            this->phi.resize(options.mxN + 1);
            pre_compute_phi1ToN();
        }
    }

    // Sieve modified version to find smallest prime factor of [0 -> N]
    // O(n*log(log(n))), n max ~ 10^7 ok
    void pre_compute_spf() {  // Check prime from 2 -> N
        int n = options.mxN;

        for (long long i = 0; i <= n; i++) {
            spf[i] = i;
        }
        for (long long i = 2; i <= sqrt(n); i++) {
            if (spf[i] == i) {
                for (long long j = i * i; j <= n; j += i) {  // iterate from i*i not i*2
                    spf[j] = min(spf[j], i);
                    isPrime[j] = false;
                }
            }
        }
    }

    // Sieve modified version to find phi [0 -> N]
    // O(n*log(n)), n max ~ 10^7 ok
    void pre_compute_phi1ToN() {
        int n = options.mxN;

        for (long long i = 0; i <= n; i++) {
            phi[i] = i;
        }
        for (long long i = 2; i <= n; i++) {
            if (phi[i] == i) {
                for (long long j = 2 * i; j <= n; j += i) {  // iterate from i*2
                    phi[j] = (phi[j] / i * (i - 1));
                }
            }
        }
    }

    vector<bool> getIsPrimeArray() {
        assert(options.pre_cal_SPF == true);
        return this->isPrime;
    }

    vector<long long> getSPFArray() {
        assert(options.pre_cal_SPF == true);
        return this->spf;
    }

    vector<long long> getPrecalPhiArray() {
        assert(options.pre_cal_phi1ToN == true);
        return this->phi;
    }

    // O(log(n))
    // Cnt number of divisors (divisible by n)
    // assert(options.pre_cal_SPF == true);
    // assert(n <= options.mxN);
    long long cntDivisors(long long n) {
        long long res = 1;
        while (n != 1) {
            long long factor = spf[n];
            long long cnt = 0;
            while (n % factor == 0) {
                cnt++;
                n /= factor;
            }
            res = res * (cnt + 1);  // Each power: can choost [0 -> power]
        }
        return res;
    }

    // O(log(n))
    // Get sum of all divisors (divisible by n)
    // assert(options.pre_cal_SPF == true);
    // assert(n <= options.mxN);
    long long sumDivisors(long long n) {
        long long ans = 1;
        while (n != 1) {
            long long factor = spf[n];
            long long power = 0;
            long long factorPow = factor;  // factor^(power+1)
            while (n % factor == 0) {
                power++;
                factorPow = factorPow * factor;
                n /= factor;
            }
            ans = ans * ((factorPow - 1) / (factor - 1));  // Tong cap so nhan
        }
        return ans;
    }

    // O(1)
    // assert(options.pre_cal_phi1ToN == true);
    // assert(n <= options.mxN);
    long long getPrecalPhi(long long n) {
        return phi[n];
    }

    // O(log(n))
    // Count number of X from [1, N] such that gcd(X,N) = 1 or Numbers of coprime number with N
    // assert(options.pre_cal_SPF == true);
    // assert(n <= options.mxN);
    long long calPhiLogN(long long n) {
        long long res = n;
        while (n != 1) {
            long long factor = spf[n];
            while (n % factor == 0) {
                n /= factor;
            }
            res = (res / factor * (factor - 1));
        }
        return res;
    }

    // O(log(n))
    // assert(options.pre_cal_SPF == true);
    // assert(n <= options.mxN);
    vector<pair<long long, long long>> primeFactorize(long long n) {
        vector<pair<long long, long long>> res;  // factor : cnt
        while (n != 1) {
            long long factor = spf[n];
            long long cnt = 0;
            while (n % factor == 0) {
                cnt++;
                n /= factor;
            }
            res.push_back({factor, cnt});
        }
        return res;
    }
};

int n;
void solve() {
    cin >> n;
    PF pf(PFOption(n + 5, true, false));
    vector<int> ans;
    for (int i = 2; i <= n; i++) {
        auto res = pf.primeFactorize(i);
        if (res.size() == 1) ans.push_back(i);
    }
    cout << ans.size() << nline;
    for (auto num : ans) {
        cout << num << " ";
    }
    cout << nline;
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
