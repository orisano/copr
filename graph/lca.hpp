#include <vector>
#include <utility>

struct LCA {
  EulerTour& euler_tour;
  const RMQ<int> rmq;

  LCA(EulerTour& euler_tour) : euler_tour(euler_tour), rmq(euler_tour.depth) {}

  int query(int u, int v) const {
    int l = euler_tour.ord[u];
    int r = euler_tour.ord[v];
    if (r < l) std::swap(r, l);
    int x = rmq.query(l, r);
    return euler_tour.id[x];
  }
};
