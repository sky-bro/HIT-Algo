#include <iostream>
#include <algorithm>
#include <functional>
#include <chrono>
#include <iomanip>
#include "Sampler.hpp"
#include "GreedySetCover.hpp"
#include "LPRoundingSetCover.hpp"
using namespace std;

vector<int> time_it(function<vector<int>()> f) {
    auto begin = std::chrono::steady_clock::now();
    auto C = f();
    auto end = std::chrono::steady_clock::now();
    cout << "took: " << fixed << setprecision(6)
         << (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) / 1e6
         << " second(s)\n";
    cout << "size of C: " << C.size() << endl;
    return C;
}

int main(int argc, char const *argv[])
{
    for (auto f: {greedy_set_cover, LP_rounding_set_cover}) {
        for (int N: {100, 1000, 5000}) {
            cout << "----N: " << N << endl;
            // [0..N-1]
            vector<vector<int>> F = generate_subsets(N);
            vector<int> U; U.reserve(N);
            for (int i = 0; i < N; ++i) U.push_back(i);
            // f(F, U);
            // time it
            // time_it(bind(f, ref(F), ref(U)));

            // check answer is correct
            vector<int> C = time_it(bind(f, ref(F), ref(U)));
            vector<bool> st(N);
            for (int i: C) {
                for (int x: F[i]) {
                    st[x] = true;
                }
            }
            cout << "valid cover: " << boolalpha
                 << all_of(st.begin(), st.end(), [](bool x){ return x; })
                 << endl;
        }
        cout << "----------------------\n";
    }
    return 0;
}
