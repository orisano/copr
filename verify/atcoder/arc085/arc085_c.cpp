#include <copr/problem/project_selection.hpp>
#include <cstdio>
#include <limits>
#include <vector>
#define mygc(c) (c) = getchar_unlocked()
#define mypc(c) putchar_unlocked(c)
template<typename T=int>inline T rd(){T x=0,m=0,k;for(;;){mygc(k);if(k=='-'){m=1;break;}if('0'<=k&&k<='9'){x=k-'0';break;}}for(;;){mygc(k);if(k<'0'||'9'<k)break;x=x*10+k-'0';}if(m)x=-x;return x;}
template<typename T=int>inline void wr(T x,char c='\n'){int s=0,m=0;char b[32];if(x<0)m=1,x=-x;for(;x;x/=10)b[s++]=x%10;if(!s)b[s++]=0;if(m)mypc('-');for(;s--;)mypc(b[s]+'0');mypc(c);}

using ll = long long;
const ll inf = std::numeric_limits<ll>::max();

int main() {
  int N = rd();
  std::vector<ll> A(N);
  for (int i = 0; i < N; i++) A[i] = -rd();
  ll sum = 0;
  for (ll a : A) sum += -a;
  ProjectSelection<ll> ps(A);
  for (int x = 1; x <= N; x++) {
    for (int y = x + x; y <= N; y += x) {
      ps.add_loss(x - 1, y - 1, inf);
    }
  }
  wr(sum + ps.solve());
  return 0;
}
