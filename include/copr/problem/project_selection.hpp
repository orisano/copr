#pragma once
#include <copr/graph/dinic.hpp>

#include <cassert>
#include <vector>

template <typename ProfitType>
struct ProjectSelection {
  enum { S, T, OFFSET };

  Dinic<ProfitType> dinic;
  ProfitType sum;

  ProjectSelection(const std::vector<ProfitType>& profits) : dinic(profits.size() + 2), sum(0) {
    int N = profits.size();
    for (int i = 0; i < N; i++) {
      auto pv = profits[i];
      if (pv == 0) continue;
      int v = i + OFFSET;
      if (pv > 0) {
        dinic.add_edge(S, v, pv);
        sum += pv;
      } else {
        dinic.add_edge(v, T, -pv);
      }
    }
  }
  void add_loss(int selected, int unselected, ProfitType loss) {
    assert(loss > 0);
    int x = selected + OFFSET;
    int y = unselected + OFFSET;
    dinic.add_edge(x, y, loss);
  }
  ProfitType solve() { return sum - dinic.max_flow_value(S, T); }
};
