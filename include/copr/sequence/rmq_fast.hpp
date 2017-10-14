#ifndef INCLUDE_RMQ_HPP
#define INCLUDE_RMQ_HPP
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <vector>

template <typename T>
struct RMQ {
  using Index = int;
  using BitIndex = int;

  const std::vector<T>& A;
  const int N, S, L, LG_L;

  std::vector<int> lg;
  BitIndex* const small;
  Index* const large;

  bool f(Index a, Index b) const {
    if (A[a] != A[b]) return A[a] < A[b];
    return a < b;
  }
  RMQ(const std::vector<T>& A) : RMQ(A, A.size()) {}
  Index query(Index l, Index r) const {
    const int a = l / S, b = r / S;
    if (a == b) return query_small(l, r);

    Index ans = F(query_small(l, a * S + (S - 1)), query_small(b * S, r));
    if (a + 1 <= b - 1) ans = F(ans, query_large(a + 1, b - 1));
    return ans;
  }
  ~RMQ() {
    std::free(small);
    std::free(large);
  }
private:
  inline Index F(Index a, Index b) const { return f(a, b) ? a : b; }

  RMQ(const std::vector<T>& A, int N) : RMQ(A, N, std::__lg(N) + 1) {}
  RMQ(const std::vector<T>& A, int N, int S) : RMQ(A, N, S, (N + S - 1) / S) {}
  RMQ(const std::vector<T>& A, int N, int S, int L) : RMQ(A, N, S, L, std::__lg(L) + 1) {}
  RMQ(const std::vector<T>& A, int N, int S, int L, int LG_L)
      : A(A), N(N), S(S), L(L), LG_L(LG_L), lg(1 << S), small((BitIndex*)std::malloc(N * sizeof(BitIndex))), large((Index*)std::malloc(L * LG_L * sizeof(Index))) {
    assert(small != nullptr);
    assert(large != nullptr);
    for (int i = 1, sz = lg.size(); i < sz; i++) {
      lg[i] = std::__lg(i);
    }
    for (int li = 0; li < L; li++) {
      int i = li * S;
      large[li * LG_L + 0] = i;
      for (int si = 0; si < S && i + si < N; si++) {
        large[li * LG_L + 0] = F(large[li * LG_L + 0], i + si);
      }
    }
    for (int x = 0; x < LG_L - 1; x++) {
      for (int li = 0; li + (1 << x) < L; li++) {
        large[li * LG_L + x + 1] = F(large[li * LG_L + x], large[(li + (1 << x)) * LG_L + x]);
      }
    }
    Index st[32];
    for (int li = 0; li < L; li++) {
      int i = li * S;
      int sti = 0;
      for (int si = 0; si < S && i + si < N; si++) {
        while (sti > 0 && f(i + si, st[sti - 1])) --sti;
        small[i + si] |= 1 << si;
        if (sti > 0) small[i + si] |= small[st[sti - 1]];
        st[sti] = i + si;
        ++sti;
      }
    }
  }
  inline int ntz(int x) const { return lg[x & -x]; }
  inline int bitmask(int l, int r) const { return ((1 << (r - l + 1)) - 1) << l; }
  inline Index query_small(Index l, Index r) const { return (l - l % S) + ntz(small[r] & bitmask(l % S, r % S)); }
  inline Index query_large(Index l, Index r) const {
    int x = lg[r - l + 1];
    return F(large[l * LG_L + x], large[(r - (1 << x) + 1) * LG_L + x]);
  }
};
#endif
