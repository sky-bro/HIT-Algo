#ifndef INCLUDED_BFPRT_HPP
#define INCLUDED_BFPRT_HPP

#include <vector>

using namespace std;

int pick(vector<int> &L, int l, int r, int k) {
  if (l == r) return L[l];

  // get median of medians
  for (int i = l; i <= r; i += 5) {
    int j = min(r, i + 5);
    for (int ii = i + 1; ii <= j; ++ii) {
      for (; ii > i && L[ii - 1] > L[ii]; --ii) swap(L[ii], L[ii - 1]);
    }
    swap(L[l + (i - l) / 5], L[(i + j) / 2]);
  }
  int nr = l + (r - l) / 5;
  int median = pick(L, l, nr, (nr + l) / 2);

  // three way partition with the approximate median
  // ---[=]=[=]+++
  //    low high
  int i = l, low = l, high = r;
  while (i <= high) {
    if (L[i] == median)
      ++i;
    else if (L[i] < median)
      swap(L[i++], L[low++]);
    else
      swap(L[i], L[high--]);
  }

  if (k < low) {
    return pick(L, l, low - 1, k);
  } else if (k <= high) {
    return L[k];
  } else {
    return pick(L, high + 1, r, k);
  }
}

#endif