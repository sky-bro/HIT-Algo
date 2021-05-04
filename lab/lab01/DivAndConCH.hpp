#ifndef INCLUDED_DivAndConCH_HPP
#define INCLUDED_DivAndConCH_HPP

// #include <bits/stdc++.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include "ConvexHull.hpp"
using namespace std;

class DivAndConCH: public ConvexHull {
private:
    vector<Point<int>> _div_con(int l, int r);
public:
    DivAndConCH() {}
    DivAndConCH(const vector<Point<int>> &points): ConvexHull(points) {}
    vector<Point<int>> work();
    ~DivAndConCH() {
        // cout << "DivAndConCH destroyed\n";
    }
};

/**
 * time complexity: O(nlog(n))
 */
vector<Point<int>> DivAndConCH::work() {
    int n = P.size();
    if (n == 0) return vector<Point<int>>();
    sort(P.begin(), P.end());
    return _div_con(0, n);
}

vector<Point<int>> DivAndConCH::_div_con(int l, int r) {
    int m = r - l;
    if (m < 3) return vector<Point<int>>(P.begin()+l, P.begin()+r);
    vector<Point<int>> lCH = _div_con(l, l + m/2), rCH = _div_con(l + m/2, r);
    int lsz = lCH.size(), rsz = rCH.size();
    // merge
    int a = 0, b = 0;
    for (int i = 0; i < lsz; ++i) {
        if (lCH[a] < lCH[i]) a = i;
    }
    for (int i = 0; i < rsz; ++i) {
        if (rCH[i] < rCH[b]) b = i;
    }
    int llb = a, lrb = a, rlb = b, rrb = b;
    // 下公切线
    while (true) {
        bool changed = false;
        for (int nlrb = (lrb-1+lsz)%lsz, cs = rCH[rlb].cross(lCH[lrb], lCH[nlrb]);
            cs > 0 || (cs == 0 && rCH[rlb].dist2(lCH[lrb]) < rCH[rlb].dist2(lCH[nlrb]));
            nlrb = (lrb-1+lsz)%lsz, cs = rCH[rlb].cross(lCH[lrb], lCH[nlrb])) {
                lrb = nlrb;
                changed = true;
            }
        for (int nrlb = (rlb+1)%rsz, cs = lCH[lrb].cross(rCH[rlb], rCH[nrlb]);
            cs < 0 || (cs == 0 && lCH[lrb].dist2(rCH[rlb]) < lCH[lrb].dist2(rCH[nrlb]));
            nrlb = (rlb+1)%rsz, cs = lCH[lrb].cross(rCH[rlb], rCH[nrlb])) {
                rlb = nrlb;
                changed = true;
            }
        if (!changed) break;
    }
    // 上公切线
    while (true) {
        bool changed = false;
        for (int nllb = (llb+1)%lsz, cs = rCH[rrb].cross(lCH[llb], lCH[nllb]);
            cs < 0 || (cs == 0 && rCH[rrb].dist2(lCH[llb]) < rCH[rrb].dist2(lCH[nllb]));
            nllb = (llb+1)%lsz, cs = rCH[rrb].cross(lCH[llb], lCH[nllb])) {
                llb = nllb;
                changed = true;
            }
        for (int nrrb = (rrb-1+rsz)%rsz, cs = lCH[llb].cross(rCH[rrb], rCH[nrrb]);
            cs > 0 || (cs == 0 && lCH[llb].dist2(rCH[rrb]) < lCH[llb].dist2(rCH[nrrb]));
            nrrb = (rrb-1+rsz)%rsz, cs = lCH[llb].cross(rCH[rrb], rCH[nrrb])) {
                rrb = nrrb;
                changed = true;
            }
        if (!changed) break;
    }
    vector<Point<int>> CH;
    CH.push_back(lCH[llb]);
    while (llb != lrb) {
        llb = (llb+1)%lsz;
        CH.push_back(lCH[llb]);
    }
    CH.push_back(rCH[rlb]);
    while (rlb != rrb) {
        rlb = (rlb+1)%rsz;
        CH.push_back(rCH[rlb]);
    }
    return CH;
}

#endif
