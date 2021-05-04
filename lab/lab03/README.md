# 实验三: 近似算法

* 实现了两种用于求解集合覆盖问题的近似算法：基于贪心策略和基于线性规划（舍入法）
* 测试了两种算法在三种不同规模数据下的运行时间，验证了覆盖的正确性

## Set Cover问题

* 除了参考老师的课件我还参考了[setcover-tamara](https://math.mit.edu/~goemans/18434S06/setcover-tamara.pdf) (好像是mit一个老师的课程的资料，可以直接google: setcover tamara)，这里面的将set cover问题转换为线性规划问题的例子很清晰
* 集合覆盖问题就是要求从集族`F`中挑选一些集合覆盖全集U中的所有元素，挑选的每个集合都有对应的代价（当然实验中每个集合代价都是1，所以就是使集合数量尽可能小）
* 近似算法求解来求set cover问题挑选出的集合（用`C`表示，也是集合的集合，我的代码中就是对应的F中集合的下标）不一定是最优的（代价最小），甚至不保证能覆盖所有元素（随机舍入法可能不会覆盖所有元素）

## glpk安装使用

* GNU线性规划工具集（GNU Linear Programming Kit, GLPK）是用来求解大规模之线性规划（LP）、混合整数规划（MIP），跟其他相关问题的软件包
* 官网: [GLPK (GNU Linear Programming Kit)](https://www.gnu.org/software/glpk/), 可以[下载源码](http://ftp.gnu.org/gnu/glpk/)，解压后里面doc目录中有pdf文档
* arch用户
  * 安装: `sudo pacman -Sy glpk`
  * 文档: `/usr/share/doc/glpk/glpk.pdf`
* 关于glpk的使用我主要就看了: 1 Introduction -> 1.3 Using the package -> 1.3.1 Brief example 的例子(我使用的是5.0版本 - December 2020)
* 课件上说的采用内点法求（karmarkar）线性规划问题，也可以用单纯形法(simplex)来求，实际发现后者更快。两者使用方法基本一致，参考`LPRoundingSetCover.hpp`文件中调用`glp_interior/glp_simplex`函数部分

## 程序使用说明

* `Sampler.hpp` 是用于从`[0..N-1]`这`N`个元素（所以我的全集`U`就是`[0..N-1]`）生成集族`F`，其中采用了水池抽样算法，思路和实验指导书中的一致
* `GreedySetCover.hpp` 中实现了基于贪心策略的近似算法
* `LPRoundingSetCover.hpp` 中实现了基于线性规划的近似算法，使用的是舍入法
* 使用`make`进行编译，`./main`运行
  * 程序针对两种近似算法，在三种不同大小数据集上运行
  * 记录了运行时间，并且验证了求得的`C`是否覆盖了所有元素
  * 运行输出示例
  
    ```txt
    ❯ ./main
    ----N: 100
    took: 0.001353 second(s)
    size of C: 28
    valid cover: true
    ----N: 1000
    took: 0.117102 second(s)
    size of C: 247
    valid cover: true
    ----N: 5000
    took: 3.037254 second(s)
    size of C: 1332
    valid cover: true
    ----------------------
    ----N: 100
          0: obj =   0.000000000e+00 inf =   1.000e+02 (100)
        10: obj =   8.000000000e+00 inf =   0.000e+00 (0)
    *    70: obj =   7.150618982e+00 inf =   0.000e+00 (0)
    took: 0.001229 second(s)
    size of C: 31
    valid cover: true
    ----N: 1000
          0: obj =   0.000000000e+00 inf =   1.000e+03 (1000)
        141: obj =   1.200000000e+02 inf =   0.000e+00 (0)
    *  1651: obj =   8.365233954e+01 inf =   0.000e+00 (0) 15
    took: 0.251094 second(s)
    size of C: 330
    valid cover: true
    ----N: 5000
          0: obj =   0.000000000e+00 inf =   5.000e+03 (5000)
        688: obj =   5.770000000e+02 inf =   0.000e+00 (0) 2
    *  6030: obj =   4.603771142e+02 inf =   0.000e+00 (2154) 52
    *  8478: obj =   4.374617213e+02 inf =   0.000e+00 (2247) 25
    * 10406: obj =   4.254588314e+02 inf =   0.000e+00 (2205) 19
    * 12036: obj =   4.188238957e+02 inf =   0.000e+00 (2299) 16
    * 13664: obj =   4.138036006e+02 inf =   0.000e+00 (2152) 16
    * 15358: obj =   4.105492542e+02 inf =   0.000e+00 (2034) 16
    * 17140: obj =   4.089063507e+02 inf =   0.000e+00 (1452) 18
    * 17981: obj =   4.086769912e+02 inf =   0.000e+00 (0) 8
    took: 37.794325 second(s)
    size of C: 1636
    valid cover: true
    ----------------------
    ```
