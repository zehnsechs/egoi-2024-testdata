#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define debug(...) // ignore
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef long double ld;

int main() {
  int n;
  cin >> n;

  bool transpose = false;
  auto printgrid = [&](vector<pii> v) {
    if (transpose) for (auto &[a, b] : v) swap(a, b);
    vector<string> grid(n,string(n,'0'));
    for(auto [a,b] : v) grid[a][b] = '1';
    for(auto g : grid) cout << g << endl;
  };
  auto query = [&](vector<pii> v) {
    cout << "?" << endl;
    printgrid(v);
    int x;
    cin >> x;
    return x;
  };
  auto answer = [&](vector<pii> v) {
    assert(sz(v) == n);
    cout << "!" << endl;
    printgrid(v);
    exit(0);
  };

  {
    int a = query({{0, 0}, {0, 1}, {0, 2}});
    int b = query({{0, 1}, {0, 2}});
    set<pii> vert = {{3 * n, 2 * n}, {3 * n - 2, 2 * n - 1}, {2 * n - 1, n}};
    set<pii> horz = {{3 * n - 2, 2 * n}, {2 * n - 1, 2 * n - 1}, {n, n}};
    if (vert.count(pii(a, b))) transpose = true;
    else assert(horz.count(pii(a, b)));
    // now assume top-left is horizontal
  }
  vector<pii> h = {{0, 0}}, v;
  int x = 1, y = 0;
  while (x < n && y < n) {
    int q = query({{0, 0}, {x, y}});
    if (q == 2 * n) h.emplace_back(x++, y);
    else if (q == 2 * n - 1) v.emplace_back(x, y++);
    else assert(false);
  }
  if (x == n) answer(h);
  else answer(v);
}
