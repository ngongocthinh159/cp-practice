#include <bits/stdc++.h>
using namespace std;
const double eps = 0.00000009;


double findSqur(double x);
int main () {
    double x;
    cin >> x;

    cout << findSqur(x) << "\n";

    
    return 0;
}

double findSqur(double x) {
    double l = 0; 
    double r = x/2;
    double res;
    while (l <= r) {
        double m = l + (r - l) / 2;

        if (abs(m*m-x) <= eps) {
            res = m;
            break;
        }
        
        if (m*m - x < 0) {
            l = m;
        } else if (m*m - x > 0) {
            r = m;
        }
    }
    return res;
}