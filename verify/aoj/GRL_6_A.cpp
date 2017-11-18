#include <copr/graph/dinic.hpp>
#include <cstdio>
#define mygc(c) (c) = getchar_unlocked()
#define mypc(c) putchar_unlocked(c)
template<typename T=int>inline T rd(){T x=0,m=0,k;for(;;){mygc(k);if(k=='-'){m=1;break;}if('0'<=k&&k<='9'){x=k-'0';break;}}for(;;){mygc(k);if(k<'0'||'9'<k)break;x=x*10+k-'0';}return x;}
template<typename T=int>inline void wr(T x,char c='\n'){int s=0,m=0;char b[32];if(x<0)m=1,x=-x;for(;x;x/=10)b[s++]=x%10;if(!s)b[s++]=0;if(m)mypc('-');for(;s--;)mypc(b[s]+'0');mypc(c);}

int main() {
  int V = rd(), E = rd();
  Dinic<int> dinic(V);
  for (int i = 0; i < E; i++) {
    int u = rd(), v = rd(), c = rd();
    dinic.add_edge(u, v, c);
  }
  wr(dinic.max_flow_value(0, V - 1));
  return 0;
}
