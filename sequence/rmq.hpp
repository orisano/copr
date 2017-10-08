#include <algorithm>
#include <vector>

template <typename T>
struct RMQ {
  using Index = int;
  using BitIndex = int;

  const std::vector<T>& A;
  const int N, S, L;

  std::vector<int> lg;
  std::vector<BitIndex> small;
  std::vector<std::vector<Index>> large;

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

private:
  Index F(Index a, Index b) const { return f(a, b) ? a : b; }

  RMQ(const std::vector<T>& A, int N) : RMQ(A, N, std::__lg(N) + 1) {}
  RMQ(const std::vector<T>& A, int N, int S) : RMQ(A, N, S, (N + S - 1) / S) {}
  RMQ(const std::vector<T>& A, int N, int S, int L) : RMQ(A, N, S, L, std::__lg(L) + 1) {}
  RMQ(const std::vector<T>& A, int N, int S, int L, int LG_L)
      : A(A), N(N), S(S), L(L), lg(1 << S), small(N), large(L, std::vector<Index>(LG_L)) {
    for (int i = 1, sz = lg.size(); i < sz; i++) {
      lg[i] = std::__lg(i);
    }
    for (int li = 0; li < L; li++) {
      int i = li * S;
      large[li][0] = i;
      for (int si = 0; si < S && i + si < N; si++) {
        large[li][0] = F(large[li][0], i + si);
      }
    }
    for (int x = 0; x < LG_L - 1; x++) {
      for (int li = 0; li + (1 << x) < L; li++) {
        large[li][x + 1] = F(large[li][x], large[li + (1 << x)][x]);
      }
    }
    std::vector<Index> st;
    for (int li = 0; li < L; li++) {
      int i = li * S;
      st.clear();
      for (int si = 0; si < S && i + si < N; si++) {
        while (!st.empty() && f(i + si, st.back())) st.pop_back();
        small[i + si] |= 1 << si;
        if (!st.empty()) small[i + si] |= small[st.back()];
        st.push_back(i + si);
      }
    }
  }
  int ntz(int x) const { return lg[x & -x]; }
  int bitmask(int l, int r) const { return ((1 << (r - l + 1)) - 1) << l; }
  Index query_small(Index l, Index r) const { return (l - l % S) + ntz(small[r] & bitmask(l % S, r % S)); }
  Index query_large(Index l, Index r) const {
    int x = lg[r - l + 1];
    return F(large[l][x], large[r - (1 << x) + 1][x]);
  }
};
