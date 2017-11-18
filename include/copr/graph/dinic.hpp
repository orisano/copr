#pragma once
#include <algorithm>
#include <limits>
#include <queue>
#include <vector>

template<typename CapacityType>
struct Dinic {
  using value_type = CapacityType;
  struct Edge {
    CapacityType cap;
    const int to, rev;
    const bool is_rev;
    Edge(int to, CapacityType cap, int rev, bool is_rev) : cap(cap), to(to), rev(rev), is_rev(is_rev) {}
  };

  static constexpr auto inf = std::numeric_limits<CapacityType>::max();
  const int UNREACHABLE = -1;

  std::vector<std::vector<Edge>> G;
  std::vector<int> level, iter;
  Dinic(int V) : G(V), level(V), iter(V) {}

  void add_edge(int from, int to, CapacityType cap) {
    int trev = G[from].size();
    int frev = G[to].size();
    G[from].emplace_back(to, cap, frev, false);
    G[to].emplace_back(from, 0, trev, true);
  }
  inline Edge& rev_edge(const Edge& e) {
    return G[e.to][e.rev];
  }
  CapacityType max_flow_value(int s, int t) {
    CapacityType value = 0;
    while (labeling(s), level[t] != UNREACHABLE) {
      std::fill(iter.begin(), iter.end(), 0);
      CapacityType bf;
      while (bf = blocking_flow(s, t, inf), bf > 0) {
        value += bf;
      }
    }
    return value;
  }
  bool labeling(int s) {
    std::fill(level.begin(), level.end(), UNREACHABLE);
    level[s] = 0;
    static std::queue<int> Q;
    Q.push(s);
    for (; !Q.empty(); Q.pop()) {
      auto v = Q.front();
      for (auto&& e : G[v]) {
        if (level[e.to] != UNREACHABLE) continue;
        if (e.cap == 0) continue;
        level[e.to] = level[v] + 1;
        Q.push(e.to);
      }
    }
    return true;
  }
  CapacityType blocking_flow(int v, int t, CapacityType f) {
    if (v == t) return f;
    auto& V = G[v];
    for (int& i = iter[v]; i < V.size(); ++i) {
      auto& e = V[i];
      if (e.cap == 0) continue;
      if (level[v] >= level[e.to]) continue;
      auto bf = blocking_flow(e.to, t, std::min(f, e.cap));
      if (bf > 0) {
        e.cap -= bf;
        rev_edge(e).cap += bf;
        return bf;
      }
    }
    return 0;
  }

  struct Flow {
    const int to;
    const CapacityType out;
    Flow(int to, CapacityType out) : to(to), out(out) {}
  };
  std::vector<std::vector<Flow>> build_flow() const {
    const int V = G.size();
    std::vector<std::vector<Flow>> F(V);
    for (int i = 0; i < V; i++) {
      for (auto&& e : G[i]) {
        if (not e.is_rev) continue;
        if (e.cap == 0) continue;
        F[e.to].emplace_back(i, e.cap);
      }
    }
    return F;
  }
};
