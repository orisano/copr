#include <copr/graph/euler_tour.hpp>
#include <copr/graph/lca.hpp>

#include <cstdio>
#define mygc(c) (c) = getchar_unlocked()
#define mypc(c) putchar_unlocked(c)
template<typename T=int>inline T rd(){T x=0,m=0,k;for(;;){mygc(k);if(k=='-'){m=1;break;}if('0'<=k&&k<='9'){x=k-'0';break;}}for(;;){mygc(k);if(k<'0'||'9'<k)break;x=x*10+k-'0';}return x;}
template<typename T=int>inline void wr(T x,char c='\n'){int s=0,m=0;char b[32];if(x<0)m=1,x=-x;for(;x;x/=10)b[s++]=x%10;if(!s)b[s++]=0;if(m)mypc('-');for(;s--;)mypc(b[s]+'0');mypc(c);}

#include <utility>

int main() {
  int N = rd();
  EulerTour et(N);
  for (int i = 0; i < N; i++) {
    int k = rd();
    et.T[i].reserve(k);
    for (int j = 0; j < k; j++) {
      et.T[i].push_back(rd());
    }
  }
  et.build(0);
  LCA lca(std::move(et));

  int Q = rd();
  for (int i = 0; i < Q; i++) {
    int u = rd(), v = rd();
    wr(lca.query(u, v));
  }
  return 0;
}
