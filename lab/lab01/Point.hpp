#ifndef Included_Point_HPP
#define Included_Point_HPP

#include <iostream>

using namespace std;

template<class T>
struct Point {
    typedef Point P;
    T x, y;
    Point(T x=0, T y=0) : x(x), y(y) {}
    bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
    bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }
    P operator-(P p) const { return P(x-p.x, y-p.y); }
    T cross(P p) const { return x*p.y - y*p.x; }
    T cross(P a, P b) const { return (a-*this).cross(b-*this); }
    T dist2() const { return x*x + y*y; }
    T dist2(P o) const { return (o-*this).dist2(); }
    double dist() const { return sqrt((double)dist2()); }
    friend ostream& operator<<(ostream& os, P p) { return os << "(" << p.x << "," << p.y << ")"; }
};

#endif
