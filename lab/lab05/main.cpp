#include <iostream>
#include <functional>
#include <chrono>
#include <iomanip>
#include <cassert>
#include "BFPRT.hpp"
#include "lazyselect.hpp"
#include "mrandom.hpp"

using namespace std;

double time_it(function<int()> f, int ans) {
    auto begin = std::chrono::steady_clock::now();
    int ret = f();
    auto end = std::chrono::steady_clock::now();
    // cout << fixed << setprecision(6) << (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) /1000000.0 << " ";
    assert(ret == ans); // make sure selection algo is correct
    double t = (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) / 1e6;
    return t;
}

int main(int argc, char const *argv[])
{
    for (int N: {1000, 2000, 5000, 10000, 20000, 50000, 100000}) {
        vector<int> A(N);
        int k = N/2;
        iota(A.begin(), A.end(), 1);
        int ans = A[k];
        shuffle(A.begin(), A.end(), g);
        int loops = 1e3;
        double t1 = 0, t2 = 0;
        for (int i = 0; i < loops; ++i) {
            vector<int> B = A;
            t1 += time_it(bind(lazyselect, ref(B), k), ans); // will not change B
            t2 += time_it(bind(pick, ref(B), 0, N-1, k), ans); // will change B
        }
        t1 /= loops;
        t2 /= loops;
        cout << "(N=" << N << ")\tlazyselect:\t" << t1 << endl;
        cout << "(N=" << N << ")\tBFPRT     :\t" << t2 << endl;
    }
    return 0;
}
