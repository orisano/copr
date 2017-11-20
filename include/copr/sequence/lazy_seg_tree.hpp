#pragma once
#include <vector>

template <typename Monoid, typename Op>
struct LazySegTree {
  using value_type = typename Monoid::value_type;
  using lazy_type = typename Op::value_type;
  using Index0 = int;

  const lazy_type none = Op::none();
  const int N, H;
  std::vector<value_type> nodes;
  std::vector<lazy_type> lazy;

  LazySegTree(int size) : LazySegTree(size, 32 - __builtin_clz(size - 1)) {}
  LazySegTree(int size, int h) : LazySegTree(size, h, 1 << h) {}
  LazySegTree(int size, int h, int aligned)
      : N(aligned), H(h), nodes(aligned * 2, Monoid::empty()), lazy(aligned, none) {}

  inline void apply(int p, lazy_type value, int l, int r) {
    nodes[p] = Op::eval(nodes[p], value, l, r);
    if (p < N) lazy[p] = Op::merge(lazy[p], value);
  }
  inline void calc(int p, int l, int r) {
    auto x = Monoid::append(nodes[p << 1], nodes[p << 1 | 1]);
    if (lazy[p] == none) {
      nodes[p] = x;
    } else {
      nodes[p] = Op::eval(x, lazy[p], l, r);
    }
  }
  void build(Index0 l, Index0 r) {
    int k = 1;
    int R = r;
    for (l += N, r += N - 1; l > 1;) {
      if (!(r & 1)) R += k;
      l >>= 1, r >>= 1, k <<= 1;
      for (int i = r, j = R; i >= l; --i, j -= k) calc(i, j - k, j);
    }
  }
  void push(Index0 l, Index0 r) {
    int s = H, k = 1 << (H - 1);
    int L = 0;
    for (l += N, r += N - 1; s > 0; k >>= 1) {
      for (int i = l >> s, j = L; i <= r >> s; ++i, j += k) {
        j += k;
        if (lazy[i] != none) {
          apply(i << 1, lazy[i], j - k, j);
          apply(i << 1 | 1, lazy[i], j, j + k);
          lazy[i] = none;
        }
      }
      --s;
      if ((l >> s) & 1) L += k;
    }
  }
  void exec(Index0 l, Index0 r, lazy_type value) {
    if (value == none) return;
    int L = l, R = r, k = 1;
    int i = l, j = r;
    push(L, L + 1);
    push(R - 1, R);
    for (l += N, r += N; l < r; l >>= 1, r >>= 1, k <<= 1) {
      if (l & 1) {
        apply(l++, value, i, i + k);
        i += k;
      }
      if (r & 1) {
        apply(--r, value, j - k, j);
        j -= k;
      }
    }
    build(L, L + 1);
    build(R - 1, R);
  }
  value_type query(Index0 l, Index0 r) {
    push(l, l + 1);
    push(r - 1, r);
    value_type x = Monoid::empty();
    for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
      if (l & 1) x = Monoid::append(x, nodes[l++]);
      if (r & 1) x = Monoid::append(x, nodes[--r]);
    }
    return x;
  }
};
