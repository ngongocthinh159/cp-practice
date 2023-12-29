/**
 * Solution for: https://codeforces.com/problemset/problem/1486/C1
*/

#include <bits/stdc++.h>
using namespace std;

int n;
int ask(int l, int r) {
    string query = "? " + to_string(l + 1) + " " + to_string(r + 1);
    cout << query << endl;
    int answer; cin >> answer;
    return answer - 1;
}
void solve() {
    cin >> n;
    int l = 0, r = n - 1, ans;
    while (l <= r) {
        int m = l + (r - l)/2;

        if (l == r) {ans = l; break;}
        if (r - l + 1 == 2) {
            int ans1 = ask(l, r);
            if (ans1 == l) ans = r;
            else ans = l;
            break;
        }
        int ans1 = ask(l, r);
        if (ans1 < m) {
            if (l == m - 1) {
                l = m; continue;
            }
            int ans2 = ask(l, m - 1);
            if (ans1 == ans2) {
                r = m - 1;
            } else {
                l = m;
            }
        } else {
            int ans2 = ask(m, r);
            if (ans1 == ans2) {
                l = ans1 == m ? m + 1 : m;
            } else {
                r = m - 1;
            }
        }
    }
    cout << "! " << ans + 1 << "\n";
}

int main() {
    solve();
    return 0;
}