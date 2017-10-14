#include <algorithm>
#include <cassert>
#include <cstdlib>

template<typename T>
struct StarrySkyTree {
  using Index0 = int;
  using value_type = T;
  struct Node {
    value_type val, add;
  };

  const int N;
  Node* const nodes;

  StarrySkyTree(int size) : StarrySkyTree(size, 1 << (32 - __builtin_clz(size - 1))) {}
  StarrySkyTree(int size, int aligned) : N(aligned), nodes((Node*)std::calloc(sizeof(Node), aligned * 2)) {
    assert(nodes != nullptr);
  }
  inline void add(value_type v, Index0 a, Index0 b) {
    add(v, a, b, 0, 0, N);
  }
  void add(value_type v, Index0 a, Index0 b, int x, Index0 l, Index0 r) {
    if (r <= a || b <= l) return;
    if (a <= l && r <= b) {
      nodes[x].add += v;
      return;
    }
    Index0 m = (l + r) >> 1;
    int lch = x + x + 1, rch = x + x + 2;
    add(v, a, b, lch, l, m);
    add(v, a, b, rch, m, r);
    nodes[x].val = std::max(nodes[lch].val + nodes[lch].add, nodes[rch].val + nodes[rch].add);
  }
  inline value_type query(Index0 a, Index0 b) const {
    return query(a, b, 0, 0, N);
  }
  value_type query(Index0 a, Index0 b, int x, Index0 l, Index0 r) const {
    if (r <= a || b <= l) return 0;
    if (a <= l && r <= b) return nodes[x].val + nodes[x].add;
    Index0 m = (l + r) >> 1;
    int lch = x + x + 1, rch = x + x + 2;
    return std::max(query(a, b, lch, l, m), query(a, b, rch, m, r)) + nodes[x].add;
  }
};
