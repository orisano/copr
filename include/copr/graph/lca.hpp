#pragma once
#include <copr/graph/euler_tour.hpp>
#include <copr/sequence/rmq.hpp>
#include <utility>

struct LCA {
  EulerTour euler_tour;
  const RMQ<int> rmq;

  LCA(EulerTour&& euler_tour) : euler_tour(euler_tour), rmq(euler_tour.depth) {}

  int query(int u, int v) const {
    int l = euler_tour.begin[u];
    int r = euler_tour.begin[v];
    if (r < l) std::swap(r, l);
    int x = rmq.query(l, r);
    return euler_tour.id[x];
  }
};
