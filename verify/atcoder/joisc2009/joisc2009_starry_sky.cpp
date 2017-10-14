#include <copr/sequence/starry_sky_tree.hpp>

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <vector>

#define mygc(c) (c) = getchar_unlocked()
#define mypc(c) putchar_unlocked(c)
template<typename T=int>inline T rd(){T x=0,m=0,k;for(;;){mygc(k);if(k=='-'){m=1;break;}if('0'<=k&&k<='9'){x=k-'0';break;}}for(;;){mygc(k);if(k<'0'||'9'<k)break;x=x*10+k-'0';}return x;}
template<typename T=int>inline void wr(T x,char c='\n'){int s=0,m=0;char b[32];if(x<0)m=1,x=-x;for(;x;x/=10)b[s++]=x%10;if(!s)b[s++]=0;if(m)mypc('-');for(;s--;)mypc(b[s]+'0');mypc(c);}

struct Star {
  int x, y, L;
  Star(int x, int y, int L) : x(x), y(y), L(L) {}
  bool operator<(const Star& rhs) const {
    if (L != rhs.L) return L > rhs.L;
    if (x != rhs.x) return x > rhs.x;
    return y > rhs.y;
  }
  inline bool ok(const Star& o) const {
    return ((y > o.y) ? (y - o.y) : (o.y - y)) <= L && ((x > o.x) ? (x - o.x) : (o.x - x)) <= L;
  }
};

int main() {
  int N = rd();

  std::vector<Star> stars;
  std::vector<int> xs;

  stars.reserve(N);
  xs.reserve(N);
  for (int i = 0; i < N; i++) {
    int x = rd(), y = rd(), L = rd();
    stars.emplace_back(x, y, L);
    xs.push_back(x);
  }
  std::sort(xs.begin(), xs.end());
  xs.erase(std::unique(xs.begin(), xs.end()), xs.end());

  std::sort(stars.begin(), stars.end());

  StarrySkyTree<short> sst(4000);
  short maxi = 0;

  struct Event {
    int t, l, r, v;
    Event(int t, int l, int r, int v) : t(t), l(l), r(r), v(v) {}
    bool operator<(const Event& rhs) const { return t < rhs.t; }
  };
  std::vector<Event> es;
  es.reserve(N * 2);
  for (int i = N - 1; i >= 0; i--) {
    const auto& si = stars[i];
    es.clear();
    for (int j = 0; j <= i; j++) {
      const auto& sj = stars[j];
      if (not si.ok(sj)) continue;
      int l = std::lower_bound(xs.begin(), xs.end(), sj.x) - xs.begin();
      int r = std::lower_bound(xs.begin(), xs.end(), sj.x + si.L + 1) - xs.begin();
      es.emplace_back(sj.y, l, r, 1);
      es.emplace_back(sj.y + si.L + 1, l, r, -1);
    }
    if (es.size() / 2 < maxi) continue;

    std::sort(es.begin(), es.end());
    for (const auto& e : es) {
      sst.add(e.v, e.l, e.r);
      short v = sst.query(0, sst.N);
      if (maxi < v) maxi = v;
    }
  }
  wr(maxi);
  return 0;
}
