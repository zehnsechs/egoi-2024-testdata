#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
typedef vector<int> vi;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  int n;
  cin>>n;
  vi l(n),r(n),dp(n);
  rep(i,0,n) cin>>l[i]>>r[i];
  map<int,int> mx; // mx[i] = dp[i] if active; only keep increasing subsequence
  mx[-1e9] = 0;
  vector<vi> delay(n+1);
  rep(i,0,n) {
    for(int j : delay[i]) {
      auto it = mx.lower_bound(j);
      if(prev(it)->second > dp[j]) continue;
      while(it != end(mx) && it->second <= dp[j]) mx.erase(it++);
      mx[j] = dp[j];
    }
    dp[i] = 1 + prev(mx.lower_bound(i-l[i]))->second;
    delay[min(n,i+r[i]+1)].emplace_back(i);
  }
  cout << *max_element(all(dp)) << endl;
}
