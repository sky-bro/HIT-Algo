#ifndef INCLUDED_ConvexHull_HPP
#define INCLUDED_ConvexHull_HPP

#include "Point.hpp"
using namespace std;

class ConvexHull {
protected:
    vector<Point<int>> P;

public:
    ConvexHull() {}
    ConvexHull(const vector<Point<int>> &points): P(points) {}
    virtual vector<Point<int>> work() = 0;
    void upadte(const vector<Point<int>> &points) { P = points; }
    virtual ~ConvexHull() {};
};

#endif
