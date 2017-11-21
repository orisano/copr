#pragma once
#include <algorithm>
#include <functional>
#include <vector>

struct HLDecomposition {
  const int N;
  std::vector<std::vector<int>> tree;
  std::vector<int> cluster, par, depth, ord, head, offset;
  HLDecomposition(int N) : N(N), tree(N), cluster(N, -1), par(N, -1), depth(N), ord(N), offset(N) {}

  void add_edge(int u, int v) {
    tree[u].push_back(v);
    tree[v].push_back(u);
  }
  void build(int root = 0) {
    std::vector<int> Q;
    Q.reserve(N);
    Q.push_back(root);
    for (int i = 0; i < N; i++) {
      int u = Q[i];
      for (int v : tree[u]) {
        if (par[u] == v) continue;
        par[v] = u;
        depth[v] = depth[u] + 1;
        Q.push_back(v);
      }
    }
    std::vector<int> subtree_size(N, 1);
    for (int i = N - 1; i > 0; i--) {
      subtree_size[par[Q[i]]] += subtree_size[Q[i]];
    }
    std::vector<std::vector<int>> pathes;
    for (int u : Q) {
      if (cluster[u] == -1) {
        cluster[u] = pathes.size();
        pathes.emplace_back();
      }
      pathes[cluster[u]].push_back(u);
      int max_subsize = -1, selected = -1;
      for (int v : tree[u]) {
        if (par[u] == v) continue;
        if (max_subsize >= subtree_size[v]) continue;
        max_subsize = subtree_size[v];
        selected = v;
      }
      if (selected != -1) cluster[selected] = cluster[u];
    }
    int P = pathes.size();
    head.resize(P + 1);
    for (int p = 0; p < P; p++) {
      int H = head[p];
      int L = pathes[p].size();
      head[p + 1] = H + L;
      for (int i = 0; i < L; i++) {
        int v = pathes[p][i];
        offset[v] = i;
        ord[H + i] = v;
      }
    }
  }
  void for_each(int u, int v, std::function<void(int, int)> f) const {
    while (cluster[u] != cluster[v]) {
      if (depth[ord[head[cluster[u]]]] > depth[ord[head[cluster[v]]]]) std::swap(u, v);
      int h = head[cluster[v]];
      f(h, h + offset[v] + 1);
      v = par[ord[h]];
    }
    if (offset[u] > offset[v]) std::swap(u, v);
    f(head[cluster[u]] + offset[u], head[cluster[v]] + offset[v] + 1);
  }
  int lca(int u, int v) const {
    int x;
    for_each(u, v, [&](int l, int r) { x = ord[l]; });
    return x;
  }
  std::vector<std::vector<int>> build_pathes() const {
    const int P = head.size() - 1;
    std::vector<std::vector<int>> pathes(P);
    for (int i = 0; i < P; i++) {
      pathes[i].reserve(head[i + 1] - head[i]);
      for (int j = head[i]; j < head[i + 1]; j++) {
        pathes[i].push_back(ord[j]);
      }
    }
    return pathes;
  }
};
