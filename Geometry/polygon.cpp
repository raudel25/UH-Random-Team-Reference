#include <bits/stdc++.h>

using namespace std;
typedef double db;

db DEG_to_RAD(db d) { return d*M_PI / 180.0; }
db RAD_to_DEG(db r) { return r*180.0 / M_PI; }

db EPS = 1e-9;

struct point {
    db x, y;
    point() { x = y = 0.0; }
    point(db _x, db _y) : x(_x), y(_y) {}

    bool operator < (const point &other) const { 
        if (fabs(x-other.x) > EPS) 
        return x < other.x;
        return y < other.y; 
    }

    bool operator == (const point &other) const {
        return (fabs(x-other.x) < EPS) && (fabs(y-other.y) < EPS);
    }

    db dist(const point &other) { 
        return hypot(x-other.x, y-other.y);
    }
};

struct vec {
    db x, y;
    vec() {}
    vec(db _x, db _y) : x(_x), y(_y) {}
    vec(const point &a, const point &b) : x(b.x - a.x), y(b.y - a.y) {}

    db cross(vec a, vec b) { return a.x*b.y - a.y*b.x; }

    bool ccw(point p, point q, point r) {
        return cross(vec(p, q), vec(p, r)) > EPS;
    }

    db dot(vec a, vec b) { return a.x*b.x + a.y*b.y; }

    db norm_sq(vec v) { return v.x*v.x + v.y*v.y; }

    double angle(const point &a, const point &o, const point &b) {
        vec oa = vec(o, a), ob = vec(o, b); 
        return acos(dot(oa, ob) / sqrt(norm_sq(oa) * norm_sq(ob)));
    }
};

// begin

struct polygon {
    vector<point> P;
    polygon(const vector<point> &_P) : P(_P) {}

    db perimeter() {
        db ans = 0.0;
        for (int i = 0; i < (int)P.size()-1; ++i)
            ans += P[i].dist(P[i+1]);
        return ans;
    }

    db area() {
        db ans = 0.0;
        for (int i = 0; i < (int)P.size()-1; ++i)
            ans += (P[i].x*P[i+1].y - P[i+1].x*P[i].y);
        return fabs(ans) / 2.0;
    }

    bool isConvex(const vector<point> &P) {
        int n = (int)P.size();
        if (n <= 3) return false;
        bool firstTurn = vec().ccw(P[0], P[1], P[2]);
        for (int i = 1; i < n-1; ++i)
            if (vec().ccw(P[i], P[i+1], P[(i+2) == n ? 1 : i+2]) != firstTurn)
                return false;
        return true; 
    }

    int insidePolygon(point pt) {
        int n = (int)P.size();
        if (n <= 3) return -1;
        bool on_polygon = false;
        for (int i = 0; i < n-1; ++i)
            if (fabs(pt.dist(P[i]) + pt.dist(P[i+1]) - P[i].dist(P[i+1])) < EPS)
                on_polygon = true;
        if (on_polygon) return 0;
        double sum = 0.0;
        for (int i = 0; i < n-1; ++i) {
        if (vec().ccw(pt, P[i], P[i+1]))
            sum += vec().angle(P[i], pt, P[i+1]);
        else
            sum -= vec().angle(P[i], pt, P[i+1]);
        }
        return fabs(sum) > M_PI ? 1 : -1;
    }
};

// end