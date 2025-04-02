/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=314
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
#define ThinhNgo_use_cases

/**
 * ########### Point and Vector
 */
const double EPS = 1e-9;
int cmp(double x, double y) {
    if (x < y - EPS) return -1;
    if (x > y + EPS) return 1;
    return 0;
}

struct Point {
    double x, y;

    Point(double _x = 0, double _y = 0) : x(_x), y(_y) {}

    int cmp(const Point& q) const {
        if (x != q.x) return ::cmp(x, q.x); // x != q.x is just pre-checking the binary presentation of x and q.x first
        return ::cmp(y, q.y);
    }

    // operator overload to compare to Point objects with >, <, >=,..
    #define op(x) bool operator x (const Point& q) const { return cmp(q) x 0; }
    op(>) op(<) op(==) op(>=) op(<=) op(!=)
    #undef op

    Point operator+(const Point& q) const {
        return Point(x + q.x, y + q.y);
    }

    Point operator-(const Point& q) const {
        return Point(x - q.x, y - q.y);
    }

    Point operator*(double k) const {
        return Point(x*k, y*k);
    }
    
    Point operator/(double k) const {
        return Point(x / k, y / k);
    }

    double dot(const Point& q) const {
        return x * q.x + y * q.y;
    }

    double cross(const Point& q) const {
        return x * q.y - y * q.x;
    }

    double norm() { // dai luong the hien do lon, co the dung cong thuc khac
        return x * x + y * y;
    }

    double len() {
        return sqrt(norm());
    }

    Point rotate(double alpha) { // Proof: https://matthew-brett.github.io/teaching/rotation_2d.html
        double cosa = cos(alpha);
        double sina = sin(alpha);
        return Point(x * cosa - y * sina, x * sina + y * cosa);
    }
};


/**
 * ########### Line
 */
struct Line {
    double a, b, c;
    Point A, B;

    Line(double a, double b, double c) : a(a), b(b), c(c) {}

    Line(Point A, Point B) : A(A), B(B) {
        a = B.y - A.y;
        b = A.x - B.x;
        c = -(a * A.x + b * A.y);
    }

    Line(Point P, double k) {
        a = -k;
        b = 1;
        c = k * P.x - P.y;
    }

    double f(Point A) {
        return a * A.x + b * A.y + c;
    }

    double distFromPoint(const Point& p) const {
        return abs(p.x * a + p.y * b + c) / sqrt(a * a + b * b);
    }
};

bool areParallel(Line l1, Line l2) {
    return cmp(l1.a * l2.b, l1.b * l2.a) == 0;
}

bool areSame(Line l1, Line l2) {
    return areParallel(l1, l2) && cmp(l1.b * l2.c, l2.b * l1.c) == 0 
        && cmp(l1.c * l2.a, l2.c * l1.a) == 0;
}

bool areIntersect(Line l1, Line l2, Point &p) { // p is the intersect point (if have)
    if (areParallel(l1, l2)) return false;
    double d = l1.a * l2.b - l2.a * l1.b;
    double dx = l1.b * l2.c - l2.b * l1.c;
    double dy = l1.c * l2.a - l2.c * l1.a;
    p = Point(dx / d, dy / d);
    return true;
}

// calculate distance from point p to line if know two points belongs to line (a, b)
double distToLine(Point p, Point a, Point b, Point &c) { // c is projection of point p into line (a, b) (if have)
    Point ap = p - a, ab = b - a;
    double k = ap.dot(ab) / ab.norm();
    c = a + (ab * k);
    return (p - c).len();
}


/**
 * ########### Circle
 */
struct Circle : Point {
    double r;

    Circle(double x = 0, double y = 0, double r = 0) : Point(x, y), r(r) {}

    Circle(Point p, double r) : Point(p), r(r) {}

    bool contains(Point p) { // return true if point p is inside the circle
        return (*this - p).len() <= r + EPS;
    }

    bool intersect(Point p) { // return true if point p intersect with circle
        return ::cmp((*this - p).len(), r) == 0;
    }
};

vector<Point> intersection(Line l, Circle cir) {
    double r = cir.r;
    double a = l.a, b = l.b, c = l.c + l.a * cir.x + l.b * cir.y;
    vector<Point> res;

    double x0 = -a * c / (a * a + b * b);
    double y0 = -b * c / (a * a + b * b);

    if (c*c > r*r*(a*a + b * b) + EPS)
        return res;
    else if (fabs(c*c - r*r*(a*a + b*b)) < EPS) {
        res.push_back(Point(x0, y0) + Point(cir.x, cir.y));
        return res;
    }

    double d = r * r - c * c / (a * a + b * b);
    double mult = sqrt(d / (a * a + b * b));
    double ax, ay, bx, by;
    ax = x0 + b * mult;
    bx = x0 - b * mult;
    ay = y0 - a * mult;
    by = y0 + a * mult;

    res.push_back(Point(ax, ay) + Point(cir.x, cir.y));
    res.push_back(Point(bx, by) + Point(cir.x, cir.y));
    return res;
}

int x[4], y[4];

void pre_compute() {

}
void solve() {
    for (int i = 0; i < 4; i++) cin >> x[i] >> y[i];
    Line l1(Point(x[0], y[0]), Point(x[1], y[1]));
    Line l2(Point(x[2], y[2]), Point(x[3], y[3]));
    Point p;
    if (areSame(l1, l2))
        cout << "LINE" << nline;
    else if (areIntersect(l1, l2, p))
        cout << "POINT " <<  p.x << " " << p.y << nline;
    else
        cout << "NONE" << nline;
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
    cout << fixed << showpoint << setprecision(2);
    cout << "INTERSECTING LINES OUTPUT" << nline;
    while (T--) {
        solve();
    }
    cout << "END OF OUTPUT" << nline;
    auto stop1 = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop1 - start1);
#ifdef ThinhNgo
    cerr << "Time: " << duration . count() / 1000 << " ms" << endl;
#endif
}
