#ifndef INCLUDED_GrahamScanCH_HPP
#define INCLUDED_GrahamScanCH_HPP

// #include <bits/stdc++.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include "ConvexHull.hpp"
using namespace std;

class GrahamScanCH: public ConvexHull {
public:
    GrahamScanCH() {}
    GrahamScanCH(const vector<Point<int>> &points): ConvexHull(points) {}
    vector<Point<int>> work();
    ~GrahamScanCH() {
        // cout << "GrahamScanCH destroyed\n";
    }
};

/**
 * time complexity: O(nlog(n))
 */
vector<Point<int>> GrahamScanCH::work() {
    int n = P.size();
    if (n == 0) return vector<Point<int>>();
    swap(P[0], *min_element(P.begin(), P.end())); // 极点放到P[0]处
    if (n <= 2) return P;
    // 按照极角排序，极点为P[0]
    sort(P.begin()+1, P.end(), [&](const auto& a, const auto& b) {
        int c = P[0].cross(a, b);
        return c > 0 || (c == 0 && P[0].dist2(a) < P[0].dist2(b));
    });
    // GrahamScan
    P.push_back(P[0]); // 处理最后一个点更简单
    vector<Point<int>> CH;
    int m = 0;
    for (int i = 0; i <= n; ++i) {
        while (m >= 2 && CH[m-2].cross(CH[m-1], P[i]) <= 0) {
            if (i == n && m == 2) break; // 防止所有点都共线，删除了一端端点
            CH.pop_back(), --m;
        }
        CH.push_back(P[i]);
        ++m;
    }
    CH.pop_back();
    return CH;
}

#endif
