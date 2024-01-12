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
#define f(i,s,e) for(long long int i=s;i<e;i++)
#define cf(i,s,e) for(long long int i=s;i<=e;i++)
#define rf(i,e,s) for(long long int i=e;i>=s;i--)
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
ll directions[8][2] = {{-1,0},{0,-1},{1,0},{0,1},{-1,-1},{1,1},{-1,1},{1,-1}};
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
void yes() { cout<<"YES\n"; }
void no() { cout<<"NO\n"; }
void OPEN(string s) {
#ifndef TESTING
    freopen((s + ".in").c_str(), "r", stdin);
    freopen((s + ".out").c_str(), "w", stdout);
#endif
}

/*  All Required define Pre-Processors and typedef Constants */
typedef long int int32;
typedef unsigned long int uint32;
typedef long long int int64;
typedef unsigned long long int  uint64;

/* clang-format on */
void solveUsingMedianFact();
void solveUsingDP();
void solveUsingDP2();

/* Main()  function */
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    /* 
    - Median là số giảm thiểu tối đa sự khác biệt của tổng sự khác biệt khi tính từ median.
    - Hay nói cách khác, khi tìm 1 số X để tất cả các số trong dãy giảm về/tăng lên bằng 
    số X đó mà yêu cầu ít sự tăng giảm nhất khi X = median.
        + Với bộ số với số số hạng lẻ: thì chọn median.
        + Với bộ số với số số hạng chẵn: trong khoảng 2 số chính 
        giữa chọn số nào cũng được median 1 <= x <= median 2.

    Chứng minh đọc thêm tại: 
    https://math.stackexchange.com/questions/113270/the-median-minimizes-the-sum-of-absolute-deviations-the-ell-1-norm 
    */
    solveUsingMedianFact();
    // solveUsingDP();
    // solveDP2();
}

void solveUsingMedianFact() {
    ll n, m, d, min = LLONG_MAX, ans = 0;
    cin >> n >> m >> d;
    ll nums[n*m];
    f(i,0,n*m) {
        cin >> nums[i];
    }
    sort(nums, nums + n*m);
    ll median = (n*m + 1) / 2;
    median--;
    median = nums[median];
    f(i,0,n*m) {
        if (abs(nums[i] - median) % d != 0) {
            cout << -1 << "\n";
            return;
        }
        ans+=abs(nums[i] - median)/d;
    }
    cout << ans << "\n";
}

void solveUsingDP() {
    ll n, m, d, min = LLONG_MAX;
    cin >> n >> m >> d;
    ll nums[n*m] = {0};
    ll prefix[n*m] = {0};
    ll surfix[n*m] = {0};
    f(i,0,n*m) {
        cin >> nums[i];
    }
    sort(nums, nums + n*m);
    f(i,0,n*m) {
        prefix[i] = i == 0 ? nums[i] : nums[i] + prefix[i - 1];
    }
    rf(i,n*m-1,0) {
        surfix[i] = i == n*m - 1 ? nums[i] : nums[i] + surfix[i + 1];
    }
    f(i,0,n*m) {
        ll cur = surfix[i] - prefix[i] + nums[i]*(2*(i + 1) - n*m - 1); // Draw to get this formular
        if (cur % d != 0) {
            cout << -1 << "\n";
            return;
        } 
        if (min > cur) {min = cur;}
    }
    cout << (int) min/d << "\n";
}

void solveUsingDP2() {
    ll n, m, d, sum = 0, min = INFF;
    cin >> n >> m >> d;
    ll nums[n*m];
    ll l[n*m];
    ll r[n*m];
    l[0] = 0;
    r[n*m - 1] = 0;
    f(i,0,n*m) {
        cin >> nums[i];
        sum += nums[i];
    }
    sort(nums, nums + n*m);
    f(i,1,n*m) {
        if ((nums[i] - nums[i - 1]) % d != 0) {
            cout << -1 << "\n";
            return;
        }
        l[i] = l[i - 1] + i*(nums[i] - nums[i - 1])/d;
    }
    rf(i,n*m-2,0) {
        r[i] = r[i + 1] + (n*m - i - 1)*(nums[i + 1] - nums[i])/d;
    }
    f(i,0,n*m) {
        ll tmp;
        if (nums[i]*n*m >= sum) tmp = (nums[i]*n*m - sum)/d + 2*r[i]; // Number of operations needed to all number reach to nums[i]
        else if (nums[i]*n*m < sum) tmp = (sum - nums[i]*n*m)/d + 2*l[i];  // Number of operations needed to all number reach to nums[i]
        if (min > tmp) min = tmp;  // Number of operations still smaller than min => update min
    }
    cout << min << "\n";
}

/* Main() Ends Here */