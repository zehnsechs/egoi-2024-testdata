#include<bits/stdc++.h>
using namespace std;
typedef vector<int> vi;

signed main(){
	cin.tie(0)->sync_with_stdio(false);

	int n,k;
	cin >> n >> k;
	if(k>2) return 0;

	vi cols(n);
	vi col_counts(2,0);
	for(int i=0;i<n;++i){
		cin >> cols[i];
		col_counts[cols[i]]++;
	}

	cout << col_counts[cols[0]] << ' ' << 0;
	
	
}
