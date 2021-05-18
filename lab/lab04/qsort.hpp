#ifndef INCLUDED_qsort01_HPP
#define INCLUDED_qsort02_HPP

// #include <iostream>
#include <vector>
#include <random>

using namespace std;

default_random_engine generator;

/**
 * get uniformly distributed random int from [lo...hi]
 */
int rand_int(int lo, int hi) {
    uniform_int_distribution<int> distribution(lo, hi);
    return distribution(generator);
}

void qsort01(vector<int>& A, int l, int r) {
    if (l >= r) return;
    int i = rand_int(l, r);
    swap(A[r], A[i]);
    i = l - 1;
    for (int j = l; j < r; ++j) {
        if (A[j] <= A[r]) swap(A[++i], A[j]);
    }
    swap(A[++i], A[r]);
    qsort01(A, l, i - 1);
    qsort01(A, i + 1, r);
}

/**
 * use three way partition
 * T(n) = 2T(n/2) + n
*/
void qsort02(vector<int>& A, int l, int r) {
    if (l >= r) return;
    int i = rand_int(l, r);
    int x = A[i], lo = l, hi = r;
    i = l;
    while (i <= hi) {
        if (A[i] == x) ++i;
        else if (A[i] < x) swap(A[i++], A[lo++]);
        else swap(A[i], A[hi--]);
    }
    // ----[x]xx[x]++++
    //     lo   hi
    qsort02(A, l, lo - 1);
    qsort02(A, hi + 1, r);
}

#endif