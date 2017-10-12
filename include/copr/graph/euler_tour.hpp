#ifndef INCLUDE_EULER_TOUR_HPP
#define INCLUDE_EULER_TOUR_HPP
#include <vector>

struct EulerTour {
  using tree_type = std::vector<std::vector<int>>;
  tree_type T;
  std::vector<int> begin, end;
  std::vector<int> id, depth;

  EulerTour(int N) : T(N), begin(N), end(N) {}

  void add_edge(int s, int t) {
    T[s].push_back(t);
    T[t].push_back(s);
  }

  void build(int root) {
    id.reserve(T.size() * 3);
    depth.reserve(T.size() * 3);
    traverse(root);
    id.shrink_to_fit();
    depth.shrink_to_fit();
  }

  void traverse(int u, int p=-1, int d=0) {
    begin[u] = end[u] = id.size();
    id.push_back(u);
    depth.push_back(d);
    for (int v : T[u]) {
      if (v == p) continue;
      traverse(v, u, d + 1);
      end[u] = id.size();
      id.push_back(u);
      depth.push_back(d);
    }
  }
};
#endif
