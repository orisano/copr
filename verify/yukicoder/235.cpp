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

const unsigned long long MOD = 1e9 + 7;

inline ll mod_add(ll x, ll y) {
  x += y;
  if (x > MOD) x -= MOD;
  return x;
}

inline ll mod_sub(ll x, ll y) {
  x -= y;
  if (x < 0) x += MOD;
  return x;
}

inline ll mod_mul(ll x, ll y) {
  return x * y % MOD;
}

struct Sum {
  using value_type = ll;
  static ll empty() { return 0; }
  static ll append(ll x, ll y) { return mod_add(x, y); }
};

std::vector<ll> ssum, csum;

struct Add {
  using value_type = ll;
  static ll none() { return 0; }
  static ll eval(ll x, ll v, int l, int r) {
    return mod_add(x, mod_mul(v, mod_sub(csum[r], csum[l])));
  }
  static ll merge(ll x, ll y) { return mod_add(x, y); }
};

int main() {
  int N = rd();
  std::vector<ll> S(N);
  for (int i = 0; i < N; i++) S[i] = rd();
  std::vector<ll> C(N);
  for (int i = 0; i < N; i++) C[i] = rd();

  HLDecomposition hl(N);
  for (int i = 0; i < N - 1; i++) {
    int A = rd() - 1, B = rd() - 1;
    hl.add_edge(A, B);
  }
  hl.build();

  LazySegTree<Sum, Add> seg(N);
  ssum.resize(N + 1);
  csum.resize(N + 1);

  for (int i = 0; i < N; i++) {
    ssum[i + 1] = mod_add(ssum[i], S[hl.ord[i]]);
    csum[i + 1] = mod_add(csum[i], C[hl.ord[i]]);
  }

  int Q = rd();
  for (int i = 0; i < Q; i++) {
    int t = rd();
    int x = rd() - 1, y = rd() - 1;
    if (t) {
      ll ans = 0;
      hl.for_each(x, y, [&](int l, int r) {
        ans = mod_add(ans, mod_sub(ssum[r], ssum[l]));
        ans = mod_add(ans, seg.query(l, r));
      });
      wr(ans);
    } else {
      ll z = rd();
      hl.for_each(x, y, [&](int l, int r) { seg.exec(l, r, z); });
    }
  }
  return 0;
}
