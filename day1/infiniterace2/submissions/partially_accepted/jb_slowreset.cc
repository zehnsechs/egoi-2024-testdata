// @EXPECTED_GRADES@ AC TLE AC TLE
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
  int n,q;
  cin>>n>>q;
  int ans = 0;
  vi behind(n,0);
  rep(i,0,q) {
    int x;
    cin>>x;
    if(x > 0) {
      if(behind[x]) {
        ++ans;
        behind.assign(n,0);
      }
      behind[x] = 1;
    }
    else behind[-x] = 0;
  }
  cout << ans << endl;
}
