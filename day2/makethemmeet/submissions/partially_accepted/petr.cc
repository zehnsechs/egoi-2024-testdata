#include <bits/stdc++.h>

using namespace std;
using int64 = int64_t;

constexpr int INF = (int) 1e9;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> d(n, vector<int>(n, INF));
    for (int i = 0; i < n; ++i) d[i][i] = 0;
    for (int i = 0; i < m; ++i) {
      int a, b;
      cin >> a >> b;
      assert(d[a][b] == INF);
      d[a][b] = d[b][a] = 1;
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
    vector<tuple<double, int, int>> cands;
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
            cands.emplace_back(-score, i, j);
          }
          {
            bool ok = true;
            double score = 0;
            int cnt_in = 0;
            int cnt_out = 0;
            for (int j1 = 0; j1 < n; ++j1) if (d[i][j1] == 1) {
              if (!avail[j1]) { ok = false; break; }
              if (can[i][j1]) ++cnt_in; else ++cnt_out;
              for (int j2 = j1 + 1; j2 < n; ++j2) if (d[i][j2] == 1) {
                if (d[j1][j2] == 1) { ok = false; break; }
                if (can[j1][j2]) score += BONUS2 * scores[1];
              }
            }
            if (!ok) continue;
            if (cnt_in) score -= BONUS2 * scores[1] * cnt_out;
            for (int k = 0; k < n; ++k) if (d[i][k] >= 2) {
              cnt_in = 0;
              cnt_out = 0;
              for (int j1 = 0; j1 < n; ++j1) if (d[i][j1] == 1) {
                if (can[k][j1]) ++cnt_in; else ++cnt_out;
              }
              if (cnt_in) {
                score += BONUS2 * scores[1] * (cnt_in - 1);
              }
              if (can[k][i]) {
                score -= BONUS2 * scores[1] * (cnt_out + cnt_in);
              }
            }
            cands.emplace_back(-score, i, -1);
          }
        }

        sort(cands.begin(), cands.end());
        for (auto [bs, bi, bj]: cands) {
          if (bj < 0) {
            bool ok = avail[bi];
            for (int j1 = 0; j1 < n; ++j1) if (d[bi][j1] == 1) {
              if (!avail[j1]) ok = false;
            }
            if (!ok) continue;
            //cerr << "Using spoke at " << bi << ", score = " << bs << "\n";
            avail[bi] = false;
            bool h = false;
            for (int j1 = 0; j1 < n; ++j1) if (d[bi][j1] == 1) {
              avail[j1] = false;
              c[j1] = c[bi];
              if (can[bi][j1]) h = true;
              for (int j2 = j1 + 1; j2 < n; ++j2) if (d[bi][j2] == 1) {
                can[j1][j2] = false;
                can[j2][j1] = false;
              }
            }
            if (h) {
              for (int j1 = 0; j1 < n; ++j1) if (d[bi][j1] == 1) {
                can[bi][j1] = true;
                can[j1][bi] = true;
              }
            }
            for (int k = 0; k < n; ++k) if (k != bi && d[bi][k] != 1) {
              bool center = can[bi][k];
              bool spoke = false;
              for (int j1 = 0; j1 < n; ++j1) if (d[bi][j1] == 1 && can[j1][k]) spoke = true;
              can[bi][k] = spoke;
              can[k][bi] = spoke;
              for (int j1 = 0; j1 < n; ++j1) if (d[bi][j1] == 1) {
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
