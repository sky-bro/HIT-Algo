#ifndef INCLUDED_Sampler_HPP
#define INCLUDED_Sampler_HPP

#include <vector>
#include <random>
#include <unordered_set>
#include <cassert>

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
 * O(st.size())
 */
vector<int> sample_k(int k, unordered_set<int> &st) {
    vector<int> res;
    res.reserve(k);
    int i = 0, n = st.size();
    auto it = st.begin();
    for (; i < k; ++it, ++i) res.push_back(*it);
    for (; i < n; ++i, ++it) {
        int j = rand_int(0, i);
        if (j < k) res[j] = *it;
    }
    return res;
}

/**
 * O(k(1+log(n/k)))
 * get k elements from [0..N-1]
 */
vector<int> sample_k(int k, int n) {
    vector<int> res;
    res.reserve(k);
    for (int i = 0; i < k; ++i) res.push_back(i);
    double W = exp(log(rand_real(0, 1))/k);
    for (int i = k; i < n;) {
        i += floor(log(rand_real(0, 1))/log(1-W)) + 1;
        if (i < n) {
            res[rand_int(0, k-1)] = i;
            W *= exp(log(rand_real(0, 1))/k);
        }
    }
    return res;
}

/**
 * 集族 F
 * [0..N-1]
 */
vector<vector<int>> generate_subsets(int N) {
    assert(N >= 20);
    vector<vector<int>> F;
    int sz = 0;
    unordered_set<int> U; // 剩下的
    // [0..N-1]
    for (int i = 0; i < N; ++i) U.insert(i);
    unordered_set<int> C; // 已经包含的
    F.emplace_back(sample_k(20, N));
    for (int x: F[0]) {
        U.erase(x);
        C.insert(x);
    }
    ++sz;
    while (!U.empty()) {
        if (U.size() < 20) {
            F.emplace_back(U.begin(), U.end());
            ++sz;
            break;
        }
        int n = rand_int(1, 20);
        int k = rand_int(1, n); // 新元素个数
        F.emplace_back(sample_k(k, U));
        vector<int> old = sample_k(k, C);
        for (int x: F[sz]) {
            U.erase(x);
            C.insert(x);
        }
        F[sz].insert(F[sz].end(), old.begin(), old.end());
        ++sz;
    }
    while (sz != N) {
        F.push_back(sample_k(rand_int(1, 20), N));
        ++sz;
    }
    return F;
}

#endif