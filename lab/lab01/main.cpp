#include <iostream>
#include <chrono>
#include <functional>
#include <iomanip>
#include "PointsSampler.hpp"
#include "ConvexHull.hpp"
#include "BruteForceCH.hpp"
#include "GrahamScanCH.hpp"
#include "DivAndConCH.hpp"
using namespace std;

template <typename T>
void printArr(const vector<T> &arr) {
    for (const T &t : arr) cout << t << " ";
    cout << endl;
}

void time_it(function<void()> f) {
    auto begin = std::chrono::steady_clock::now();
    f();
    auto end = std::chrono::steady_clock::now();
    cout << fixed << setprecision(6)
         << (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) / 1e6
         << " ";
}

int main(int argc, char const *argv[]) {
    vector<unique_ptr<ConvexHull>> CHs;
    CHs.emplace_back(make_unique<BruteForceCH>());
    CHs.emplace_back(make_unique<GrahamScanCH>());
    CHs.emplace_back(make_unique<DivAndConCH>());
    int step = 10, k0 = 0, k1 = 10000;
    // int step = 1, k0 = 1, k1 = 1000;
    for (int k = k0; k <= k1; k += step) {
        vector<Point<int>> P = PointsSampler::sample_k(k);
        // cout << "sample size: " << k << endl;
        // printArr(P);
        cout << P.size() << " ";
        for (auto& ch: CHs) {
            ch->upadte(P);
            time_it(bind(&ConvexHull::work, ref(*ch)));
        }
        cout << endl;
    }
    return 0;
}
