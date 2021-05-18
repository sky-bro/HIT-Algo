#include <iostream>
#include <algorithm>
#include <chrono>
#include <functional>
#include <iomanip>
#include <cassert>
#include "qsort.hpp"

using namespace std;

// std::random_device rd;
// std::mt19937 g(rd());
default_random_engine g;

void time_it(function<void()> f) {
    auto begin = std::chrono::steady_clock::now();
    f();
    auto end = std::chrono::steady_clock::now();
    cout << fixed << setprecision(6) << (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) /1000000.0 << " ";
}

int main(int argc, char const *argv[])
{
    int N = 1e5;
    if (argc > 1) N = stoi(argv[1]);
    vector<int> A0(N);
    iota(A0.begin(), A0.end(), 1);
    for (int rep = 0; rep <= N; rep += N/10) {
        auto A = A0;
        fill_n(A.begin(), rep, 1);
        shuffle(A.begin(), A.end(), g);
        auto A2 = A, A3 = A;
        // 根据指导书上的伪代码实现的qsort
        time_it(bind(qsort01, ref(A), 0, N-1));
        assert(is_sorted(A.begin(), A.end()));
        // 改进的三路划分的qsort
        time_it(bind(qsort02, ref(A2), 0, N-1));
        assert(is_sorted(A2.begin(), A2.end()));
        // C++的sort
        time_it(bind(static_cast<void(*)(std::vector<int>::iterator, std::vector<int>::iterator)>(sort),
                A3.begin(), A3.end()));
        assert(is_sorted(A3.begin(), A3.end()));
        cout << endl;
    }
    return 0;
}
