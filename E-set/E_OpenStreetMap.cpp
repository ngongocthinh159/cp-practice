#include <bits/stdc++.h>
using namespace std;

/* clang-format off */

/* TYPES  */
#define ll long long

/* FUNCTIONS */
#define cf(i,s,e) for(long long int i=(s);i<=(e);i++)
#define fi first
#define se second
#define pb push_back

/* clang-format on */
#define MAXN 3000
ll n, m, a, b, g0, x, y, z, sum = 0;
int cur;
int matrix[MAXN][MAXN];
deque<int> q;

/* Main()  function */
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m >> a >> b;
    cin >> g0 >> x >> y >> z;

    // Build maxtrix
    cf(i,1,n) {
        cf(j,1,m) {
            matrix[i-1][j-1] = g0;
            g0 = (g0*x+y)%z;
        }
    }

    // Using monotonic queue
    // Get min val for each col [i,j] -> [i + a - 1,j] that (0 <= i <= n-a) (0 <= j <= m - 1)
    // Imagine one col will be represented by that min val
    cf(j,0,m-1) {
        q.clear();

        cf(i,0,n-1) {
            for (;q.size() > 0 && matrix[q.front()][j] >= matrix[i][j];) q.pop_front();
            q.push_front(i);
            for (;q.size() > 0 && !(i - a + 1 <= q.back() && q.back() <= i);) q.pop_back();
            if (i >= a - 1) matrix[i-a+1][j] = matrix[q.back()][j];
        }
    }

    // Using monotonic queue get min val for each grid [a x b]
    // Each grid can be represented by b cols
    // Each col can be represented by the min val of each col get from previous step
    // Traverse at max n*m
    ll sum = 0;
    cf(i,0,n-a) {
        q.clear();

        cf(j,0,m-1) {
            for (;q.size() > 0 && matrix[i][q.front()] >= matrix[i][j];) q.pop_front();
            q.push_front(j);
            for (;q.size() > 0 && !(j-b+1 <= q.back() && q.back() <= j);) q.pop_back();
            if (j >= b - 1) sum += matrix[i][q.back()];
        }
    }

    cout << sum << "\n";
}

/* Main() Ends Here */