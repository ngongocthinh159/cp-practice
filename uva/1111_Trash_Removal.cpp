/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3552
*/

#include<bits/stdc++.h>
using namespace std;

#define nline '\n'
#define ll long long

#define fastio() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
void IN_OUT() {
#ifndef ONLINE_JUDGE
freopen("Input.txt", "r", stdin);
freopen("Output.txt", "w", stdout);
#endif
}
/*--------------------------------------------------------------------------------------------------------------------------*/

const double EPS = 1e-9;
int cmp(double x, double y) {
    if (x > y + EPS) return 1;
    if (x < y - EPS) return -1;
    return 0;
}
struct Point {
    double x, y;
    Point(double _x = 0, double _y = 0) : x(_x), y(_y) {}
    
    Point operator - (const Point& q) {
        return Point(x - q.x, y - q.y);
    }
    bool operator == (const Point& q) const {
        int x_res = cmp(x, q.x);
        if (x_res != 0) return false;
        return cmp(y, q.y) == 0;
    }
    bool operator < (const Point& q) const {
        int x_res = cmp(x, q.x);
        if (x_res != 0) return x_res < 0;
        return cmp(y, q.y) < 0;
    }

    friend istream& operator >> (istream& is, Point& p) {
        is >> p.x >> p.y;
        return is;
    }
};
struct Line {
    double a, b, c;
    Point A, B;
    Line(Point _A, Point _B) : A(_A), B(_B) {
        Point AB = B - A;
        Point n(AB.y, -AB.x);
        a = n.x;
        b = n.y;
        c = -(a * A.x + b * A.y);
    }

    double distFromPoint(const Point& p) {
        return fabs(a * p.x + b * p.y + c) / sqrt(a * a + b * b);
    }
};
double cross(Point &A, Point &B) {
    return A.x * B.y - B.x * A.y;
}
int ccw(Point& A, Point& B, Point& C) {
    Point AB = B - A;
    Point AC = C - A;
    return cmp(cross(AB, AC), 0);
}
void convexHull(vector<Point> &p) {
    sort(p.begin(), p.end());
    p.erase(unique(p.begin(), p.end()), p.end());
    int n = p.size();
    vector<Point> up, down;
    for (int i = 0; i < n; i++) {
        while (up.size() >= 2 && ccw(up[up.size() - 2], up[up.size() - 1], p[i]) >= 0)
            up.pop_back();
        up.push_back(p[i]);
        while (down.size() >= 2 && ccw(down[down.size() - 2], down[down.size() - 1], p[i]) <= 0)
            down.pop_back();
        down.push_back(p[i]);
    }
    p = down;
    for (int i = (int) up.size() - 2; i > 0; i--) p.push_back(up[i]);
}

#define MAXN 105
int n;
void solve() {
    vector<Point> polygon(n);
    for (int i = 0; i < n; i++) cin >> polygon[i];
    vector<Point> hull = polygon;
    convexHull(hull);
    int m = hull.size();
    double ans = DBL_MAX;
    for (int i = 0; i < m; i++) {
        Line l(hull[i], hull[(i+1) % m]);
        double cur = DBL_MIN;
        for (int j = i + 2; j < i + 2 + (m - 2); j++) {
            cur = max(cur, l.distFromPoint(hull[j % m]));
        }
        ans = min(ans, cur);
    }
    printf("%.2f\n", ceil(ans * 100) / 100);
}

int main() {
    fastio();
    IN_OUT();
    int cnt = 1;
    while (1) {
        cin >> n;
        if (!n) break;
        printf("Case %d: ", cnt++);
        solve();
    }
    return 0;
}