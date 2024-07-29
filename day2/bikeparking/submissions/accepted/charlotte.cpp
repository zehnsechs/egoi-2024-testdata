#include<bits/stdc++.h>

using namespace std;
typedef vector<int> vi;

signed main(){
	cin.tie(0)-> sync_with_stdio(0);
	int n;
	cin >> n;
	vi people(n);
	vi spots(n);

	for(int i=0;i<n;++i){
		cin >> spots[i];
	}
	for(int i=0;i<n;++i){
		cin >> people[i];
	}

	int free = 0;
	int happy = 0;
	int ind = 0;
	int unhappy = 0;

	for(int i=0;i<n;++i){
		int inc = 0;
		//give free spots to people
		inc = min(free,people[i]);
		happy += inc;
		free -= inc;
		people[i] -= inc;
		//move indifferent people to make more happy
		inc = min(ind,people[i]);	
		happy += inc;
		unhappy += inc;
		ind -= inc;
		people[i] -= inc;
		//make people indiffernt if there is space (temp until kicked out)
		inc = min(spots[i],people[i]);
		ind += inc;
		spots[i] -= inc;
		people[i] -= inc;

		unhappy += people[i];
		free += spots[i];

		//cerr << i << " happy " << happy << " ind " << ind << " unhappy " << unhappy << '\n';
	}
	cout << happy - unhappy<< '\n';
}
