#ifndef INCLUDED_DivAndConCH2_HPP
#define INCLUDED_DivAndConCH2_HPP

// #include <bits/stdc++.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include "ConvexHull.hpp"
using namespace std;

class DivAndConCH2: public ConvexHull {
private:
    vector<Point<int>> _div_con(int l, int r);
public:
    DivAndConCH2() {}
    DivAndConCH2(const vector<Point<int>> &points): ConvexHull(points) {}
    vector<Point<int>> work();
    ~DivAndConCH2() {
        // cout << "DivAndConCH2 destroyed\n";
    }
};

/**
 * time complexity: O(nlog(n))
 */
vector<Point<int>> DivAndConCH2::work() {
    int n = P.size();
    if (n == 0) return vector<Point<int>>();
    sort(P.begin(), P.end());
    return _div_con(0, n);
}

vector<Point<int>> DivAndConCH2::_div_con(int l, int r) {
    int m = r - l;
    if (m < 3) return vector<Point<int>>(P.begin()+l, P.begin()+r);
    vector<Point<int>> lCH = _div_con(l, l + m/2), rCH = _div_con(l + m/2, r);
    int lsz = lCH.size(), rsz = rCH.size();
    // merge
    vector<Point<int>> P2;
    P2.push_back(lCH[0]);
    auto cmp = [&](const auto& a, const auto& b) {
        int c = P2[0].cross(a, b);
        return c > 0 || (c == 0 && P2[0].dist2(a) < P2[0].dist2(b));
    };
    // 寻找右边极角最大，最小的点的下标，对应rh, rl
    int rl = 0, rh = 0;
    for (int i = 1; i < rsz; ++i) {
        if (cmp(rCH[rh], rCH[i])) rh = i;
        else if (cmp(rCH[i], rCH[rl])) rl = i;
    }
    // 将三个序列的元素归并到P2，复杂度O(n)
    int i = 1, j = rl, k = (rl - 1 + rsz) % rsz;
    while (i != lsz || j != rh || k != (rh-1+rsz)%rsz) {
        int flag = 0;
        if (i == lsz || (j != rh && cmp(rCH[j], lCH[i]))) flag = 1;
        if (flag == 1) {
            if (j == rh || (k != (rh-1+rsz)%rsz && cmp(rCH[k], rCH[j]))) flag = 2;
        } else if ((k != (rh-1+rsz)%rsz && cmp(rCH[k], lCH[i]))) {
            flag = 2;
        }
        if (flag == 0) {
            P2.push_back(lCH[i++]);
        } else if (flag == 1) {
            P2.push_back(rCH[j++]);
            j %= rsz;
        } else {
            P2.push_back(rCH[k--]);
            k = (k+rsz) % rsz;
        }
    }
    // P2中的点已经按照极角排序（逆时针排序），极点为P2[0]
    // 下面复用GrahamScanCH代码，已经有序，复杂度为O(n)
    int n = P2.size();
    P2.push_back(P2[0]);
    vector<Point<int>> CH;
    m = 0;
    for (int i = 0; i <= n; ++i) {
        while (m >= 2 && CH[m-2].cross(CH[m-1], P2[i]) <= 0) {
            if (i == n && m == 2) break; // 防止所有点都共线，删除了一端端点
            CH.pop_back(), --m;
        }
        CH.push_back(P2[i]);
        ++m;
    }
    CH.pop_back();
    return CH;
}

#endif
