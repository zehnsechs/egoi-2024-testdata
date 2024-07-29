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

const int MAXN = 105;
int cnt[MAXN*MAXN];
mt19937 rng(31);

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


  vector<pii> h, v;
  vi rows(n), cols(n);
  iota(all(rows),0);
  iota(all(cols),0);
  auto know = [&](pii p, char c) {
    if(c == 'h' && count(all(rows),p.first)) {
      h.emplace_back(p);
      rows.erase(find(all(rows),p.first));
    }
    if(c == 'v' && count(all(cols),p.second)) {
      v.emplace_back(p);
      cols.erase(find(all(cols),p.second));
    }
    if(sz(rows) == 0) answer(h);
    if(sz(cols) == 0) answer(v);
  };



  using bs = bitset<205>;
  int k = 0;

  vector<pii> ca;
  vector<bs> valid;
  valid.emplace_back(0);
  vi active_row(n), active_col(n);

  while(true) {
    rep(b,0,k) {
      int c0 = 0, c1 = 0;
      for(auto a : valid) {
        if(a[b]) ++c1;
        else ++c0;
      }
      assert(c0 + c1);
      if(c1 == 0) know(ca[b],'v');
      if(c0 == 0) know(ca[b],'h');
      if(c0 == 0 || c1 == 0) {
        --active_row[ca[b].first];
        --active_col[ca[b].second];
        ca.erase(begin(ca)+b);
        for(auto &a : valid) rep(i,b,k) a[i] = a[i+1];
        --k;
        --b;
        unordered_set<bs> vv(all(valid));
        valid = vector<bs>(all(vv));
      }
    }


    while(sz(valid) < 1e3 && k < sz(rows) + sz(cols)) {
      shuffle(all(rows),rng);
      shuffle(all(cols),rng);
      //sort(all(rows),[&](int a, int b){return active_row[a] < active_row[b];});
      //sort(all(cols),[&](int a, int bd){return active_col[a] < active_col[b];});
      if(count(all(ca),pii(rows[0],cols[0]))) break;
      ca.emplace_back(rows[0],cols[0]);
      ++active_row[rows[0]];
      ++active_col[cols[0]];
      vector<bs> valid2;
      for(auto a : valid) {
        a[k] = 0;
        valid2.emplace_back(a);
        a[k] = 1;
        valid2.emplace_back(a);
      }
      swap(valid,valid2);
      ++k;
    }

    auto simulate = [&](bs a, bs on, int use_h) {
      vi vert(n), horz(n);
      rep(i,0,k) if(on[i]) {
        if(a[i]) horz[ca[i].first] = 1;
        else vert[ca[i].second] = 1;
      }
      if(use_h) for(auto [r,c] : h) horz[r] = 1;
      else for(auto [r,c] : v) vert[c] = 1;
      int vv = count(all(vert),1), hh = count(all(horz),1);
      return n*(vv+hh) - vv*hh;
    };

    ll best = 1e18;
    bs bestmsk = 0;
    int best_use_h = 0;
    vi probs = {100,90,80,70,60,40,30,20,10};
    while(sz(probs) < 50) probs.emplace_back(rng()%70+20);
    for(int prob : probs) {
      int use_h = rng()%2;
      bs on;
      rep(i,0,k) on[i] = (rng()%100 < prob);
      memset(cnt,0,sizeof cnt);
      for(auto a : valid) ++cnt[simulate(a,on,use_h)];
      ll mx = *max_element(all(cnt)); // try different heuristic, something like entropy?
      if(mx < best) {
        best = mx;
        bestmsk = on;
        best_use_h = use_h;
      }
    }
    vector<pii> ca2 = (best_use_h ? h : v);
    rep(i,0,k) if(bestmsk[i]) ca2.emplace_back(ca[i]);
    int t = query(ca2);
    vector<bs> valid2;
    for(auto a : valid) if(simulate(a,bestmsk,best_use_h) == t) valid2.emplace_back(a);
    swap(valid,valid2);
    assert(sz(valid));
  }
}
