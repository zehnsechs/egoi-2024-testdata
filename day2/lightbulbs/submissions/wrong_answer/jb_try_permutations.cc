#include <bits/stdc++.h>
#include <random>
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

  vi perm(n);
  iota(all(perm),0);

  mt19937 rng(42);
  while(true) {
    shuffle(all(perm),rng);
    vector<pii> q;
    rep(i,0,n) q.emplace_back(i,perm[i]);
    if(query(q) == n*n) answer(q);
  }
}
