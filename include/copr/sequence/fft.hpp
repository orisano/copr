#pragma once

#include <algorithm>
#include <cassert>
#include <cmath>
#include <complex>
#include <vector>

template<typename T>
inline std::complex<T> cmul(const std::complex<T>& a, const std::complex<T>& b) {
  return std::complex<T>(a.real() * b.real() - a.imag() * b.imag(), a.real() * b.imag() + a.imag() * b.real());
}

template<typename T, typename C=std::complex<T>>
void fft(std::vector<std::complex<T>>& a, int sign=+1) {
  const int N = a.size();
  assert(N == (N & -N));

  const T theta = 8 * sign * std::atan(1.0) / N;
  for (int i = 0, j = 1; j < N - 1; ++j) {
    for (int k = N >> 1; k > (i ^= k); k >>= 1);
    if (j < i) std::swap(a[i], a[j]);
  }
  for (int m, mh = 1; (m = mh << 1) <= N; mh = m) {
    int irev = 0;
    for (int i = 0; i < N; i += m) {
      auto w = std::exp(C(0, theta * irev));
      for (int k = N >> 2; k > (irev ^= k); k >>= 1);
      for (int j = i; j < mh + i; ++j) {
        int k = j + mh;
        auto x = a[j] - a[k];
        a[j] += a[k];
        a[k] = cmul(w, x);
      }
    }
  }
}

