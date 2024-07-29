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
    cout << "?" << ' ';
    printgrid(v);
    int x;
    cin >> x;
    return x;
  };
  auto answer = [&](vector<pii> v) {
    assert(sz(v) == n);
    cout << "!" << ' ';
    printgrid(v);
    exit(0);
  };

  vector<pii> ans;
  rep(i,0,n) {
    vector<pii> q;
    rep(j,0,n) q.emplace_back(i,j);
    int k = query(q);
    if(k == n*n) answer(q);
    if(k == n) q = {q[0]};
    while(sz(q) >= 3) {
      vector<pii> a, b;
      for(auto p : q) {
        swap(a,b);
        a.emplace_back(p);
      }
      assert(sz(a) >= 2);
      int k = query(a);
      if(k == n) { q = {a[0]}; break; }
      if(k < sz(a)*n) q = a;
      else q = b;
    }
    if(sz(q) == 2) {
      if(sz(ans)) {
        if(query({ans[0],q[0]}) == 2*n) q = {q[0]};
        else q = {q[1]};
      }
      else {
        pii t = {i,0};
        while(t == q[0] || t == q[1]) ++t.second;
        int k0 = query({q[0],t});
        if(k0 == 2*n) q = {q[1]};
        else if(k0 == n) q = {q[0]};
        else {
          int k1 = query({q[1],t});
          if(k1 == 2*n) q = {q[0]};
          else q = {q[1]};
        }
      }
    }
    assert(sz(q) == 1);
    ans.emplace_back(q.back());
  }
  answer(ans);
}
