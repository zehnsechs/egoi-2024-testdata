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

  auto printgrid = [&](vector<pii> v, vector<pii> v2 = {}) {
    vector<string> grid(n,string(n,'0'));
    for(auto [a,b] : v) grid[a][b] = '1';
    for(auto [a,b] : v2) grid[a][b] = '1';
    for(auto g : grid) cout << g << endl;
  };
  auto query = [&](vector<pii> v, vector<pii> v2 = {}) {
    cout << "?" << endl;
    printgrid(v,v2);
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

  vector<pii> h, v;
  vi rows(n), cols(n);
  iota(all(rows),0);
  iota(all(cols),0);
  auto know = [&](pii p, char c) {
    if(c == 'h') rows.erase(find(all(rows),p.first)), h.emplace_back(p);
    if(c == 'v') cols.erase(find(all(cols),p.second)), v.emplace_back(p);
    if(sz(rows) == 0) answer(h);
    if(sz(cols) == 0) answer(v);
  };

  {
    int a = query({{0, 0}, {0, 1}, {0, 2}});
    int b = query({{0, 1}, {0, 2}});
    set<pii> vert = {{3 * n, 2 * n}, {3 * n - 2, 2 * n - 1}, {2 * n - 1, n}};
    set<pii> horz = {{3 * n - 2, 2 * n}, {2 * n - 1, 2 * n - 1}, {n, n}};
    if (vert.count(pii(a, b))) know({0,0},'v');
    else if(horz.count(pii(a, b))) know({0,0},'h');
    else assert(false);
  }

  while(true) {
    // TODO: shuffle rows & cols?
    vector<pii> cand;
    rep(i,0,min(sz(rows),sz(cols))) cand.emplace_back(rows[i],cols[i]);
    while(sz(cand)) {
      char c_same = sz(h) > sz(v) ? 'h' : 'v';
      char c_diff = c_same^'h'^'v';
      vector<pii> q = (c_same == 'h' ? h : v);

      // try some different strategies

      if(sz(q) >= 2 && sz(cand) >= 2) {
        pii p1 = cand.back();
        cand.pop_back();
        pii p2 = cand.back();
        cand.pop_back();
        int t = query(q,{p1,p2});
        if(t == (sz(q)+2)*n) know(p1,c_same), know(p2,c_same);
        else if(t == (sz(q)+2)*n - 2*sz(q)) know(p1,c_diff), know(p2,c_diff);
        else if(t == (sz(q)+2)*n - sz(q)-1) {
          int t = query(q,{p1});
          if(t == (sz(q)+1)*n) know(p1,c_same), know(p2,c_diff);
          else if(t == (sz(q)+1)*n-sz(q)) know(p1,c_diff), know(p2,c_same);
          else assert(false);
        }
        else assert(false);
        continue;
      }

      if(sz(q) >= 1 && sz(cand) >= 1) {
        pii p = cand.back();
        cand.pop_back();
        int t = query(q,{p});
        if(t == (sz(q)+1)*n) know(p,c_same);
        else if(t == (sz(q)+1)*n-sz(q)) know(p,c_diff);
        else assert(false);
        continue;
      }
    }
  }
}
