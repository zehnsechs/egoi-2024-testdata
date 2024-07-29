#include<bits/stdc++.h>

using namespace std;
typedef vector<int> vi;

signed main(){
	int n,q;
	cin >> n >> q;

	vi behind(n,-1);
	int curr = 0;

	while(q--){
		int p;
		cin >> p;
		if(p>0){
			if(behind[p]!= curr) behind[p]=curr;
			else {
				curr++;
				behind[p]=curr;
			}
		} else {
			p *= -1;
			behind[p]=-1;
		}
	}
	cout << curr;

}
