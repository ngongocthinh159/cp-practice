/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://usaco.org/index.php?page=viewproblem2&cpid=382
*/

#include<bits/stdc++.h>
using namespace std;

#define nline '\n'
#define ll long long

#define fastio() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
void IN_OUT() {
#ifndef ONLINE_JUDGE
freopen("curling.in", "r", stdin);
freopen("curling.out", "w", stdout);
#endif
}
/*--------------------------------------------------------------------------------------------------------------------------*/

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
        int cmp_x = ::cmp(x, q.x);
        if (cmp_x != 0) 
            return cmp_x;
        return ::cmp(y, q.y);
    }

    // operator overload to compare to Point objects with >, <, >=,..
#define op(X) bool operator X (const Point& q) const { return cmp(q) X 0; };
    op(>) op(<) op(==) op(>=) op(<=) op(!=)
#undef op

    // plus/minus two vectors
#define op(X) Point operator X (const Point &q) const { return Point(x X q.x, y X q.y); };
    op(+) op(-)
#undef op

    // scale vector
#define op(X) Point operator X (double k) const { return Point(x X k, y X k); };
    op(*) op(/)
#undef op

    friend istream& operator >> (istream& is, Point& p) {
        is >> p.x >> p.y;
        return is;
    }

    friend ostream& operator << (ostream& os, Point& p) {
        os << p.x << " " << p.y;
        return os;
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

    double dist(const Point& q) const {
        return (*this - q).len();
    }

    double mandist(const Point& q) const {
        return abs(x - q.x) + abs(y - q.y);
    }
};
/**
 * ########### Line
 */
struct Line {
    double a, b, c;
    Point A, B;

    Line(double _a, double _b, double _c) : a(_a), b(_b), c(_c) {}

    Line(Point _A, Point _B) : A(_A), B(_B) {
        a = B.y - A.y;
        b = A.x - B.x;
        c = -(a * A.x + b * A.y);
    }

    Line(Point P, double k) {
        if (k == DBL_MAX) { // case line is orthogonal with x-axis (equation: x = p.x)
            a = 1;
            b = 0;
            c = -P.x;
            return;
        }
        a = -k;
        b = 1;
        c = k * P.x - P.y;
    }

    double f(const Point& P) {
        return a * P.x + b * P.y + c;
    }

    // calculate distance from a point to line if already has the line object
    double distFromPoint(const Point& p, Point &projectedPoint) const { // projectedPoint is projection of point p into current line
        double k = - (p.x * a + p.y * b + c) / (a * a + b * b);
        projectedPoint = p + Point(k * a, k * b);
        return abs(k) * sqrt(a * a + b * b);
    }
};
int ccw(Point a, Point b, Point c) {
    return cmp((b - a).cross(c - a), 0);
}

// check if point P is in segment AB
bool isInSegment(const Point& A, const Point& B, const Point& P) {
    // cout << ((A - P).norm() + (B - P).norm()) << nline;
    // cout << (A - B).norm() << nline;
    return cmp((A - P).len() - (A - B).len() + (B - P).len(), 0) == 0;
}

double triangleArea(const Point& A, const Point& B, const Point& C) {
    return fabs((B - A).cross(C - A) / 2.0);
}

// check if point P is inside the triangle ABC (include boundary)
bool isInTriangle(const Point& A, const Point& B, const Point& C, const Point& P) {
    return cmp(triangleArea(A, B, P) + triangleArea(A, C, P) + triangleArea(B, C, P) - triangleArea(A, B, C), 0) == 0;
}

// check if point P is inside the convex polygon ps
// ps must be convex before passing in
bool isInPolygon(vector<Point>& ps, const Point& P) {
    if (ps.size() == 1) return ps[0] == P;
    if (ps.size() == 2) return isInSegment(ps[0], ps[1], P);

    int n = ps.size();
    int l = 1, r = n;
    while (r - l > 1) {
        int m = l + (r - l)/2;
        int res = ccw(ps[0], ps[m], P);
        if (res == 0) {
            return isInSegment(ps[0], ps[m], P);
        }
        if (res > 0) 
            l = m;
        else
            r = m;
    }
    if (l == 0) {
        return isInSegment(ps[0], ps[1], P);
    } else if (l == n - 1) {
        return false;
    } else {
        return isInTriangle(ps[0], ps[l], ps[l + 1], P);
    }
}

void shift(vector<Point> &ps) {
    int idx = min_element(ps.begin(), ps.end()) - ps.begin();
    int m = ps.size();
    vector<Point> pp;
    for (int i = idx; i < idx + m; i++) 
        pp.push_back(ps[i % m]);
    ps = pp;
}

void convexHullMonotoneChain(vector<Point>& pts) {
    sort(pts.begin(), pts.end());
    pts.erase(unique(pts.begin(), pts.end()), pts.end());

    vector<Point> up, down;
    for (int i = 0; i < (int) pts.size(); i++) {
        while ((int) up.size() >= 2 && ccw(up[up.size() - 2], up[up.size() - 1], pts[i]) >= 0)
            up.pop_back();
        up.push_back(pts[i]);

        while ((int) down.size() >= 2 && ccw(down[down.size() - 2], down[down.size() - 1], pts[i]) <= 0)
            down.pop_back();
        down.push_back(pts[i]);
    }
    pts = down;
    for (int i = up.size() - 2; i > 0; i--)
        pts.push_back(up[i]);
}

int n;
void solve() {
    cin >> n;
    vector<Point> p1(n), p2(n);
    for (int i = 0; i < n; i++) {
        cin >> p1[i].x >> p1[i].y;
    }
    for (int i = 0; i < n; i++) {
        cin >> p2[i].x >> p2[i].y;
    }
    vector<Point> hull1 = p1;
    vector<Point> hull2 = p2;
    convexHullMonotoneChain(hull1);
    convexHullMonotoneChain(hull2);
    shift(hull1);
    shift(hull2);
    int pointA = 0, pointB = 0;
    for (int i = 0; i < n; i++) {
        // if (i != 0) continue;
        if (isInPolygon(hull1, p2[i])) pointA++;
        if (isInPolygon(hull2, p1[i])) pointB++;
    }
    cout << pointA << " " << pointB << nline;
}

int main() {
    fastio();
    IN_OUT();
    solve();
    return 0;
}