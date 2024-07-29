#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define debug(...) //ignore
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef long double ld;

using ll = int; // should work without overflow

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  ll n,m,q;
  cin>>n>>m>>q;
  set<ll> s;
  rep(i,0,m) {
    ll x;
    cin>>x;
    s.emplace(x);
    s.emplace(x+n);
  }
  auto md = [&](ll x) { return (x%(2*n)+2*n)%(2*n); };
  auto go = [&](ll x, ll y) { return min(md(x-y),md(y-x)); };
  rep(i,0,q) {
    ll x, y;
    cin>>x>>y;
    ll ans = go(x,y);
    if(m > 0) {
      auto it = s.lower_bound(x);
      if(it == end(s)) it = begin(s);
      ans = min(ans, go(x, *it) + 1 + go(md(*it+n), y));
      it = prev(it == begin(s) ? end(s) : it);
      ans = min(ans, go(x, *it) + 1 + go(md(*it+n), y));
    }
    cout << ans << endl;
  }
}
