#ifndef INCLUDED_LPRoundingSetCover_HPP
#define INCLUDED_LPRoundingSetCover_HPP

#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include "glpk.h"
using namespace std;

vector<int> LP_rounding_set_cover(vector<vector<int>> &F, vector<int> &U) {
    int n = F.size(); // x个数
    int m = U.size(); // 约束不等式个数
    unordered_map<int, int> x2i;
    for (int i = 0; i < m; ++i) x2i.emplace(U[i], i); // 每个元素对应的下标（对应了m个不等式约束）
    glp_prob *lp = glp_create_prob();
    glp_set_obj_dir(lp, GLP_MIN); // 最小化目标（设置优化方向）
    glp_add_rows(lp, m); // 不等式个数
    for (int i = 1; i <= m; ++i) glp_set_row_bnds(lp, i, GLP_LO, 1., 0.); // 都是 >= 1
    glp_add_cols(lp, n); // 变量x个数
    for (int i = 1; i <= n; ++i) {
        glp_set_col_bnds(lp, i, GLP_LO, 0., 0.); // x的约束都是 >= 0
        glp_set_obj_coef(lp, i, 1.); // 目标函数中的x的系数，都是1
    }
    // f是最高的元素频率
    int sz = 0;
    vector<int> freq(m);
    for (auto &S: F) {
        sz += S.size();
        for (int x: S) ++freq[x2i[x]];
    }
    int f = *max_element(freq.begin(), freq.end());
    int *ia = new int[sz+1];
    int *ja = new int[sz+1];
    double *ar = new double[sz+1];
    int idx = 1;
    for (int i = 0; i < n; ++i) {
        for (int x: F[i]) {
            ia[idx] = x2i[x] + 1;
            ja[idx] = i + 1;
            ar[idx] = 1.;
            ++idx;
        }
    }
    glp_load_matrix(lp, sz, ia, ja, ar);
    // glp_write_mps，glp_read_mps也可以写读lp问题，但这里对于现生成的数据不用了
    // lp问题初始化完毕，开始求解
    glp_smcp smcp;
    glp_init_smcp(&smcp);
    // 默认GLP_MSG_ALL: full output (including informational messages).
    smcp.msg_lev = GLP_MSG_ERR; // error and warning messages only; 
    smcp.msg_lev = GLP_MSG_ON; // error and warning messages only; 
    // smcp.presolve = GLP_ON;
    glp_simplex(lp, &smcp);
    // glp_iptcp iptcp;
    // iptcp.msg_lev = GLP_MSG_ERR;
    // glp_interior(lp, &iptcp);

    // glp_simplex(lp, nullptr); // 单纯形法求，发现更快
    // glp_interior(lp, nullptr); // 内点法求（karmarkar）

    // 舍入法选择保留的集合
    vector<int> res; // 返回集合的下标
    for (int i = 0; i < n; ++i) {
        if (1./f <= glp_get_col_prim(lp, i+1)) res.push_back(i);
        // cout << "x" << i << ": " << glp_get_col_prim(lp, i) << " ";
    }
    // cout << endl;
    delete [] ia;
    delete [] ja;
    delete [] ar;
    glp_delete_prob(lp);
    return res;
}

#endif