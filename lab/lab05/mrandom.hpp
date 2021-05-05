#ifndef INCLUDED_mrandom_HPP
#define INCLUDED_mrandom_HPP

#include <random>
#include <vector>

using namespace std;

random_device rd;
mt19937 g(rd());
// default_random_engine g;

/**
 * get uniformly distributed random int from [lo...hi]
 */
int rand_int(int lo, int hi) {
    uniform_int_distribution<int> distribution(lo, hi);
    return distribution(g);
}

/**
 * get uniformly distributed real number from [lo, hi)
 */
double rand_real(double lo, double hi) {
    uniform_real_distribution<double> distribution(lo, hi);
    return distribution(g);
}

/**
 * Algorithm L improves upon this algorithm by
 * computing how many items are discarded before
 * the next item enters the reservoir
 * time complexity O(k(1+log(n/k)))
 */
vector<int> sample_k(const vector<int> &S, int k) {
    vector<int> R; R.reserve(k);
    for (int i = 0; i < k; ++i) R.push_back(S[i]);
    double W = exp(log(rand_real(0, 1))/k);
    for (int i = k, n = S.size(); i < n;) {
        i += floor(log(rand_real(0, 1))/log(1-W)) + 1;
        if (i < n) {
            R[rand_int(0, k-1)] = S[i];
            W *= exp(log(rand_real(0, 1))/k);
        }
    }
    return R;
}

#endif