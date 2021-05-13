# encoding=utf-8
import matplotlib.pyplot as plt
import numpy as np
import math
import sys

datafile = 'data.txt'
if len(sys.argv) > 1:
       datafile = sys.argv[1]

fig = plt.figure()
ax = fig.add_subplot(121)
ax2 = fig.add_subplot(122)
ax.set(title='t - K',
       ylabel='time took in seconds (t)', xlabel='sample size (K)')

ax2.set(title='log(t) - K',
       ylabel='log(t)', xlabel='sample size (K)')

ys = [[], [], [], []]
ys2 = [[], [], [], []]
with open(datafile, 'r') as f:
    line = f.readline()
    lo = int(line.split()[0])
    while line:
        [k, a, b, c, d] = [float(x) for x in line.split()]
        hi = k
        ys2[0].append(math.log(max(a, 1e-6))) # 防止时间为0
        ys2[1].append(math.log(max(b, 1e-6)))
        ys2[2].append(math.log(max(c, 1e-6)))
        ys2[3].append(math.log(max(d, 1e-6)))
        ys[0].append(a)
        ys[1].append(b)
        ys[2].append(c)
        ys[3].append(d)
        line = f.readline()
sz = len(ys[0])
x = np.linspace(lo, hi, sz)
# y1 = x/100

ax.plot(x, ys[0], label='BruteForceCH')
ax.plot(x, ys[1], label='GrahamScanCH')
ax.plot(x, ys[2], label='DivAndConCH')
ax.plot(x, ys[3], label='DivAndConCH2')
ax.legend()
ax2.plot(x, ys2[0], label='BruteForceCH')
ax2.plot(x, ys2[1], label='GrahamScanCH')
ax2.plot(x, ys2[2], label='DivAndConCH')
ax2.plot(x, ys2[3], label='DivAndConCH2')
ax2.legend()
plt.show()
