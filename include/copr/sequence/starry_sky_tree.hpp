#pragma once
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <limits>

template <typename IntType>
struct StarrySkyTree {
  using Index0 = int;
  using value_type = IntType;
  struct Node {
    value_type val, add;
  };

  const int N;
  Node* const nodes;

  StarrySkyTree(int size) : StarrySkyTree(size, 1 << (32 - __builtin_clz(size - 1))) {}
  StarrySkyTree(int size, int aligned)
      : N(aligned), nodes((Node*)std::calloc(sizeof(Node), aligned * 2)) {
    assert(nodes != nullptr);
  }
  void add(value_type v, Index0 a, Index0 b) {
    for (int l = a + N, r = b + N; l < r; l >>= 1, r >>= 1) {
      if (l & 1) nodes[l++].add += v;
      if (r & 1) nodes[--r].add += v;
    }
    for (int l = a + N, r = b - 1 + N; l > 1;) {
      l >>= 1;
      r >>= 1;
      nodes[l].val = std::max(eval_node(nodes[l << 1]), eval_node(nodes[l << 1 | 1]));
      if (l != r) nodes[r].val = std::max(eval_node(nodes[r << 1]), eval_node(nodes[r << 1 | 1]));
    }
  }
  value_type query(Index0 a, Index0 b) const {
    auto maxi = std::numeric_limits<value_type>::min();
    for (int l = a + N, r = b + N; l < r; l >>= 1, r >>= 1) {
      if (l & 1) maxi = std::max(maxi, eval_node(nodes[l++]));
      if (r & 1) maxi = std::max(maxi, eval_node(nodes[--r]));
    }
    return maxi;
  }

private:
  inline value_type eval_node(Node n) const { return n.val + n.add; }
};
