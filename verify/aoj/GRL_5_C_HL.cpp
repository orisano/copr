#include <copr/graph/hl_decomposition.hpp>
#include <cstdio>
#define mygc(c) (c) = getchar_unlocked()
#define mypc(c) putchar_unlocked(c)
// clang-format off
template<typename T=int>inline T rd(){T x=0,m=0,k;for(;;){mygc(k);if(k=='-'){m=1;break;}if('0'<=k&&k<='9'){x=k-'0';break;}}for(;;){mygc(k);if(k<'0'||'9'<k)break;x=x*10+k-'0';}if(m)x=-x;return x;}
template<typename T=int>inline void wr(T x,char c='\n'){int s=0,m=0;char b[32];if(x<0)m=1,x=-x;for(;x;x/=10)b[s++]=x%10;if(!s)b[s++]=0;if(m)mypc('-');for(;s--;)mypc(b[s]+'0');mypc(c);}
// clang-format on

int main() {
  int N = rd();
  HLDecomposition hl(N);
  for (int i = 0; i < N; i++) {
    int k = rd();
    for (int j = 0; j < k; j++) {
      hl.add_edge(i, rd());
    }
  }
  hl.build(0);
  int Q = rd();
  for (int i = 0; i < Q; i++) {
    int u = rd(), v = rd();
    wr(hl.lca(u, v));
  }
  return 0;
}
