//@EXPECTED_GRADES@ AC AC AC AC TLE
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define debug(...) //ignore
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef long double ld;

const int MAXN = 100'123;
int c[MAXN];
int cc_at_lev[MAXN];
int level[MAXN];

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  int n, k;
  cin>>n>>k;
  rep(i,0,n) cin>>c[i];
  vector<vi> g(n);
  bool is_path = true;
  rep(x,1,n) {
    int p;
    cin>>p;
    if(p != x-1) is_path = false;
    g[p].emplace_back(x);
  }

  auto solve_path = [&]{
    // solve paths seperately, since they can be
    // worst case for the running time otherwise
    vi cnt(k);
    rep(x,0,n) ++cnt[c[x]];
    cout << *max_element(all(cnt)) << " " << 0 << endl;
    exit(0);
  };
  if(is_path) solve_path();


  vi is_root(n);
  vi dfs_in(n), dfs_out(n), dfs_ord(n);
  {
    level[0] = 0;
    vi seen(n);
    int T = 0;
    function<void(int)> dfs = [&](int x) {
      dfs_ord[T] = x;
      dfs_in[x] = T++;
      if(seen[c[x]] == 0) is_root[x] = 1;
      ++seen[c[x]];
      for(int y : g[x]) {
        level[y] = level[x]+1;
        dfs(y);
      }
      --seen[c[x]];
      dfs_out[x] = T;
    };
    dfs(0);
  }
  pii best = {1,0};


  // first we relabel the nodes by their dfs order, to decrease cache misses
  {
    vi c2(all(c));
    vi level2(all(level));
    vi is_root2 = is_root;
    vi dfs_out2 = dfs_out;
    rep(i,0,n) {
      c[i] = c2[dfs_ord[i]];
      level[i] = level2[dfs_ord[i]];
      is_root[i] = is_root2[dfs_ord[i]];
      dfs_out[i] = dfs_out2[dfs_ord[i]];
    }
  }

  vi has_col(k);
  rep(x,0,n) ++has_col[c[x]];

  // we also renumber the colors based on heavy to light
  {
    vi cols(k);
    iota(all(cols),0);
    sort(all(cols),[&](int x, int y){ return has_col[x] > has_col[y]; });
    vi inv_cols(k);
    rep(i,0,k) inv_cols[cols[i]] = i;
    rep(x,0,n) c[x] = inv_cols[c[x]];
  }

  fill(all(has_col),0);
  rep(x,0,n) ++has_col[c[x]];

  vector<vi> by_color(k);
  rep(i,0,n) by_color[c[i]].emplace_back(i);

  vi cand;
  rep(i,0,n) if(is_root[i]) cand.emplace_back(i);
  sort(all(cand),[&](int x, int y){return c[x] < c[y];});

  int cc = -1;
  for(int root : cand) {

    // skip if cannot improve
    int extra = (best.first == best.second ? 1 : 0);
    if(dfs_out[root] - root < best.first+extra) continue;
    if(has_col[c[root]] < best.first+extra) continue;

    if(cc != c[root]) {
      if(cc != -1) for(int i : by_color[cc]) --cc_at_lev[level[i]];
      cc = c[root];
      for(int i : by_color[cc]) ++cc_at_lev[level[i]];
    }

    int ans = 1;
    int already = 1;

    // the below are the only place taking O(n^2) time
    // they have very few cache misses due to the reorderings
    const int lim = dfs_out[root];
    rep(x,root+1,lim) {
      if(c[x] == cc) ++already;
      if(cc_at_lev[level[x]]-- > 0) ++ans;
    }
    rep(x,root+1,lim) {
      ++cc_at_lev[level[x]];
    }
    best = max(best, {ans, already});
  }

  cout << best.first << " " << best.first-best.second << endl;
}
