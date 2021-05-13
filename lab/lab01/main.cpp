#include <iostream>
#include <chrono>
#include <functional>
#include <iomanip>
#include "PointsSampler.hpp"
#include "ConvexHull.hpp"
#include "BruteForceCH.hpp"
#include "GrahamScanCH.hpp"
#include "DivAndConCH.hpp"
#include "DivAndConCH2.hpp"
using namespace std;

template <typename T>
void printArr(const vector<T> &arr) {
    for (const T &t : arr) cout << t << " ";
    cout << endl;
}

vector<Point<int>> time_it(function<vector<Point<int>>()> f) {
    auto begin = std::chrono::steady_clock::now();
    auto res = f();
    auto end = std::chrono::steady_clock::now();
    cout << fixed << setprecision(6)
         << (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) / 1e6
         << " ";
    return res;
}

int main(int argc, char const *argv[]) {
    vector<unique_ptr<ConvexHull>> CHs;
    CHs.emplace_back(make_unique<BruteForceCH>());
    CHs.emplace_back(make_unique<GrahamScanCH>());
    CHs.emplace_back(make_unique<DivAndConCH>());
    CHs.emplace_back(make_unique<DivAndConCH2>());
    int step = 10, k0 = 0, k1 = 10000;
    // int step = 1, k0 = 0, k1 = 1000;
    for (int k = k0; k <= k1; k += step) {
        vector<Point<int>> P = PointsSampler::sample_k(k);
        // P = {{29,45}, {75,8}, {32,50}, {78,78}, {24,26}};
        // cout << "sample size: " << k << endl;
        // printArr(P);
        cout << P.size() << " ";
        bool flag = false;
        size_t pre = 0;
        for (auto& ch: CHs) {
            ch->upadte(P);
            auto res = time_it(bind(&ConvexHull::work, ref(*ch)));
            // printArr(res);
            if (flag) {
                if (res.size() != pre) {
                    printArr(res);
                    printArr(P);
                    return -1; // 发现求得凸包大小不同，算法实现有误
                }
            }
            pre = res.size();
            flag = true;
        }
        cout << endl;
    }
    return 0;
}
