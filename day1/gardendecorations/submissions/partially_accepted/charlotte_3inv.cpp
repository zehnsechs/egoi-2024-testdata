#include<bits/stdc++.h>

using namespace std;
typedef vector<int> vi;

int main(){
	int k,n;
	cin >> k >> n;
	if(k==0) {
		cout << 3<< endl;
		return 0;
	}
	vi target(n);
	vi source(n);
	for(int j=0;j<n;++j){
		int e;
		cin >> e;
	        target[j]=e;	
		source[e]=j;
	}
	
	vi a(n);
	vi y(n);
	vi z(n,0);

	
	for(int i=0;i<n;++i){
		int cur = i;
		while(source[cur] > i) {
			cur = source[cur];
		}
		a[i] = cur;
	}

	for(int i=0;i<n;++i) {
		int cur = i;
		while(target[cur]>i) {
			cur = target[cur];
		}
		if(target[cur] == i && target[i]>i) z[i]=1;
		y[i] = cur;
		cerr <<"i " << i << " yi "<< y[i] << " z "<<z[i]<<'\n';
	}	
	

	if(k==1){
		vector<bool> b(n);
		for(int i=0;i<n;++i) {
			bool bi;
			cin >> bi;
			b[i]=bi;
			bool res;
			if(source[a[i]] ==i )
				res = b[i];
		       	else{
			       	res = b[i]^b[source[a[i]]];
				cerr << source[a[i]] << " -> " << i << '\n';
		        
			}
			cout << res << endl;	
		}
	}

	if(k==2){
		vector<bool> b(n);
		for(int i=n-1;i>=0;--i){
			bool bi;
			cin >> bi;
			b[i] = bi;
			int pi = target[i];
			while(pi > i){

				b[i] = b[i]^ b[pi];
				cerr << pi << " -> " << i << '\n';
				pi = target[y[pi]];
			}
		
			int qi = a[i];
			while(qi > i && !z[i]){
				b[i]=b[i]^b[qi];
				cerr << qi << " -> " << i << '\n';
				qi = target[y[qi]];
			}
			cout << b[i]<<endl;
		}
	}

	if(k==3){
		vector<bool> b(n);
		for(int i=0;i<n;++i){
			bool bi;
			cin >> bi;
			b[i] = bi;
			if(target[y[i]]!=i) {
				b[i] = b[i]^ b[target[y[i]]];		
				cerr << target[y[i]] << " -> " << i << '\n';
			}
			cout << b[i]<<endl;
		}
	}

}
