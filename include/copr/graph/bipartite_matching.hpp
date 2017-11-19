#pragma once
#include <copr/graph/dinic.hpp>

struct BipartiteMatching {
  enum { S, T, OFFSET };
  const int X, Y;
  Dinic<int> dinic;

  BipartiteMatching(int X, int Y) : X(X), Y(Y), dinic(X + Y + 2) {
    for (int x = 0; x < X; x++) {
      dinic.add_edge(S, x + OFFSET, 1);
    }
    for (int y = 0; y < Y; y++) {
      dinic.add_edge(y + X + OFFSET, T, 1);
    }
  }
  void add_edge(int x, int y) { dinic.add_edge(x + OFFSET, y + X + OFFSET, 1); }
  int max_matching() { return dinic.max_flow_value(S, T); }
};
