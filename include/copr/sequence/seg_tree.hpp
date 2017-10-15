#pragma once
#include <vector>

template<typename Monoid>
struct SegTree {
  using value_type = typename Monoid::value_type;
  using Index0 = int;

  const int N;
  std::vector<value_type> nodes;

  SegTree(int size) : SegTree(size, 1 << (32 - __builtin_clz(size - 1))) {}
  SegTree(int size, int aligned) : N(aligned), nodes(aligned * 2, Monoid::empty()) {}

  template<typename F>
  void modify(int x, F f) {
    x += N;
    nodes[x] = f(nodes[x]);
    while (x > 1) {
      x >>= 1;
      nodes[x] = Monoid::append(nodes[x << 1], nodes[x << 1 | 1]);
    }
  }

  value_type query(Index0 a, Index0 b) const {
    auto x = Monoid::empty();
    for (int l = a + N, r = b + N; l < r; l >>= 1, r >>= 1) {
      if (l & 1) x = Monoid::append(x, nodes[l++]);
      if (r & 1) x = Monoid::append(x, nodes[--r]);
    }
    return x;
  }
};
