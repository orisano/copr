#include <copr/sequence/fft.hpp>

#include <algorithm>
#include <complex>
#include <cstdio>
#include <vector>

#define mygc(c) (c) = getchar_unlocked()
#define mypc(c) putchar_unlocked(c)
template<typename T=int>inline T rd(){T x=0,m=0,k;for(;;){mygc(k);if(k=='-'){m=1;break;}if('0'<=k&&k<='9'){x=k-'0';break;}}for(;;){mygc(k);if(k<'0'||'9'<k)break;x=x*10+k-'0';}return x;}
template<typename T=int>inline void wr(T x,char c='\n'){int s=0,m=0;char b[32];if(x<0)m=1,x=-x;for(;x;x/=10)b[s++]=x%10;if(!s)b[s++]=0;if(m)mypc('-');for(;s--;)mypc(b[s]+'0');mypc(c);}

int nextpow2(int x) { return 1 << std::__lg(2 * x - 1); }

int main() {
  int N = rd();
  int aligned = nextpow2(2 * N + 1);

  std::vector<std::complex<double>> A(aligned), B(aligned);
  for (int i = 1; i <= N; ++i) {
    A[i] = rd();
    B[i] = rd();
  }
  fft(A, +1);
  fft(B, +1);
  for (int i = 0; i < aligned; i++) A[i] = cmul(A[i], B[i]);
  fft(A, -1);
  for (int i = 1; i <= 2 * N; i++) {
    wr((int)((A[i].real() / aligned) + 0.5));
  }
  return 0;
}
