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

  auto printgrid = [&](vector<pii> v) {
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

  auto get = [&](int x, int y) {
    int a = query({{x, y}, {x, (y+1)%n}, {x, (y+2)%n}});
    int b = query({{x, (y+1)%n}, {x, (y+2)%n}});
    set<pii> vert = {{3 * n, 2 * n}, {3 * n - 2, 2 * n - 1}, {2 * n - 1, n}};
    set<pii> horz = {{3 * n - 2, 2 * n}, {2 * n - 1, 2 * n - 1}, {n, n}};
    if (vert.count(pii(a, b))) return 'v';
    assert(horz.count(pii(a, b)));
    return 'h';
  };
  vector<string> g(n,string(n,'?'));
  rep(i,0,n) rep(j,0,n) g[i][j] = get(i,j);
  vector<pii> ans;
  rep(i,0,n) {
    if(g[i] == string(n,'v')) {
      vector<pii> ans2;
      rep(j,0,n) ans2.emplace_back(i,j);
      answer(ans2);
    }
    else {
      rep(j,0,n) if(g[i][j] == 'h') {
        ans.emplace_back(i,j);
        break;
      }
    }
  }
  answer(ans);
}
