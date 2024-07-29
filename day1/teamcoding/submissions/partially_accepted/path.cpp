#include<bits/stdc++.h>

using namespace std;
typedef vector<int> vi;

signed main(){
	int n,k;
	cin >> n >> k;
	
	vi col(n,0);

	for(int i=0;i<n;++i){
		int c;
		cin >> c;
		col[c]++;
	}
	cout << *max_element(col.begin(),col.end())<< ' '<< 0;

}
