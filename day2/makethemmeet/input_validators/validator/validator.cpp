#include "validator.h"
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100;

void run() {
  int group = Arg("group");

  int N = Int(2, MAXN);
  Space();
  int M = Int(N - 1, (N * N - N) / 2);
  Endl();

  vector<vector<int>> graph(N, vector<int>());

  set<pair<int, int>> edges;

  for (int i = 0; i < M; i++) {
    int u = Int(0, N - 1);
    Space();
    int v = Int(0, N - 1);
    graph[u].push_back(v);
    graph[v].push_back(u);
    edges.insert({u, v});
    edges.insert({v, u});
    assert(u != v);
    if (group == 2) {
      assert(u == i && v == i + 1);
    }
    if (group == 0) {
      assert(u == 0 && v == i + 1);
    }
    Endl();
  }
  assert(edges.size() == 2 * M);

  // Connectedness
  vector<int> queue;
  vector<int> seen(N, 0);
  int num_seen = 0;
  queue.push_back(0);
  while (queue.size() > 0) {
    int u = queue.back();
    queue.pop_back();
    if (!seen[u]) {
      seen[u] = 1;
      num_seen++;
      for (auto v : graph[u]) {
        queue.push_back(v);
      }
    }
  }

  assert(num_seen == N);

  int max_deg = 0;
  for (int i = 0; i < N; i++) {
    max_deg = max(max_deg, (int)graph[i].size());
  }

  if (group == 1)
    assert(2 * M == (N * N - N));
  if (group == 2)
    assert(M == N - 1 && max_deg <= 2);
  if (group == 3)
    assert(M == N - 1);
}
