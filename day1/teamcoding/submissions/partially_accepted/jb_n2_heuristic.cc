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

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  int n, k;
  cin>>n>>k;
  vi c(n);
  rep(i,0,n) cin>>c[i];
  vector<vi> g(n);
  rep(x,1,n) {
    int p;
    cin>>p;
    g[p].emplace_back(x);
  }

  vi level(n);
  vi is_root(n);
  vi subtree(n);
  vi dfs_in(n), dfs_out(n), dfs_ord(n);
  {
    vi seen(n);
    int T = 0;
    function<void(int)> dfs = [&](int x) {
      dfs_ord[T] = x;
      dfs_in[x] = T++;
      if(seen[c[x]] == 0) is_root[x] = 1;
      ++seen[c[x]];
      subtree[x] = 1;
      for(int y : g[x]) {
        level[y] = level[x]+1;
        dfs(y);
        subtree[x] += subtree[y];
      }
      --seen[c[x]];
      dfs_out[x] = T;
    };
    dfs(0);
  }

  vi has_col(k);
  rep(i,0,n) ++has_col[c[i]];

  pii best = {-1e9,-1e9};

  // we will pick lots of candidate vertices to process later
  // we select these by quite a few different heuristics
  vi cand;

  // select the 50 first and last vertices
  {
    rep(x,0,min(50,n)) {
      cand.emplace_back(x);
      cand.emplace_back(n-1-x);
    }
  }

  // select the first and last 20 colors
  {
    rep(cc,0,20) {
      rep(x,0,n) if(is_root[x] && (c[x]==cc || c[x]==k-1-cc)) cand.emplace_back(x);
    }
  }

  // select the 200 roots of largest subtree size
  {
    vi verts;
    rep(i,0,n) if(is_root[i]) verts.emplace_back(i);
    sort(all(verts),[&](int x, int y){ return subtree[x] > subtree[y]; });
    verts.resize(min(200,sz(verts)));
    for(int v : verts) cand.emplace_back(v);
  }

  // select all roots of the 200 heaviest colors
  {
    vi cols(k);
    rep(i,0,n) ++cols[c[i]];
    vi which_cols(k);
    iota(all(which_cols),0);
    sort(all(which_cols),[&](int x, int y){ return cols[x] > cols[y]; });
    which_cols.resize(min(200,sz(which_cols)));
    for(int cc : which_cols) {
      rep(x,0,n) if(is_root[x] && c[x]==cc) cand.emplace_back(x);
    }
  }

  vi done(n);
  auto go = [&](vi cand) {
    sort(all(cand),[&](int x, int y){ return c[x] < c[y]; });
    int cc = -1;
    vi cc_at_lev(n);
    for(int root : cand) {
      if(done[root]) continue;
      done[root] = true;

      // skip if cannot improve
      int extra = (best.first == best.second ? 1 : 0);
      if(dfs_out[root] - dfs_in[root] < best.first+extra) continue;
      if(has_col[c[root]] < best.first+extra) continue;

      if(cc != c[root]) {
        cc = c[root];
        fill(all(cc_at_lev),0);
        rep(i,0,n) if(c[i] == cc) ++cc_at_lev[level[i]];
      }

      int ans = 0;
      int already = 0;
      rep(i,dfs_in[root],dfs_out[root]) {
        int x = dfs_ord[i];
        if(c[x] == cc) ++already;
        if(cc_at_lev[level[x]]-- > 0) ++ans;
      }
      rep(i,dfs_in[root],dfs_out[root]) {
        int x = dfs_ord[i];
        ++cc_at_lev[level[x]];
      }
      best = max(best, {ans, already});
    }
  };

  // use the heuristic to find a "kind of good answer"
  go(cand);
  debug(best.first);

  // now process all nodes, but we can skip things
  // if we surely cannot improve on the "kind of good answer"
  vi cand2;
  rep(i,0,n) if(is_root[i]) cand2.emplace_back(i);
  go(cand2);

  cout << best.first << " " << best.first-best.second << endl;
}
