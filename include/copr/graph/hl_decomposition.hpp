#pragma once
#include <algorithm>
#include <functional>
#include <vector>

struct HLDecomposition {
  struct Node {
    int ord, par, depth;
    int idx;
    int path_id = -1;
    Node() {}
  };

  const int N;
  std::vector<std::vector<int>> tree, pathes;
  std::vector<Node> nodes;
  std::vector<int> Q;

  HLDecomposition(int N) : N(N), tree(N), nodes(N) {}
  void add_edge(int u, int v) {
    tree[u].push_back(v);
    tree[v].push_back(u);
  }
  void build(int root = 0) {
    Q.reserve(N);
    Q.push_back(root);
    nodes[root].par = -1;
    nodes[root].depth = 0;
    for (int i = 0; i < Q.size(); i++) {
      int u = Q[i];
      auto& U = nodes[u];
      U.ord = i;
      for (int v : tree[u]) {
        if (U.par == v) continue;
        auto& V = nodes[v];
        V.par = u;
        V.depth = U.depth + 1;
        Q.push_back(v);
      }
    }
    decomposition();
  }
  void for_each(int u, int v, std::function<void(int, int, int)> f) const {
    while (nodes[u].path_id != nodes[v].path_id) {
      int head_u = pathes[nodes[u].path_id][0];
      int head_v = pathes[nodes[v].path_id][0];
      if (nodes[head_u].depth > nodes[head_v].depth) {
        std::swap(u, v);
        std::swap(head_u, head_v);
      }
      f(nodes[v].path_id, 0, nodes[v].idx + 1);
      v = nodes[head_v].par;
    }
    if (nodes[v].idx < nodes[u].idx) std::swap(u, v);
    f(nodes[v].path_id, nodes[u].idx, nodes[v].idx + 1);
  }
  int lca(int u, int v) const {
    int x;
    for_each(u, v, [&](int p, int l, int r) { x = pathes[p][l]; });
    return x;
  }
  void decomposition() {
    std::vector<int> subtree_size(N, 1);
    for (int i = N - 1; i > 0; i--) {
      subtree_size[nodes[Q[i]].par] += subtree_size[Q[i]];
    }
    for (int u : Q) {
      auto& U = nodes[u];
      if (U.path_id == -1) {
        U.path_id = pathes.size();
        pathes.emplace_back();
      }
      pathes[U.path_id].push_back(u);

      int max_subsize = -1, selected = -1;
      for (int v : tree[u]) {
        if (U.par == v) continue;
        if (max_subsize >= subtree_size[v]) continue;
        max_subsize = subtree_size[v];
        selected = v;
      }
      if (selected != -1) nodes[selected].path_id = U.path_id;
    }
    for (auto&& path : pathes) {
      for (int i = 0; i < path.size(); i++) {
        nodes[path[i]].idx = i;
      }
    }
  }
};
