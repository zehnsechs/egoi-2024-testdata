#include <bits/stdc++.h>

using namespace std;
using int64 = int64_t;
using ii = pair<int, int>;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    vector<int> p(n);
    p[0] = -1;
    for (int i = 1; i < n; ++i) cin >> p[i];
    vector<vector<int>> children(n);
    for (int i = 1; i < n; ++i) children[p[i]].push_back(i);
    vector<int> level(n);
    map<int, map<int, int>> counts;
    vector<vector<int>> order(n);
    vector<vector<int>> orderByLevel(n);
    vector<int> left(n);
    vector<int> right(n);
    vector<int> leftByLevel(n);
    vector<int> rightByLevel(n);
    vector<int> size(n);
    int ptr = 0;
    auto dfs = [&](auto self, int root) -> void {
      level[root] = p[root] < 0 ? 0 : 1 + level[p[root]];
      ++counts[a[root]][level[root]];
      left[root] = order[a[root]].size();
      leftByLevel[root] = ptr;
      orderByLevel[level[root]].push_back(ptr);
      ++ptr;
      order[a[root]].push_back(root);
      size[root] = 1;
      for (int child : children[root]) {
        self(self, child);
        size[root] += size[child];
      }
      right[root] = order[a[root]].size();
      rightByLevel[root] = ptr;
    };
    dfs(dfs, 0);
    assert(ptr == n);

    int res = 0;
    int rsteps = 0;
    auto dfs2 = [&](auto self, int root) -> pair<map<int, map<int, int>>, map<int, int>> {
      vector<pair<map<int, map<int, int>>, map<int, int>>> cres;
      pair<map<int, map<int, int>>, map<int, int>> cur;
      int mchild = -1;
      for (int child : children[root]) {
        if (mchild < 0 || size[child] > size[mchild]) mchild = child;
      }
      for (int child : children[root]) {
        if (child == mchild) {
          cur = std::move(self(self, child));
        } else {
          cres.push_back(std::move(self(self, child)));
        }
      }
      for (const auto& other : cres) {
        for (const auto& [l, c_cnt] : other.first) {
          
        }
      }
      return std::move(cur);
    };

    vector<int> mark(n);
    for (int c = 0; c < n; ++c) {
      vector<ii> to_check;
      for (int x : order[c]) {
        if (mark[x]) continue;
        for (int i = left[x]; i < right[x]; ++i) {
          int v = order[c][i];
          mark[v] = 1;
        }
        to_check.emplace_back(level[x], x);
      }
      sort(to_check.begin(), to_check.end());
      if (to_check.size() > 100) to_check.resize(100);
      for (auto [xx, x] : to_check) {
        auto it = counts[c].lower_bound(level[x] + 1);
        int score = 1;
        while (it != counts[c].end()) {
          int l = it->first;
          int total = it->second;
          int avail = lower_bound(orderByLevel[l].begin(), orderByLevel[l].end(), rightByLevel[x]) - lower_bound(orderByLevel[l].begin(), orderByLevel[l].end(), leftByLevel[x]);
          score += min(total, avail);
          ++it;
        }
        int csteps = score - (right[x] - left[x]);
        if (score > res || (score == res && csteps < rsteps)) {
          res = score;
          rsteps = csteps;
        }
      }
    }
    cout << res << " " << rsteps << "\n";
    return 0;
}
