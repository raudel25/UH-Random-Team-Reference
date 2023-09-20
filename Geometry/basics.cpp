#include <bits/stdc++.h>

using namespace std;
typedef double db;

// begin

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

    point rotate(db theta) { 
        db rad = DEG_to_RAD(theta);
        return point(x*cos(rad) - y*sin(rad), x*sin(rad) + y*cos(rad));
    }
};

struct line {
    db a, b, c;
    line() {}
    line(db _a, db _b, db _c) : a(_a), b(_b), c(_c) {}

    void pointsToLine(const point &p1, const point &p2) {
        if (fabs(p1.x-p2.x) < EPS) {
            a = 1.0;
            b = 0.0;
            c = -p1.x;
        }
        else {
            a = -(db)(p1.y-p2.y) / (p1.x-p2.x);
            b = 1.0;
            c = -(db)(a*p1.x) - p1.y;
        }
    }

    void pointSlopeToLine(point p, db m) {
        a = -m; 
        b = 1.0; 
        c = -((a * p.x) + (b * p.y)); 
    }

    bool areParallel(const line &other) {
        return (fabs(a-other.a) < EPS) && (fabs(b-other.b) < EPS);
    }

    bool areSame(const line &other) {
        return areParallel(other) && (fabs(c-other.c) < EPS);
    }

    bool areIntersect(const line &other, point &p) {
        if (areParallel(other)) return false;
        p.x = (other.b*c - b*other.c) / (other.a*b - a*other.b);
        if (fabs(b) > EPS) p.y = -(a*p.x + c);
        else p.y = -(other.a*p.x + other.c);
        return true;
    }
};

struct vec{
    db x, y;
    vec(db _x, db _y) : x(_x), y(_y) {}
    vec(const point &a, const point &b) : x(b.x - a.x), y(b.y - a.y) {}

    vec scale(db s) {
        return vec(x*s, y*s);
    }

    point translate(const point &p) {
        return point(x+p.x, y+p.y);
    }

    db dot(vec a, vec b) { return a.x*b.x + a.y*b.y; }

    db norm_sq(vec v) { return v.x*v.x + v.y*v.y; }

    db angle(const point &a, const point &o, const point &b) {
        vec oa = vec(o, a), ob = vec(o, b); 
        return acos(dot(oa, ob) / sqrt(norm_sq(oa) * norm_sq(ob)));
    }

    db cross(vec a, vec b) { return a.x*b.y - a.y*b.x; }

    bool ccw(point p, point q, point r) {
        return cross(vec(p, q), vec(p, r)) > EPS;
    }

    bool collinear(point p, point q, point r) {
        return fabs(cross(vec(p, q), vec(p, r))) < EPS;
    }

    db distToLine(point p, point a, point b) {
        vec ap = vec(a, p), ab = vec(a, b);
        db u = dot(ap, ab) / norm_sq(ab);
        point c = ab.scale(u).translate(a);
        return c.dist(p);
    }

    db distToLineSegment(point p, point a, point b) {
        vec ap = vec(a, p), ab = vec(a, b);
        db u = dot(ap, ab) / norm_sq(ab);
        if (u < 0.0) {
            point c = point(a.x, a.y);
            return c.dist(p);
        }
        if (u > 1.0) {
            point c = point(b.x, b.y);
            return c.dist(p);
        }
        return distToLine(p, a, b); 
    }
};

struct circle {
    point c;
    db r;
    circle(const point &_c, db _r) : c(_c), r(_r) {}

    int inside(const point &p) {
        db dist = c.dist(p);
        return dist < r ? 1 : (fabs(dist-r) < EPS ? 0 : -1);
    }

    point inCircle(point p1, point p2, point p3) {
        line l1, l2;
        double ratio = p1.dist(p2) / p1.dist(p3);
        point p = vec(p2, p3).scale(ratio / (1+ratio)).translate(p2);
        l1.pointsToLine(p1, p);
        ratio = p2.dist(p1) / p2.dist(p3);
        p = vec(p1, p3).scale(ratio / (1+ratio)).translate(p1);
        l2.pointsToLine(p2, p);
        point c;
        l1.areIntersect(l2, c);
        return c;
    }
};

// end