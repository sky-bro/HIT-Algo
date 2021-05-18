# 实验五: 计算k位数的随机算法

* 任务就是实现找第k大元素，实现两个算法
  * 实现O(n)复杂度的select，也就是BFPRT算法: 参考 [blog](https://www.jianshu.com/p/3905983674f3), [BFPRT-simple.cpp](https://github.com/sky-bro/AC/blob/master/Algorithms/Median%20of%20medians/BFPRT-simple.cpp)
  * 实现随机算法lazyselect，能以$1 - O(n^{-1/4})$的概率在一轮中找到第k大，一轮找不到就两轮，三轮直到找到

## BFPRT

* 参考博客[中位数的中位数 - Median of Medians，选取近似的中位数作为pivot元素](https://www.jianshu.com/p/3905983674f3)
* 博客对应代码[Median of medians](https://github.com/sky-bro/AC/tree/master/Algorithms/Median%20of%20medians)

## Lazyselect

* 默认的采样比例n^(3/4)已实现
* 其它采样比例的对比未实现 TODO
* refs
  * https://people.cs.umass.edu/~mcgregor/711S09/lec04.pdf
  * https://www2.cs.sfu.ca/CourseCentral/405/petra/Current/random2-4up.pdf

## 对比两种k位数算法

采用不同大小的随机序列进行测试，每个序列运行1000次取运行时间的平均值，结果如下

```txt
(N=1000)        lazyselect:     0.000148354
(N=1000)        BFPRT     :     0.000172629
(N=2000)        lazyselect:     0.000245446
(N=2000)        BFPRT     :     0.000349101
(N=5000)        lazyselect:     0.000543804
(N=5000)        BFPRT     :     0.000897497
(N=10000)       lazyselect:     0.000987361
(N=10000)       BFPRT     :     0.00176972
(N=20000)       lazyselect:     0.00178929
(N=20000)       BFPRT     :     0.00353356
(N=50000)       lazyselect:     0.0039252
(N=50000)       BFPRT     :     0.009168
(N=100000)      lazyselect:     0.0070601
(N=100000)      BFPRT     :     0.018703
```

可以看出二者运行时间均随N的增大而线性增加，BFPRT略慢于lazyselect，主要是因为BFPRT的常数项比较大，而lazyselect有可能一轮就找到正确答案。

## 随机算法参数分析

TODO 暂未实现