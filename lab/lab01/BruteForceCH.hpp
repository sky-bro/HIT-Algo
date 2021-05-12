#ifndef INCLUDED_BruteForceCH_HPP
#define INCLUDED_BruteForceCH_HPP

#include <algorithm>
#include <vector>
#include "ConvexHull.hpp"
using namespace std;

class BruteForceCH: public ConvexHull {
public:
    BruteForceCH() {}
    BruteForceCH(const vector<Point<int>> &points): ConvexHull(points) {}
    vector<Point<int>> work();
    ~BruteForceCH() {
        // cout << "BruteForceCH destroyed\n";
    }
};

/**
 * time complexity: O(n^4+nlog(n))
 */
vector<Point<int>> BruteForceCH::work() {
    int n = P.size();
    if (n == 0) return vector<Point<int>>();
    for (int a = 0; a < n; ++a) {
        if (P[a].x < 0) continue; // Point::x < 0 -> point deleted
        for (int b = 0; b < n; ++b) {
            if (P[a].x < 0) break; // important
            if (b == a || P[b].x < 0) continue;
            for (int c = 0; c < n; ++c) {
                if (P[b].x < 0 || P[a].x < 0) break; // important
                if (c == a || c == b || P[c].x < 0) continue;
                // check if abc on same line, if so, delete the middle point
                if (P[a].cross(P[b], P[c]) == 0) {
                    int i = a, j = b, k = c;
                    if (P[j] < P[i]) swap(i, j);
                    if (P[j] < P[k]) P[j].x = -1;
                    else if (P[i] < P[k]) P[k].x = -1;
                    else P[i].x = -1;
                    continue;
                }
                for (int d = 0; d < n; ++d) {
                    if (d == a || d == b || d == c || P[d].x < 0) continue;
                    if (P[a].cross(P[b], P[c])*P[a].cross(P[b], P[d]) >= 0
                     && P[a].cross(P[c], P[b])*P[a].cross(P[c], P[d]) >= 0
                     && P[b].cross(P[c], P[a])*P[b].cross(P[c], P[d]) >= 0
                    ) {
                        P[d].x = -1; // delete
                    }
                }
            }
        }
    }
    // A, B, left most & right most
    int m = 1, i = 0;
    while (P[i].x < 0) ++i;
    int a = i, b = i;
    for (++i; i < n; ++i) {
        if (P[i].x < 0) continue;
        ++m;
        if (P[i] < P[a]) a = i;
        if (P[b] < P[i]) b = i;
    }
    vector<Point<int>> CH(m), S_U(m);
    CH[0] = P[a]; // A
    int il = 1, iu = 0;
    // S_L, S_U
    for (int i = 0; i < n; ++i) {
        if (P[i].x < 0 || i == a || i == b) continue;
        if (P[a].cross(P[b], P[i]) < 0) { // < 0, S_L
            CH[il++] = P[i];
        } else { // > 0, S_U
            S_U[iu++] = P[i];
        }
    }
    // A, S_L, B, reverse(S_U)
    sort(CH.begin() + 1, CH.begin() + il); // S_L
    sort(S_U.begin(), S_U.begin() + iu);
    CH[il] = P[b]; // B
    for (int i = 0; i < iu; ++i) CH[il+1+i] = S_U[iu-1-i]; // reverse(S_U)
    return CH;
}

#endif
