#ifndef INCLUDE_EULER_TOUR_HPP
#define INCLUDE_EULER_TOUR_HPP
#include <stack>
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
    struct Frame {
      int u, p, d;
      int i = 0;
      Frame(int u, int p, int d) : u(u), p(p), d(d) {}
    };
    std::stack<Frame> s;

    s.emplace(u, p, d);
    while (!s.empty()) {
      auto& f = s.top();
      if (f.i == 0) begin[f.u] = id.size();
      end[f.u] = id.size();
      id.push_back(f.u);
      depth.push_back(f.d);

      bool call = false;
      while (f.i < T[f.u].size()) {
        int v = T[f.u][f.i];
        ++f.i;
        if (v != f.p) {
          s.emplace(v, f.u, f.d + 1);
          call = true;
          break;
        }
      }
      if (!call) s.pop();
    }
  }
};
#endif
