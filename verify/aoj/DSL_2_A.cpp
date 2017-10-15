#include <copr/sequence/seg_tree.hpp>

#include <cstdio>
#include <limits>
#define mygc(c) (c) = getchar_unlocked()
#define mypc(c) putchar_unlocked(c)
template<typename T=int>inline T rd(){T x=0,m=0,k;for(;;){mygc(k);if(k=='-'){m=1;break;}if('0'<=k&&k<='9'){x=k-'0';break;}}for(;;){mygc(k);if(k<'0'||'9'<k)break;x=x*10+k-'0';}return x;}
template<typename T=int>inline void wr(T x,char c='\n'){int s=0,m=0;char b[32];if(x<0)m=1,x=-x;for(;x;x/=10)b[s++]=x%10;if(!s)b[s++]=0;if(m)mypc('-');for(;s--;)mypc(b[s]+'0');mypc(c);}

struct Min {
  using value_type = int;
  static const int empty() { return std::numeric_limits<int>::max(); }
  static const int append(int x, int y) { return std::min(x, y); }
};

int main() {
  int N = rd(), Q = rd();
  SegTree<Min> st(N);
  for (int i = 0; i < Q; i++) {
    int c = rd(), x = rd(), y = rd();
    if (c == 0) {
      st.modify(x, [y](int a){ return y; });
    } else {
      wr(st.query(x, y + 1));
    }
  }
  return 0;
}
