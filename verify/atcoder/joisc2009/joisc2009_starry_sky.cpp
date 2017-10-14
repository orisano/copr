#include <copr/sequence/starry_sky_tree.hpp>

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <queue>
#include <vector>

#define mygc(c) (c) = getchar_unlocked()
#define mypc(c) putchar_unlocked(c)
template<typename T=int>inline T rd(){T x=0,m=0,k;for(;;){mygc(k);if(k=='-'){m=1;break;}if('0'<=k&&k<='9'){x=k-'0';break;}}for(;;){mygc(k);if(k<'0'||'9'<k)break;x=x*10+k-'0';}return x;}
template<typename T=int>inline void wr(T x,char c='\n'){int s=0,m=0;char b[32];if(x<0)m=1,x=-x;for(;x;x/=10)b[s++]=x%10;if(!s)b[s++]=0;if(m)mypc('-');for(;s--;)mypc(b[s]+'0');mypc(c);}


struct Star {
  int x, y, L;
  short l, po;
  Star(int x, int y, int L) : x(x), y(y), L(L) {}
  bool operator<(const Star& rhs) const {
    return y < rhs.y;
  }
  inline bool ok(const Star& o) const {
    return L <= o.L && std::abs(y - o.y) <= L && std::abs(x - o.x) <= L;
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
  for (auto& si : stars) {
    si.l = std::lower_bound(xs.begin(), xs.end(), si.x) - xs.begin();
    short po = 1;
    for (auto& sj : stars) {
      if (si.ok(sj)) po++;
    }
    si.po = po;
  }

  StarrySkyTree<short> sst(4000);
  short maxi = 0;

  struct Event {
    int y;
    short l, r;
    Event(int y, short l, short r) : y(y), l(l), r(r) {}
  };

  for (auto&& si : stars) {
    if (si.po <= maxi) continue;

    std::queue<Event> es;
    for (auto&& sj : stars) {
      if (not si.ok(sj)) continue;
      while (!es.empty() && es.front().y < sj.y) {
        auto e = es.front();
        es.pop();
        sst.add(-1, e.l, e.r);
      }
      int r = std::lower_bound(xs.begin(), xs.end(), sj.x + si.L + 1) - xs.begin();
      es.emplace(sj.y + si.L + 1, sj.l, r);

      sst.add(1, sj.l, r);
      short v = sst.query(0, sst.N);
      if (maxi < v) maxi = v;
    }
    while (!es.empty()) {
      auto e = es.front();
      es.pop();
      sst.add(-1, e.l, e.r);
    }
  }
  wr(maxi);
  return 0;
}
