//when doing binary search does not calculate the total number correctly when switching sides

#include<bits/stdc++.h>

using namespace std;
typedef vector<int> vi;
typedef pair<int,int> pii;

int n;

template <typename Iterator>
int query(Iterator begin,Iterator end){
	cout << '?' <<'\n';
	vector<string> grid(n,string(n,'0'));
	for(Iterator it=begin; it != end;++it ){
		grid[it->first][it->second]='1';
	}	
	for(string s:grid){
		cout << s <<'\n'; 
	}
	cout << flush;
	int res;
	cin >> res;
	return res;
}

void answer(vector<pii>& lamps){
	cout << '!' <<'\n';
	vector<string> grid(n,string(n,'0'));
	for(auto [r,c]: lamps){
		grid[r][c]='1';
	}	
	for(string s:grid){
		cout << s <<'\n'; 
	}

	cout << flush;
}



int bs(int index, char rc, bool is_col, vi indices){
	vector<pii> q;
	for(int i: indices){
		if(rc == 'r'){
			q.push_back({index,i});
		} else {
			q.push_back({i,index});
		}
	}
	int tot = query(q.begin(),q.end());
	if(tot == indices.size()*n)
		return -1;
	if(tot == n){
		return *indices.begin();
	}
	int tot_num = tot/n - (tot==n?1:0);
	//cerr << tot_num << '\n';
	int l=0, u=indices.size();
	while(l != u-2){
		int m = (l+u)/2 +(l+u)%2;
		int res = query(q.begin()+l,q.begin()+m);	
		res = res/n - (res==n?1:0);
		//cerr<< res << ' ' << '\n';
		if(res == 0)
			return *(indices.begin()+l);
		if(res == tot_num)
			return *(indices.begin()+u-1);
		if(res > tot_num/2)
			l = m;
		else 
			u = m;
//this is not the correct way to do it
		tot_num = res;

	}
	vector<pii> q2 = {{0,0}};
	q2.push_back(*(q.begin()+l));
	int res=query(q2.begin(),q2.end());
	if(res == 2*n && ((rc == 'c' && is_col) || (rc =='r' && !is_col))) return *(indices.begin()+l);
	return *(indices.begin()+l+1);
}

signed main(){
	cin >> n;

	vector<pii> q = {{0,0},{0,1},{0,2}};
	int res = query(q.begin(),q.end());
	bool is_col=true;
	if(res == n) is_col = false;
	else if(res ==2*n-1 || res == 3*n-2){
		int res2 = query(q.begin()+1,q.end());
		if((res == 2*n-1 && res2 == 2*n-1) || (res == 3*n-2 && res2 == 2*n)) is_col=false;
	}
	//cerr << is_col << '\n';
	vector<pii> res_v;
	res_v.push_back({0,0});
	for(int i=1;i<n;++i){
		vi indices(n);
		iota(indices.begin(),indices.end(),0);
		char rc = is_col?'c':'r';
		int res = bs(i,rc,is_col,indices);
		//cerr << res << '\n';
		if(res ==-1) {
			if(rc == 'c'){
				vector<pii> row;
				for(int j=0;j<n;++j) row.push_back({j,i});
				answer(row);
				return 0;
			}
			vector<pii> col;
			for(int j=0;j<n;++j) col.push_back({i,j});
			answer(col);
			return 0;
		}
		pii r;
		rc=='c'? r={res,i}:r={i,res};
		res_v.push_back(r);

	}

	answer(res_v);
	return 0;
}

