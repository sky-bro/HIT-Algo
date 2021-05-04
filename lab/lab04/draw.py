# encoding=utf-8
import matplotlib.pyplot as plt
import numpy as np
import math

fig1 = plt.figure(1)
ax1 = fig1.add_subplot(111)
fig2 = plt.figure(2)
ax2 = fig2.add_subplot(111)
fig3 = plt.figure(3)
ax3 = fig3.add_subplot(111)
ax1.set(title='N = 10k', ylabel='time took in seconds (t)', xlabel='rep rate (%)')
ax2.set(title='N = 100k', ylabel='time took in seconds (t)', xlabel='rep rate (%)')
ax3.set(title='N = 1000k', ylabel='time took in seconds (t)', xlabel='rep rate (%)')

ys1 = [[], [], []]
with open('data10k.txt', 'r') as f:
    line = f.readline()
    while line:
        [a, b, c] = [float(x) for x in line.split()]
        ys1[0].append(a)
        ys1[1].append(b)
        ys1[2].append(c)
        line = f.readline()
x = np.linspace(0, 100, 11)
ax1.plot(x, ys1[0], label='qsort01')
ax1.plot(x, ys1[1], label='qsort02')
ax1.plot(x, ys1[2], label='std::sort')
ax1.legend()

ys2 = [[], [], []]
with open('data100k.txt', 'r') as f:
    line = f.readline()
    while line:
        [a, b, c] = [float(x) for x in line.split()]
        ys2[0].append(a)
        ys2[1].append(b)
        ys2[2].append(c)
        line = f.readline()
x = np.linspace(0, 100, 11)
ax2.plot(x, ys2[0], label='qsort01')
ax2.plot(x, ys2[1], label='qsort02')
ax2.plot(x, ys2[2], label='std::sort')
ax2.legend()

ys3 = [[], []]
with open('data1000k.txt', 'r') as f:
    line = f.readline()
    while line:
        [a, b] = [float(x) for x in line.split()]
        ys3[0].append(a)
        ys3[1].append(b)
        line = f.readline()
x = np.linspace(0, 100, 11)
ax3.plot(x, ys3[0], label='qsort02')
ax3.plot(x, ys3[1], label='std::sort')
ax3.legend()

plt.show()
