#include <bits/stdc++.h>
using namespace std;

/* clang-format off */

/* TYPES  */
#define ll long long
#define pii pair<int, int>
#define pll pair<long long, long long>
#define vi vector<int>
#define vll vector<long long>
#define mii map<int, int>
#define si set<int>
#define sc set<char>

/* FUNCTIONS */
#define f(i,s,e) for(long long int i=(s);i<(e);i++)
#define cf(i,s,e) for(long long int i=(s);i<=(e);i++)
#define rf(i,e,s) for(long long int i=(e);i>=(s);i--)
#define fe(a, b) for (auto&(a) : (b))
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define eb emplace_back

/* PRINTS */
template <class T>
void print_v(vector<T> &v) { cout << "{"; for (auto x : v) cout << x << ","; cout << "\b}"; }

/* UTILS */
#define MOD 1000000007
#define PI 3.1415926535897932384626433832795
double EPS = 1e-9;
int INF = 1000000005;
long long INFF = 1000000000000000005LL;
int directions[8][2] = {{-1,0},{0,1},{1,0},{0,-1},{-1,1},{1,1},{1,-1},{-1,-1}}; // UP-RIGHT-BOTTOM-DOWN || NORTH-EAST-SOUTH-WEST, From dir[4] Right of Up then clock wise
#define read(type) readInt<type>()
ll min(ll a,int b) { if (a<b) return a; return b; }
ll min(int a,ll b) { if (a<b) return a; return b; }
ll max(ll a,int b) { if (a>b) return a; return b; }
ll max(int a,ll b) { if (a>b) return a; return b; }
ll gcd(ll a,ll b) { if (b==0) return a; return gcd(b, a%b); } // Greatest common divisor (Uoc chung lon nhat): O(log(min(a,b))
ll lcm(ll a,ll b) { return a/gcd(a,b)*b; } // Lowest common mutiple (Boi chung nho nhat): O(log(min(a,b))
string to_upper(string a) { for (int i=0;i<(int)a.size();++i) if (a[i]>='a' && a[i]<='z') a[i]-='a'-'A'; return a; }
string to_lower(string a) { for (int i=0;i<(int)a.size();++i) if (a[i]>='A' && a[i]<='Z') a[i]+='a'-'A'; return a; }
string int_to_string(ll a) { char x[100]; sprintf(x, "%lld", a); string s = x; return s; }
ll string_to_int(string a) { char x[100]; ll res; strcpy(x, a.c_str()); sscanf(x, "%lld", &res); return res; }
bool prime(ll a) { if (a==1) return 0; for (int i=2;i<=round(sqrt(a));++i) if (a%i==0) return 0; return 1; }
ll mod(ll x, ll _mod) { return (((x%_mod) + _mod) % _mod); }
ll addMod(ll a, ll b, ll _mod) { return mod(mod(a, _mod) + mod(b, _mod), _mod); }
ll subMod(ll a, ll b, ll _mod) { return mod(mod(a, _mod) - mod(b, _mod), _mod); }
ll mulMod(ll a, ll b, ll _mod) { return mod(mod(a, _mod) * mod(b, _mod), _mod); }
ll powMod(ll x, ll n, ll _mod) { if (n == 0) return 1%_mod; ll u = powMod(mod(x,_mod),n/2,_mod); u = (u*u)%_mod; if (n%2 == 1) u = (u*(mod(x,_mod)))%_mod; return u; } // (x^n)%_mod
ll inverseMod(ll a, ll _mod) { if (gcd(a, _mod) != 1) {cout << "There is no inverse mod of " << a << " and " << _mod << "\n"; return -1;}; return powMod(mod(a,_mod), _mod-2, _mod); } // Return -1 if ((1/a)%_mod) not exist (a and _mod not coprime)
ll divMod(ll a, ll b, ll _mod) { ll tmp = inverseMod(b, _mod); if (tmp == -1) {cout << "There is no divided mod of " << a << " and " << b << "\n"; return -1;} return (((mod(a, _mod))*inverseMod(mod(b, _mod), _mod))%_mod); } // Return -1 if ((1/b)%_mod) not exist (b and _mod not coprime)
void yes() { cout<<"YES\n"; }
void no() { cout<<"NO\n"; }
void OPEN() {
    freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
}

/*  All Required define Pre-Processors and typedef Constants */
typedef long int int32;
typedef unsigned long int uint32;
typedef long long int int64;
typedef unsigned long long int  uint64;

/* clang-format on */
void solve1();
void solve2();

/* Main()  function */
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    // solve1(); // O(n*m*(n + m))
    solve2(); // O(n*m)
}

void solve1() {
    ll m, n;
    cin >> m >> n;
    int A[m][n], B[m][n], C[m][n];
    f(i,0,m) {
        f(j,0,n) {
            cin >> B[i][j];
            A[i][j] = 1;
            C[i][j] = 0;
        }
    }
    f(i,0,m) {
        f(j,0,n) {
            if (B[i][j] == 0) {
                f(k,0,n)
                    A[i][k] = 0;
                f(q,0,m)
                    A[q][j] = 0;
            }
        }
    }
    f(i,0,m) {
        f(j,0,n) {
            if (A[i][j]) {
                f(k,0,n)
                    C[i][k] = 1;
                f(q,0,m)
                    C[q][j] = 1;
            }
        }
    }
    f(i,0,m) {
        f(j,0,n) {
            if (C[i][j] != B[i][j]) {cout << "NO\n"; return;}
        }
    }
    cout << "YES\n";
    f(i,0,m) {
        f(j,0,n) {
            cout << A[i][j] << " ";
        }
        cout << "\n";
    }
}

void solve2() {
    ll m, n;
    cin >> m >> n;
    int matrix[m][n];
    bool rows[m]; // mark 0 for row, rows[i] = true mean all row i = 0
    bool cols[n]; // mark 0 for col, cols[i] = true mean all col i = 0
    bool rows2[m]; // mark 1 for row, rows[i] = true mean all row i = 1 
    bool cols2[n]; // mark 1 for col, cols[i] = true mean all row i = 1
    memset(rows, false, sizeof(rows));
    memset(cols, false, sizeof(cols));
    memset(rows2, false, sizeof(rows2));
    memset(cols2, false, sizeof(cols2));
    f(i,0,m) {
        f(j,0,n) {
            cin >> matrix[i][j];
            if (matrix[i][j] == 0) {rows[i] = true; cols[j] = true;} // mark row, col to all 0
        }
    }
    f(i,0,m) {
        f(j,0,n) {
            if (matrix[i][j] == 1) {
                int cnt = 0;
                f(k,0,4) {
                    int newX = i + directions[k][0];
                    int newY = j + directions[k][1];
                    if (!(0 <= newX && newX <= m - 1 && 0 <= newY && newY <= n - 1) || matrix[newX][newY] == 1) cnt++;
                }
                if (cnt == 4) {
                    if (!rows[i] && !cols[j]) {
                        rows2[i] = true; cols2[j] = true; // mark row, col to all 1
                    }
                }
            }
        }
    }
    f(i,0,m) {
        f(j,0,n) {
            // if matrix[i][j] == 1, then OR all row i is 1, OR all col j is 1 otherwise => False to create matrix
            if (matrix[i][j] == 1 && !(rows2[i] || cols2[j])) {cout << "NO\n";return;}
        }
    }
    cout << "YES\n";
    f(i,0,m) {
        f(j,0,n) {
            if (rows[i] || cols[j]) cout << "0 ";
            else cout << "1 ";
        }
        cout << "\n";
    }
}

/* Main() Ends Here */