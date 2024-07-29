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

  auto printgrid = [&](vector<pii> v, vector<pii> v2 = {}) {
    vector<string> grid(n,string(n,'0'));
    for(auto [a,b] : v) grid[a][b] = '1';
    for(auto [a,b] : v2) grid[a][b] = '1';
    for(auto g : grid) cout << g << ' ' << endl;
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
    //cerr << "know " << p.first << " " << p.second << " " << c << endl;;
    if(c == 'h') rows.erase(find(all(rows),p.first)), h.emplace_back(p);
    if(c == 'v') cols.erase(find(all(cols),p.second)), v.emplace_back(p);
    if(sz(rows) == 0) answer(h);
    if(sz(cols) == 0) answer(v);
  };

  auto binary_search_row = [&](int r, char c_same, char c_diff, auto& COLS, auto& H){
    vector<pii> q;
    if(c_same == 'h') for(int i : COLS) q.emplace_back(r,i);
    else for(int i : COLS) q.emplace_back(i,r);
    int t = query(q);
    if(t == sz(q)*n) {
      for(auto p : q) know(p,c_diff);
      return;
    }
    while(sz(q) >= 3) {
      vector<pii> a,b;
      for(auto p : q) {
        swap(a,b);
        a.emplace_back(p);
      }
      assert(sz(a) >= 2);
      int t = query(a);
      if(t == sz(a)*n) {
        for(auto p : a) know(p,c_diff);
        q = b;
      }
      else if(t == n) {
        know(a[0],c_same);
        return;
      }
      else q = a;
    }
    if(sz(q) == 2) {
      assert(sz(H));
      if(query({H[0],q[0]}) == 2*n) {
        know(q[0],c_same);
        return;
      }
      else {
        know(q[1],c_same);
        return;
      }
    }
    know(q[0],c_same);
  };

  mt19937_64 rng(31);
  {
    auto r = rng()%n, c1 = rng()%n, c2 = rng()%n, c3 = rng()%n;
    while(c2 == c1) c2 = rng()%n;
    while(c3 == c1 || c3 == c2) c3 = rng()%n;
    pii p1 = {r,c1}, p2 = {r,c2}, p3 = {r,c3};
    int a = query({p1, p2, p3});
    if(a == 3*n) know(p1,'v'), know(p2,'v'), know(p3,'v');
    else if(a == n) know(p1,'h');
    else {
      int b = query({p2,p3});
      if(a == 3*n-2 && b == 2*n-1) {
        know(p1,'v');
        if(query({p1,p2}) == 2*n) know(p2,'v'), know(p3,'h');
        else know(p2,'h'), know(p3,'v');
      }
      else if(a == 3*n-2 && b == 2 * n){
        know(p1,'h');
        know(p2,'v');
        know(p3,'v');
      }
      else if(a == 2*n-1 && b == n) {
        know(p1,'v');
        know(p2,'h');
      }
      else if(a == 2*n-1 && b == 2*n-1) {
        know(p1,'h');
      }
      else assert(false);
    }
  }


  while(true) {
    shuffle(all(rows),rng);
    shuffle(all(cols),rng);
    //cerr << sz(rows) << " " << sz(cols) << " used " << Q << " " << fixed << setprecision(2) << (2*n-sz(rows)-sz(cols))/ld(Q) << endl;

    if(sz(rows) <= 3 && sz(cols) >= 10) {
      binary_search_row(rows.back(),'h','v',cols,h);
      continue;
    }
    if(sz(cols) <= 3 && sz(rows) >= 10) {
      binary_search_row(cols.back(),'v','h',rows,v);
      continue;
    }

    vector<pii> cand;
    rep(i,0,min(sz(rows),sz(cols))) cand.emplace_back(rows[i],cols[i]);

    char c_same = sz(h) > sz(v) ? 'h' : 'v';
    char c_diff = c_same^'h'^'v';
    vector<pii> q = (c_same == 'h' ? h : v);

    int k = min({sz(q), sz(cand), 10});

    vector<pii> ca;
    while(sz(ca) < k) {
      ca.emplace_back(cand.back());
      cand.pop_back();
    }

    vector<ll> valid;
    rep(msk,0,1<<k) valid.emplace_back(msk);
    while(sz(valid) > 1) {
      rep(b,0,k) {
        int c0 = 1, c1 = 1;
        for(auto a : valid) {
          c0 &= ~((a>>b)&1);
          c1 &= (a>>b)&1;
        }
        assert(c0 + c1 <= 1);
        if(c0) know(ca[b],c_diff);
        if(c1) know(ca[b],c_same);
        if(c0||c1) {
          ca.erase(begin(ca)+b);
          --k;
          for(auto &a : valid) {
            a = (a&((1LL<<b)-1)) | ((a>>(b+1))<<b);
          }
          c_same = sz(h) > sz(v) ? 'h' : 'v';
          if(c_same == c_diff) for(auto &a : valid) {
            a = (~a)&((1LL<<k)-1);
          }
          c_diff = c_same^'h'^'v';
          q = (c_same == 'h' ? h : v);
          //for(int i : rows) for(int j : cols) {
          //  bool ok = true;
          //  for(auto [r,c] : cand) if(i == r || j == c) ok = false;
          //  for(auto [r,c] : ca) if(i == r || j == c) ok = false;
          //  if(ok) cand.emplace_back(i,j);
          //}
        }
      }
      while(sz(valid) < 1e4 && sz(cand) && k < sz(q) && k < 60 && sz(rows) >= 4 && sz(cols) >= 4) {
        ca.emplace_back(cand.back());
        cand.pop_back();
        vector<ll> valid2 = valid;
        for(auto a : valid) valid2.emplace_back(a|(1LL<<k));
        swap(valid,valid2);
        ++k;
      }

      pair<ll,ll> best = {-1e18,0};
      rep(_,0,200) {
        ll msk = rng()%(1LL<<k);
        vector<ll>cnt(k+1);
        for(auto a : valid) ++cnt[__builtin_popcountll(msk&a)];
        ll mx = 0;
        //for(auto a : cnt) mx = max(mx,a);
        //for(auto a : cnt) if(a == mx) ++mx;
        for(auto a : cnt) mx += a*a;
        mx = mx * *max_element(all(cnt));
        //mx = *max_element(all(cnt));
        best = max(best, pair<ll,ll>{-mx, msk});
      }
      ll msk = best.second;
      vector<pii> ca2;
      rep(i,0,k) if(msk>>i&1) ca2.emplace_back(ca[i]);
      int t = query(q,ca2);
      int count = -1;
      rep(a,0,__builtin_popcountll(msk)+1) {
        int b = __builtin_popcountll(msk)-a;
        if(t == (sz(q)+a+b)*n - (sz(q)+a)*b) { assert(count == -1); count = a; }
      }
      assert(count != -1);
      vector<ll> valid2;
      for(auto a : valid) if(__builtin_popcountll(msk&a) == count) valid2.emplace_back(a);
      swap(valid,valid2);
    }

    assert(sz(valid) == 1);
    rep(i,0,k) know(ca[i], (valid[0]>>i&1) ? c_same : c_diff);
  }
}
