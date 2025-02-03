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
// #define ThinhNgo_use_cases




struct SuffixArray {
    string s;
    int n;
    vector<int> _p, _lcp, _idx_to_pidx;
    vector<vector<int>> rmq;
    bool query_lcp_ij = false;

    SuffixArray(string &str, bool query_lcp_ij = false) {
        s = str;
        n =  s.size();
        _p = suffix_array_construction(s);
        _lcp = lcp_construction(s, _p);

        if (query_lcp_ij) {
            this->query_lcp_ij = true;;
            int LOG = __lg(n) + 1;
            rmq.assign(LOG + 1, vector<int>(_lcp.size()));
            for (int i = 0; i < _lcp.size(); i++) rmq[0][i] = _lcp[i];
            for (int j = 1; j <= LOG; j++)
                for (int i = 0; i + (1 << j) < _lcp.size(); i++)
                    rmq[j][i] = min(rmq[j - 1][i], rmq[j - 1][i + (1 << (j - 1))]);
        }
    }

    vector<int> sort_cyclic_shifts(string const& s) {
        int n = s.size();
        const int alphabet = 256;

        // h = 0, sorted n cycle strings by comparing 2^0 = 1 (the first) character
        vector<int> p(n), c(n), cnt(max(alphabet, n), 0);
        for (int i = 0; i < n; i++)
            cnt[s[i]]++;
        for (int i = 1; i < alphabet; i++)
            cnt[i] += cnt[i-1];
        for (int i = 0; i < n; i++)
            p[--cnt[s[i]]] = i;
        c[p[0]] = 0;
        int classes = 1;
        for (int i = 1; i < n; i++) {
            if (s[p[i]] != s[p[i-1]])
                classes++;
            c[p[i]] = classes - 1;
        }

        // h = 1, 2,.. sorted n cycle strings by comparing 2^1,2,3.. first characters
        vector<int> pn(n), cn(n);
        for (int h = 0; (1 << h) < n; ++h) {
            for (int i = 0; i < n; i++) {
                pn[i] = p[i] - (1 << h);
                if (pn[i] < 0)
                    pn[i] += n;
            }
            fill(cnt.begin(), cnt.begin() + classes, 0);
            for (int i = 0; i < n; i++)
                cnt[c[pn[i]]]++;
            for (int i = 1; i < classes; i++)
                cnt[i] += cnt[i-1];
            for (int i = n-1; i >= 0; i--)
                p[--cnt[c[pn[i]]]] = pn[i];
            cn[p[0]] = 0;
            classes = 1;
            for (int i = 1; i < n; i++) {
                pair<int, int> cur = {c[p[i]], c[(p[i] + (1 << h)) % n]};
                pair<int, int> prev = {c[p[i-1]], c[(p[i-1] + (1 << h)) % n]};
                if (cur != prev)
                    ++classes;
                cn[p[i]] = classes - 1;
            }
            c.swap(cn);
        }
        return p;
    }

    vector<int> suffix_array_construction(string s) {
        s += (char) 0;
        vector<int> sorted_shifts = sort_cyclic_shifts(s);
        sorted_shifts.erase(sorted_shifts.begin());
        return sorted_shifts;
    }

    vector<int> lcp_construction(string const& s, vector<int> const& p) {
        // Kasai algorithm for lcp construction
        _idx_to_pidx.resize(n);
        for (int i = 0; i < n; i++)
            _idx_to_pidx[_p[i]] = i;

        int n = s.size();
        int k = 0;
        vector<int> lcp(n-1, 0);
        for (int i = 0; i < n; i++) {
            if (_idx_to_pidx[i] == n - 1) {
                k = 0;
                continue;
            }
            int j = p[_idx_to_pidx[i] + 1];
            while (i + k < n && j + k < n && s[i+k] == s[j+k])
                k++;
            lcp[_idx_to_pidx[i]] = k;
            if (k)
                k--;
        }
        return lcp;
    }

    const vector<int>& get_p_array() {
        return _p;
    }

    const vector<int>& get_lcp_array() {
        return _lcp;
    }

    const vector<int>& get_idx_to_pidx_array() {
        return _idx_to_pidx;
    }

    int _query_rmq(int l, int r) {
        int bit = 32 - __builtin_clz(r - l + 1) - 1;
        return min(rmq[bit][l], rmq[bit][r - (1 << bit) + 1]);
    }

