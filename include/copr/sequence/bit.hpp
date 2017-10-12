#include <algorithm>
#include <vector>

template <typename T>
struct BIT {
  using value_type = T;
  using Index1 = int;
  std::vector<value_type> A;
  const int N, N2;
  BIT(int N) : A(N + 1, 0), N(N), N2(1 << std::__lg(N)) {}
  void add(Index1 a, value_type w) {
    for (Index1 x = a; x <= N; x += x & -x) {
      A[x] += w;
    }
  }
  value_type sum(Index1 a) const {
    value_type ret = 0;
    for (Index1 x = a; x > 0; x -= x & -x) {
      ret += A[x];
    }
    return ret;
  }
  Index1 lower_bound(value_type w) const {
    if (w <= 0) return 0;
    Index1 x = 0;
    for (int k = N2; k > 0; k >>= 1) {
      if (x + k <= N && A[x + k] < w) {
        w -= A[x + k];
        x += k;
      }
    }
    return x + 1;
  }
};
