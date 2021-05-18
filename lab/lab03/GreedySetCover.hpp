#ifndef INCLUDED_GreedySetCover_HPP
#define INCLUDED_GreedySetCover_HPP

#include <vector>
#include <unordered_set>
using namespace std;

vector<int> greedy_set_cover(vector<vector<int>> &F, vector<int> &U) {
    int n = F.size();
    unordered_set<int> C; // 已经包含的集合，这里每个集合用它的下标表示
    unordered_set<int> Us(U.begin(), U.end()); // 还剩下的元素
    vector<int> res; // 返回集合的下标
    while (!Us.empty()) {
        int sz = 0, j = -1; // 这次新包含F[j]可以新加入sz个元素
        for (int i = 0; i < n; ++i) {
            if (C.count(i)) continue; // 已经包含了
            int cur_sz = 0;
            for (int x: F[i]) {
                if (Us.count(x)) ++cur_sz;
            }
            if (cur_sz > sz) j = i;
        }
        for (int x: F[j]) Us.erase(x);
        res.push_back(j);
        C.insert(j);
    }
    return res;
}

#endif