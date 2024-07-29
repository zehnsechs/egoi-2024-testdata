#include <bits/stdc++.h>
using namespace std;

int main() {
  int n,q, ans = 0, x;
  cin>>n>>q;
  set<int> behind;
  for(int i = 0; i < q; ++i) {
    cin>>x;
    if(x > 0) {
      if(behind.count(x)) {
        ++ans;
        behind.clear();
      }
      behind.emplace(x);
    }
    else behind.erase(-x);
  }
  cout << ans << endl;
}