    // query largest common prefix of 2 suffixes starting at index i and j in original string
    int query_lcp_suffix(int i, int j) {
        assert(i < n);
        assert(j < n);
        assert(query_lcp_ij == true);

        if (i == j) return n - i;
        int l = _idx_to_pidx[i], r = _idx_to_pidx[j];
        if (l > r) swap(l, r);
        r--;
        return _query_rmq(l, r);
    }

    // query largest common prefix of 2 suffixes at index i and j after sorted in p array
    int query_lcp_p_array(int i, int j) {
        assert(i < n);
        assert(j < n);
        assert(i <= j);
        assert(query_lcp_ij == true);

        if (i == j) return n - _p[i];
        j--;
        return _query_rmq(i, j);
    }

    // compare two sub-strings in the original string O(1)
    int compare_substr(int l1, int r1, int l2, int r2) {
        assert(query_lcp_ij == true);

        int len1 = r1 - l1 + 1;
        int len2 = r2 - l2 + 1;
        int pidx1 = _idx_to_pidx[l1];
        int pidx2 = _idx_to_pidx[l2];
        if (pidx1 > pidx2) swap(pidx1, pidx2);
        int common_len = query_lcp_p_array(pidx1, pidx2);
        common_len = min(common_len, min(len1, len2));

        int compare_idx1 = l1 + common_len;
        int compare_idx2 = l2 + common_len;
        if (compare_idx1 <= r1 && compare_idx2 <= r2) {
            if (s[compare_idx1] < s[compare_idx2]) return -1;
            return 1;
        } 
        else if (compare_idx1 <= r1) return 1;
        else if (compare_idx2 <= r2) return -1;
        return 0;
    }

        int _compare_with_suffix(string &t, int suffix_idx) {
        int i = 0, j = suffix_idx;
        while (i < t.size() && j < n && t[i] == s[j]) i++, j++;

        if (i < t.size() && j < n) {
            if (t[i] < s[j]) return -1;
            return 1;
        }
        if (i < t.size()) return 1;
        if (j < n) return -1;
        return 0;
    }
    // search an arbitrary str M in the original str O(m*logn)
    // return [l, r] in p array => str occurs at position [p[l], p[l + 1], ..., p[r]]
    // return [-1, -1] if str do not occur
    pair<int,int> search_str(string &t) {
        int lower_bound = -1, upper_bound = -1;
        {
            int l = -1, r = n;
            while (r - l > 1) {
                int m = l + (r - l)/2;
                if (_compare_with_suffix(t, _p[m]) <= 0)
                    r = m;
                else
                    l = m;
            }
            if (r != n) lower_bound = r;
        }
        if (lower_bound == -1) return {-1, -1};

        {
            int l = -1, r = n;
            while (r - l > 1) {
                int m = l + (r - l)/2;
                if (_compare_with_suffix(t, _p[m]) == -1)
                    r = m;
                else
                    l = m;
            }
            upper_bound = r;
        }
        if (lower_bound == upper_bound) return {-1, -1};

        return {lower_bound, --upper_bound};
    }

    void _print() {
        const char* headers[] = {"Index", "Suffix", "P", "LCP"};
        printf("%-5s %-20s %-5s %-5s\n", headers[0], headers[1], headers[2], headers[3]);
        for (int i = 0; i < n; i++) {
            if (i < n - 1)
                printf("%-5d %-20s %-5d %-5d\n", i, s.substr(_p[i]).c_str(), _p[i], _lcp[i]);
            else    
                printf("%-5d %-20s %-5d\n", i, s.substr(_p[i]).c_str(), _p[i]);
        }
    }
};

int n;
string s;
void pre_compute() {

}
void solve() {
    cin >> n >> s;
    n = s.size();
    string t = s;
    reverse(ALL(s));
    t += '#';
    t += s;
    reverse(ALL(s));
    SuffixArray sa(t, true);
    int ans = 1;
    for (int i = 0; i < n; i++) {
        if (0 <= i - 1 && i + 1 < n) {
            int idx1 = i + 1;
            int idx2 = n - (i - 1) - 1 + (n + 1);
            ans = max(ans, 1 + 2*sa.query_lcp_suffix(idx1, idx2));
        }
    }
    for (int i = 0; i < n; i++) {
        if (i + 1 >= n) continue;
        if (s[i] == s[i + 1]) {
            ans = max(ans, 2);
            if (0 <= i - 1 && i + 2 < n) {
                int idx1 = i + 2;
                int idx2 = n - (i - 1) - 1 + (n + 1);
                ans = max(ans, 2 + 2*sa.query_lcp_suffix(idx1, idx2));
            }
        }
    }
    cout << ans << nline;
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
