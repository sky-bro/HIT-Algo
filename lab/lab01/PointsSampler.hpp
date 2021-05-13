#ifndef INCLUDED_PointsSampler_HPP
#define INCLUDED_PointsSampler_HPP

#include <random>
#include <vector>
#include <cassert>
#include "Point.hpp"
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

class PointsSampler
{
public:
    const static int R = 101, C = 101, N = R * C;
    /**
     * Reservoir Sampling, time complexity O(k(1+log(n/k)))
     */
    static vector<Point<int>> sample_k(int k) {
        assert(k >= 0 && k <= N);
        vector<Point<int>> res;
        if (k == 0) return res;
        res.reserve(k);
        for (int i = 0; i < k; ++i) res.emplace_back(i/C, i%C);
        double W = exp(log(rand_real(0, 1))/k);
        for (int i = k; i < N;) {
            i += floor(log(rand_real(0, 1))/log(1-W)) + 1;
            if (i < N) {
                int idx = rand_int(0, k-1);
                res[idx].x = i/C;
                res[idx].y = i%C;
                W *= exp(log(rand_real(0, 1))/k);
            }
        }
        return res;
    }
};

#endif
