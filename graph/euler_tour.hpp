#include <vector>
#include <map>

struct EulerTour {
  using tree_type = std::vector<std::vector<int>>;
  tree_type T;
  std::vector<int> id, depth;
  std::map<int, int> ord;

  EulerTour(int N) : T(N) {}

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
    ord[u] = id.size();
    id.push_back(u);
    depth.push_back(d);
    for (int v : T[u]) {
      if (v == p) continue;
      traverse(v, u, d + 1);
      id.push_back(u);
      depth.push_back(d);
    }
  }
};
