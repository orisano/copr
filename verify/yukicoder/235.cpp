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

const ll MOD = 1e9 + 7;

struct Sum {
  using value_type = ll;
  static ll empty() { return 0; }
  static ll append(ll x, ll y) { return (x + y) % MOD; }
};

int gp;
std::vector<std::vector<ll>> ssum, csum;

struct Add {
  using value_type = ll;
  static ll none() { return 0; }
  static ll eval(ll x, ll v, int l, int r) {
    return (x + (v * ((csum[gp][r] - csum[gp][l] + MOD) % MOD)) % MOD) % MOD;
  }
  static ll merge(ll x, ll y) { return (x + y) % MOD; }
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

  const int P = hl.pathes.size();
  std::vector<LazySegTree<Sum, Add>> segs;
  segs.reserve(P);
  ssum.resize(P);
  csum.resize(P);
  for (int p = 0; p < P; p++) {
    const int L = hl.pathes[p].size();
    segs.emplace_back(L);
    ssum[p].resize(L + 1);
    csum[p].resize(L + 1);
    for (int i = 1; i <= L; i++) {
      int u = hl.pathes[p][i - 1];
      ssum[p][i] = (ssum[p][i - 1] + S[u]) % MOD;
      csum[p][i] = (csum[p][i - 1] + C[u]) % MOD;
    }
  }

  int Q = rd();
  for (int i = 0; i < Q; i++) {
    int t = rd();
    int x = rd() - 1, y = rd() - 1;
    if (t) {
      ll ans = 0;
      hl.for_each(x, y, [&](int p, int l, int r) {
        gp = p;
        ans += (ssum[p][r] - ssum[p][l] + MOD) % MOD;
        ans += segs[p].query(l, r);
        ans %= MOD;
      });
      wr(ans);
    } else {
      ll z = rd();
      hl.for_each(x, y, [&](int p, int l, int r) {
        gp = p;
        segs[p].exec(l, r, z);
      });
    }
  }
  return 0;
}
