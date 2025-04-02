/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://codeforces.com/problemset/problem/1032/D
 */

#include <bits/stdc++.h>
using namespace std;

#define fastio()                      \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL)
void IN_OUT() {
#ifndef ONLINE_JUDGE
    freopen("Input.txt", "r", stdin);
    freopen("Output.txt", "w", stdout);
#endif
}
/*--------------------------------------------------------------------------------------------------------------------------*/
const double EPS = 1e-9;
int cmp_eps(double x, double y) {
    if (x < y - EPS) return -1;
    if (x > y + EPS) return 1;
    return 0;
}
struct Point {
    double x, y;
    Point() { x = 0, y = 0; }
    Point(double _x, double _y) : x(_x), y(_y) {}

    int cmp(const Point &q) const {
        int res_x = ::cmp_eps(x, q.x);
        if (res_x != 0) return res_x;
        return ::cmp_eps(y, q.y);
    }

    double norm() {
        return x * x + y * y;
    }

    double len() {
        return sqrt(norm());
    }

#define op(X) bool operator X(const Point &q) const { return cmp(q) X 0; };
    op(>) op(<) op(>=) op(<=) op(==) op(!=)
#undef op

#define op(X) Point operator X(const Point &q) const { return Point(x X q.x, y X q.y); };
    op(+) op(-)
#undef op

#define op(X) Point operator X(double k) const { return Point(x X k, y X k); };
    op(*) op(/)
#undef op
};
struct Line {
    double a, b, c;
    Point A, B;
    Line(double _a, double _b, double _c) : a(_a), b(_b), c(_c) {}
    Line(Point _A, Point _B) : A(_A), B(_B) {
        Point u = (A - B);
        a = u.y;
        b = -u.x;
        c = (-a * A.x - b * A.y);
    }
    Line(Point p, double k) {
        if (k == DBL_MAX) {
            a = 1;
            b = 0;
            c = - (a * p.x + b * p.y);
            return;
        }
        a = -k;
        b = 1;
        c = -(a * p.x + b * p.y);
    }
};
bool areParallel(Line l1, Line l2) {
    return cmp_eps(l1.a * l2.b, l2.a * l1.b) == 0;
}
bool intersect(Line l1, Line l2, vector<Point> &res) {
    if (areParallel(l1, l2))
        return false;
    
    double d = l1.a * l2.b - l2.a * l1.b;
    double dx = l1.b * l2.c - l2.b * l1.c;
    double dy = l1.c * l2.a - l2.c * l1.a;
    res.push_back(Point(dx / d, dy / d));
    return true;
}
double a, b, c, xa, ya, xb, yb;

void find_cut(Point p, Line l, vector<Point> &res) {
    vector<Point> tmp;
    Line ax(p, 0);
    if (intersect(ax, l, tmp)) {
        for (auto p : tmp) res.push_back(p);
    }
    tmp.clear();

    Line ay(p, DBL_MAX);
    if (intersect(ay, l, tmp))
        for (auto p : tmp) res.push_back(p);
    tmp.clear();
}
void solve() {
    cin >> a >> b >> c >> xa >> ya >> xb >> yb;
    Line l(a, b, c);
    vector<Point> can_a, can_b;
    Point A(xa, ya), B(xb, yb);
    find_cut(A, l, can_a);
    find_cut(B, l, can_b);
    double res = fabs(xa - xb) + fabs(ya - yb);
    for (auto cut_a : can_a) {
        for (auto cut_b : can_b) {
            res = min(res, (A - cut_a).len() + (cut_a - cut_b).len() + (B - cut_b).len());        
        }
    }
    printf("%.12f\n", res);
}

int main() {
    fastio();
    IN_OUT();
    solve();
    return 0;
}