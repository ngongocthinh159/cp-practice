/*
    Solution for: https://codeforces.com/problemset/problem/679/A
*/

#include <bits/stdc++.h>
using namespace std;
#define ll long long
bool prime(ll a) { if (a==1) return 0; for (int i=2;i<=round(sqrt(a));++i) if (a%i==0) return 0; return 1; }

int a[] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,4,9,25,49};
void solve() {
    int cnt = 0;
    for (int num : a) {
        cout << num << endl;
        string s; cin >> s;
        if (s == "yes") {
            cnt++;
            if (cnt > 1) cout << "composite\n";
        }
    }
    cout << "prime\n";
}

/* Main()  function */
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    solve();
}