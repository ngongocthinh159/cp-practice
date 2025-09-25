/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/group/qcIqFPYhVr/contest/203881/problem/S

S. Godzilla and Pretty XOR
time limit per test
2 seconds
memory limit per test
256 megabytes

Godzilla is in love with Codezilla. Codezilla is a competitive programming fan. That's why she told Godzilla that she'll marry him if he solves the "Pretty XOR" problem.

Here is Pretty XOR problem:

We have an empty set of integers s, which is initially empty. You are given n queries. We have 2 types of queries:

1. Add number k to s (if it's already in s, do nothing).

2. If we sort all different pretty numbers in increasing order, print k - th of them.

A non-negative integer x is pretty if and only if there is a subset(possibly empty) of s(current s) with xor of elements equal to x (xor of elements of an empty set is equal to 0). For example if s =  {1, 2} then 0, 1, 2 and 3 are pretty.

Since Godzilla is not a programming fan, he asked you to help him.
Input

The first line of input contains one integer, n (1 ≤ n ≤ 106).

The next n lines contain the queries. Each line contains two integers, t and k where t is the type of query (1 ≤ t ≤ 2). If t = 1 then 1 ≤ k ≤ 109. Otherwise 1 ≤ k ≤ number of different pretty numbers.
Output

Print the answer of each query of second type in one line.

Examples
Input
6
1 10
1 3
2 1
2 2
2 3
2 4

Output
0
3
9
10

Input
14
2 1
1 1
2 1
2 2
1 2
2 1
2 2
2 3
2 4
1 3
2 1
2 2
2 3
2 4

Output
0
0
1
0
1
2
3
0
1
2
3
*/

#include<bits/stdc++.h>
using namespace std;

#define nline '\n'
#define ll long long
#define MOD 1000000007
#define MOD1 998244353
#define LINF ((long long)1e18)
#define IINF ((int)1e9)
#define MASK(i) (1LL << (i))
#define all(v) (v).begin(), (v).end()


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

#define fastio() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
void IN_OUT() {
#ifndef ONLINE_JUDGE
    freopen("Input.txt", "r", stdin);
    freopen("Output.txt", "w", stdout);
#endif
}
struct chash {static uint64_t splitmix64(uint64_t x) {x += 0x9e3779b97f4a7c15;x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;x = (x ^ (x >> 27)) * 0x94d049bb133111eb;return x ^ (x >> 31);}size_t operator()(uint64_t x) const {static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();return splitmix64(x + FIXED_RANDOM);}}; // https://codeforces.com/blog/entry/62393
struct chashp {static uint64_t splitmix64(uint64_t x) {x += 0x9e3779b97f4a7c15;x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;x = (x ^ (x >> 27)) * 0x94d049bb133111eb;return x ^ (x >> 31);}size_t operator()(pair<uint64_t,uint64_t> x) const {static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();return splitmix64(x.first + FIXED_RANDOM)^(splitmix64(x.second + FIXED_RANDOM) >> 1);}}; // https://codeforces.com/blog/entry/62393
/*--------------------------------------------------------------------------------------------------------------------------*/

#define B 30
int basis[B];
int sz;

void pre_compute() {
    
}
void solve() {
    int n; cin >> n;
    int t, k;
    for (int i = 0; i < n; i++) {
        cin >> t >> k;
        if (t == 1) {
            int mask = k;
            for (int bit = B - 1; bit >= 0; bit--) if ((mask >> bit) & 1) {
                if (!basis[bit]) {
                    basis[bit] = mask;
                    sz++;
                    break;
                }
                mask ^= basis[bit];
            }
        } else {
            int cnt = sz;
            int ans = 0;
            for (int bit = B - 1; bit >= 0; bit--) if (basis[bit]) {
                int decr = min(ans, ans ^ basis[bit]);
                int incr = max(ans, ans ^ basis[bit]);
                if (!(k <= (1 << (cnt - 1)))) {
                    ans = incr;
                    k -= (1 << (cnt - 1));
                } else
                    ans = decr;
                cnt--;
            }
            cout << ans << nline;
        }
    }
}

int main() {
    fastio();
    IN_OUT();
    int T = 1;
    // cin >> T;
    pre_compute();
    for (int cases = 1; cases <= T; cases++) {

        solve();
    }
    return 0;
}
