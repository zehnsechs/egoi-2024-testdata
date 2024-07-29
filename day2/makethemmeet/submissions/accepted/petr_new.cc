#include <bits/stdc++.h>

using namespace std;
using int64 = int64_t;

constexpr int INF = (int) 1e9;

using mask = bitset<100>;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> d(n, vector<int>(n, INF));
    vector<mask> adj(n);
    for (int i = 0; i < n; ++i) d[i][i] = 0;
    for (int i = 0; i < m; ++i) {
      int a, b;
      cin >> a >> b;
      assert(d[a][b] == INF);
      d[a][b] = d[b][a] = 1;
      adj[a].set(b);
      adj[b].set(a);
    }
    for (int k = 0; k < n; ++k)
      for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
          d[i][j] = min(d[i][j], d[i][k] + d[k][j]);

    vector<vector<bool>> can(n, vector<bool>(n, false));
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) if (i != j) can[i][j] = true;
    vector<vector<int>> res;
    mt19937 rng(57);
    vector<double> scores = vector<double>(n);
    scores[n - 1] = 1;
    for (int i = n - 2; i >= 0; --i) scores[i] = scores[i + 1] + (n - i);
    vector<int> c(n);
    vector<bool> avail(n, true);
    vector<tuple<double, int, int, mask>> cands;
    vector<int> order(n);
    double BONUS = 5;
    double BONUS2 = 3;
    while (true) {
      bool any = false;
      for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) if (can[i][j]) any = true;
      if (!any) break;
      iota(c.begin(), c.end(), 0);
      avail.assign(n, true);
      iota(order.begin(), order.end(), 0);
      while (true) {
        shuffle(order.begin(), order.end(), rng);
        cands.clear();
        for (int ii = 0; ii < n; ++ii) {
          int i = order[ii];
          if (!avail[i]) continue;
          for (int jj = ii + 1; jj < n; ++jj) {
            int j = order[jj];
            if (!avail[j] || d[i][j] != 1) continue;
            double score = 0;
            if (can[i][j]) score += BONUS * scores[1];
            for (int k = 0; k < n; ++k) if (k != i && k != j) {
              if (can[i][k] && !can[j][k]) score -= scores[d[i][k]] - scores[d[j][k]];
              if (can[j][k] && !can[i][k]) score -= scores[d[j][k]] - scores[d[i][k]];
            }
            cands.emplace_back(-score, i, j, 0);
          }
          {
            double score = 0;
            int cnt_in = 0;
            int cnt_out = 0;
            mask taken = 0;
            mask forbidden = 0;
            for (int jj1 = 0; jj1 < n; ++jj1) {
              int j1 = order[jj1];
              if (d[i][j1] == 1 && avail[j1] && !forbidden.test(j1)) {
                taken.set(j1);
                forbidden |= adj[j1];
                if (can[i][j1]) ++cnt_in; else ++cnt_out;
                for (int jj2 = 0; jj2 < jj1; ++jj2) {
                  int j2 = order[jj2];
                  if (taken.test(j2)) {
                    if (d[j1][j2] == 1) { assert(false); }
                    if (can[j1][j2]) score += BONUS2 * scores[1];
                  }
                }
              }
            }
            if (cnt_in) score -= BONUS2 * scores[1] * cnt_out;
            for (int k = 0; k < n; ++k) if (k != i && !taken.test(k)) {
              cnt_in = 0;
              cnt_out = 0;
              for (int j1 = 0; j1 < n; ++j1) if (taken.test(j1)) {
                if (can[k][j1]) ++cnt_in; else ++cnt_out;
              }
              if (cnt_in) {
                score += BONUS2 * scores[1] * (cnt_in - 1);
              }
              if (can[k][i]) {
                score -= BONUS2 * scores[1] * (cnt_out + cnt_in);
              }
            }
            cands.emplace_back(-score, i, -1, taken);
          }
        }

        sort(cands.begin(), cands.end(), [](const auto& a, const auto& b) {
          return tie(get<0>(a), get<1>(a), get<2>(a)) < tie(get<0>(b), get<1>(b), get<2>(b));
        });
        for (auto [bs, bi, bj, taken]: cands) {
          if (bj < 0) {
            bool ok = avail[bi];
            for (int j1 = 0; j1 < n; ++j1) if (taken.test(j1)) {
              if (!avail[j1]) ok = false;
            }
            if (!ok) continue;
            //cerr << "Using spoke at " << bi << ", score = " << bs << "\n";
            avail[bi] = false;
            bool h = false;
            for (int j1 = 0; j1 < n; ++j1) if (taken.test(j1)) {
              avail[j1] = false;
              c[j1] = c[bi];
              if (can[bi][j1]) h = true;
              for (int j2 = j1 + 1; j2 < n; ++j2) if (taken.test(j2)) {
                can[j1][j2] = false;
                can[j2][j1] = false;
              }
            }
            if (h) {
              for (int j1 = 0; j1 < n; ++j1) if (taken.test(j1)) {
                can[bi][j1] = true;
                can[j1][bi] = true;
              }
            }
            for (int k = 0; k < n; ++k) if (k != bi && !taken.test(k)) {
              bool center = can[bi][k];
              bool spoke = false;
              for (int j1 = 0; j1 < n; ++j1) if (taken.test(j1) && can[j1][k]) spoke = true;
              can[bi][k] = spoke;
              can[k][bi] = spoke;
              for (int j1 = 0; j1 < n; ++j1) if (taken.test(j1)) {
                can[j1][k] = center;
                can[k][j1] = center;
              }
            }
          } else {
            if (avail[bi] && avail[bj]) {
              //cerr << "Using edge " << bi << "-" << bj << ", score = " << bs << "\n";
              if (uniform_int_distribution<int>(0, 10)(rng) == 0) continue;
              c[bi] = c[bj];
              avail[bi] = false;
              avail[bj] = false;
              can[bi][bj] = can[bj][bi] = false;
              for (int k = 0; k < n; ++k) if (k != bi && k != bj) {
                if (can[bi][k] && !can[bj][k]) {
                  can[bj][k] = true;
                  can[k][bj] = true;
                  can[bi][k] = false;
                  can[k][bi] = false;
                } else if (can[bj][k] && !can[bi][k]) {
                  can[bj][k] = false;
                  can[k][bj] = false;
                  can[bi][k] = true;
                  can[k][bi] = true;
                }
              }
            }
          }
        }
        break;
      }
      res.push_back(c);
      //for (int i = 0; i < n; ++i) {
      //  for (int j = 0; j < n; ++j) if (can[i][j]) cerr << '+'; else cerr << '-';
      //  cerr << '\n';
      //}
      //cerr << endl;
    }
    printf("%d\n", res.size());
    for (const auto& v : res) {
      for (auto x : v) printf("%d ", x);
      printf("\n");
    }
    return 0;
}
