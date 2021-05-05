#ifndef INCLUDED_lazyselect_HPP
#define INCLUDED_lazyselect_HPP

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include "mrandom.hpp"

using namespace std;

/**
 * n = A.size()
 * k in [0..n-1]
 */
int lazyselect(const vector<int> &A, int k) {
    int n = A.size(), m = pow(n, 3./4); // size of A, R
    int x = k*pow(n, -1./4), l = max(int(x-sqrt(n)), 0), h = min(int(x+sqrt(n)), m-1);
    int loops = 0;
    while (1) {
        ++loops;
        // cout << "loop: " << ++loops << endl;
        vector<int> R = sample_k(A, m);
        sort(R.begin(), R.end());
        int L = R[l], H = R[h];
        int cnt = 0; // count number of elements that are smaller than L in A
        vector<int> P;
        for (int i = 0; i < n; ++i) {
            if (A[i] < L) ++cnt;
            else if (A[i] <= H) P.push_back(A[i]);
        }
        int sz = P.size();
        if (k >= cnt && k < cnt + sz && sz <= 4*m+1) {
            sort(P.begin(), P.end());
            return P[k-cnt];
        }
    }
}

#endif