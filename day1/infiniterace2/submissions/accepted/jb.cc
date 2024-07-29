#include <bits/stdc++.h>
using namespace std;

int main() {
  int n,q, last_lap = 0, ans = 0, x;
  cin>>n>>q;
  vector<int> last_overtake(n,-1);
  for(int i = 0; i < q; ++i) {
    cin>>x;
    if(x > 0) {
      if(last_overtake[x] >= last_lap) ++ans, last_lap = i;
      last_overtake[x] = i;
    }
    else last_overtake[-x] = -1;
  }
  cout << ans << endl;
}
