//@EXPECTED_GRADES@ TLE AC AC AC TLE

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

  vi level(n), is_root(n);
  {
    vi col_parent(n,-1);
    function<void(int)> dfs = [&](int x) {
      int cp = col_parent[c[x]];
      col_parent[c[x]] = x;
      for(int y : g[x]) {
        level[y] = level[x]+1;
        dfs(y);
      }
      col_parent[c[x]] = cp;
      if(cp == -1) is_root[x] = true;
    };
    dfs(0);
  }

  int best = 0;
  vi bests;


  vector<map<int,int>> col_at_lev(n);
  rep(i,0,n) ++col_at_lev[c[i]][level[i]];

  {
    vector<vi> below(n);
    function<void(int)> dfs = [&](int x) {
      for(int y : g[x]) {
        dfs(y);
        if(sz(below[y]) > sz(below[x]))
          swap(below[x], below[y]);
        rep(i,0,sz(below[y]))
          below[x][sz(below[x])-1-i] += below[y][sz(below[y])-1-i];
      }

      below[x].emplace_back(1);
      if(!is_root[x]) return;

      // process x in O(min(subtree, color)) time
      int ans = 1;
      for(auto it = col_at_lev[c[x]].upper_bound(level[x]);
          it != end(col_at_lev[c[x]]); ++it) {
        auto [lev,cnt] = *it;
        int idx = sz(below[x]) - (lev - level[x]) - 1;
        if(idx < 0) break;
        ans += min(below[x][idx], cnt);
      }
      if(best < ans) {
        bests.clear();
        best = ans;
      }
      if(best == ans) bests.emplace_back(x);
    };
    dfs(0);
  }

  // the solution finds all potential answers,
  // but is slow at handling ties to compute the second output number
  int best2 = 0;
  for(auto root : bests) {
    int already = 0;
    function<void(int)> dfs = [&](int x) {
      if(c[x] == c[root]) ++already;
      for(int y : g[x]) dfs(y);
    };
    dfs(root);
    best2 = max(best2,already);
  }

  cout << best << " " << best - best2 << endl;
}
