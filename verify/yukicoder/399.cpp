#include <copr/graph/hl_decomposition.hpp>
#include <copr/sequence/lazy_seg_tree.hpp>
#include <cstdio>
#define mygc(c) (c) = getchar_unlocked()
#define mypc(c) putchar_unlocked(c)
// clang-format off
template<typename T=int>inline T rd(){T x=0,m=0,k;for(;;){mygc(k);if(k=='-'){m=1;break;}if('0'<=k&&k<='9'){x=k-'0';break;}}for(;;){mygc(k);if(k<'0'||'9'<k)break;x=x*10+k-'0';}if(m)x=-x;return x;}
template<typename T=int>inline void wr(T x,char c='\n'){int s=0,m=0;char b[32];if(x<0)m=1,x=-x;for(;x;x/=10)b[s++]=x%10;if(!s)b[s++]=0;if(m)mypc('-');for(;s--;)mypc(b[s]+'0');mypc(c);}
// clang-format on

using ll = long long;

struct Sum {
  using value_type = ll;
  static ll empty() { return 0; }
  static ll append(ll x, ll y) { return x + y; }
};

struct Add {
  using value_type = ll;
  static ll none() { return 0; }
  static ll eval(ll x, ll v, int l, int r) { return x + v * (r - l); }
  static ll merge(ll x, ll y) { return x + y; }
};

int main() {
  int N = rd();
  HLDecomposition hl(N);
  for (int i = 0; i < N - 1; i++) {
    int u = rd() - 1, v = rd() - 1;
    hl.add_edge(u, v);
  }
  hl.build();

  LazySegTree<Sum, Add> seg(N);
  int Q = rd();
  ll ans = 0;
  for (int i = 0; i < Q; i++) {
    int A = rd() - 1, B = rd() - 1;
    hl.for_each(A, B, [&](int l, int r) {
      seg.exec(l, r, 1);
      ans += seg.query(l, r);
    });
  }
  wr(ans);
  return 0;
}
