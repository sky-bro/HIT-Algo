# 实验五: 计算k位数的随机算法

* 任务就是实现找第k大元素，实现两个算法
  * 实现O(n)复杂度的select，也就是BFPRT算法: 参考 [blog](https://www.jianshu.com/p/3905983674f3), [BFPRT-simple.cpp](https://github.com/sky-bro/AC/blob/master/Algorithms/Median%20of%20medians/BFPRT-simple.cpp)
  * 实现随机算法lazyselect，能以$1 - O(n^(-1/4))$的概率在一轮中找到第k大，一轮找不到就两轮，三轮直到找到

## BFPRT

* 参考博客[中位数的中位数 - Median of Medians，选取近似的中位数作为pivot元素](https://www.jianshu.com/p/3905983674f3)
* 博客对应代码[Median of medians](https://github.com/sky-bro/AC/tree/master/Algorithms/Median%20of%20medians)

## Lazyselect

TODO
