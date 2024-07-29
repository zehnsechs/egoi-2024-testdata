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

  auto _query = [&](vector<pii> v) {
    vi V(n),H(n);
    auto hsh = [&](int x, int y) { return (31312*ll(x)*y+1223*x+y*13)%133%2; };
    for (auto [a, b] : v) (hsh(a,b) ? ++V[a] : ++H[b]);
    return n*n - count(all(V),0)*count(all(H),0);
  };
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

  vector<pii> v, q;
  rep(i,0,n) rep(j,0,n) v.emplace_back(i,j);

  int remove = n*n-10*n;
  mt19937 rng(12);
  while(sz(v) > n) {
    remove = max(1,min(remove, sz(v)-n));
    shuffle(all(v),rng);
    q.assign(begin(v),end(v)-remove);
    if(query(q) == n*n) { v = q; remove = 1.1*remove; }
    else remove = remove*0.8;
  }
  assert(sz(v) == n);
  answer(v);
}
