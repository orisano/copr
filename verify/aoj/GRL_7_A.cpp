#include <copr/graph/bipartite_matching.hpp>
#include <cstdio>
#define mygc(c) (c) = getchar_unlocked()
#define mypc(c) putchar_unlocked(c)
template<typename T=int>inline T rd(){T x=0,m=0,k;for(;;){mygc(k);if(k=='-'){m=1;break;}if('0'<=k&&k<='9'){x=k-'0';break;}}for(;;){mygc(k);if(k<'0'||'9'<k)break;x=x*10+k-'0';}if(m)x=-x;return x;}
template<typename T=int>inline void wr(T x,char c='\n'){int s=0,m=0;char b[32];if(x<0)m=1,x=-x;for(;x;x/=10)b[s++]=x%10;if(!s)b[s++]=0;if(m)mypc('-');for(;s--;)mypc(b[s]+'0');mypc(c);}

int main() {
  int X = rd(), Y = rd(), E = rd();
  BipartiteMatching bm(X, Y);
  for (int i = 0; i < E; i++) {
    int x = rd(), y = rd();
    bm.add_edge(x, y);
  }
  wr(bm.max_matching());
  return 0;
}
