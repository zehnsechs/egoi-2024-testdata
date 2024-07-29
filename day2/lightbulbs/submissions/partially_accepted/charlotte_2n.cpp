#include<bits/stdc++.h>

using namespace std;
typedef vector<int> vi;
typedef pair<int,int> pii;

int n;

int query(vector<pii>& lamps){
	cout << '?' <<'\n';
	vector<string> grid(n,string(n,'0'));
	for(auto [r,c]: lamps){
		grid[r][c]='1';
	}	
	for(string s:grid){
		cout << s <<'\n'; 
	}
	cout << endl;
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

	cout << endl;
}

signed main(){
	cin >> n;

	int r=0,c=0;
	
	vector<pii> one;
	vector<pii> rows;
	vector<pii> cols;
	
	
	int i=1;
	vector<pii> q = {{0,0},{i,i}};
	while(i<n && query(q)==2*n) {
		++i;
		q = {{0,0},{i,i}};
	}
	for(int j=0;j<i;++j){
		one.push_back({j,j});
	}
		
	if(i==n) {//all diagonals have same dir
		answer(one);
		return 0;
	}
	
	bool is_col = true;
	q ={{0,0},{i,0},{i,i}};
	int t = query(q);
	if(t ==2*n-1) swap(one,cols);
	else {
		swap(one,rows);
		is_col=false;
	}
	while(rows.size()<n && cols.size()<n){
		q = {{0,0},{rows.size(),cols.size()}};
		t = query(q);
		if((t==2*n && is_col) || (t ==2*n-1 && !is_col)) cols.push_back({rows.size(),cols.size()});
		else rows.push_back({rows.size(),cols.size()});
	}	

	if( cols.size()==n) answer(cols);
	else answer(rows);
	return 0;
}

