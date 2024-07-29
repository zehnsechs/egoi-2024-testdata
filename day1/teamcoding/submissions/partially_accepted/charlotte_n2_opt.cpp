#include<bits/stdc++.h>

using ll = long long;
using namespace std;
using vi = vector<int>;




void solve_levels(int v, int p, vector<vi>& adj, vi& levels, int d){
  levels[d]++;  
  for(int w:adj[v]){
      if(w==p) continue;
      solve_levels(w,v,adj,levels,d+1);  
  }
} 

void solve_colors(int v,int p, vector<vi>& adj,vi& col,vi& col_count,int c,int d,vi& vis){
    if(col[v]==c) {
	    col_count[d]++;
    	    vis[v] =1;
    }
    for(int w:adj[v]){
      if(w==p) continue;
      solve_colors(w,v,adj,col,col_count,c,d+1,vis);
    }
}

void parent(int v,int p, vector<vi>& adj, vi& parents, vi& level){
  parents[v]=p;
  if(p>-1)
  	level[v]=level[p]+1;
  for(int w:adj[v]){
    if(w==p) continue;
    parent(w,v,adj,parents,level);
  }
}
int main(){
    cin.tie(0)->sync_with_stdio(false);

    int n,k;
    cin>> n >> k;
    //cerr << n << ' ' << k << '\n';   
    vi col(n);
    vector<vi> adj(n);
    

    for(int i = 0;i<n;++i){
      cin >> col[i];
    }
    //cerr << "cols done"<< '\n';
    
    for(int i=0;i<n-1;++i){
      int u,v;
     cin >> u;
     v=i+1;
    adj[u].push_back(v);
    adj[v].push_back(u);
    //cerr << u << ' ' << u << '\n'; 
    }
  
    vi v_level(n+1,0);
    vi parents(n,-1);
    parent(0,-1,adj,parents,v_level);

    vector<vi> col_count(n,vi(n+1,0));
    vi vis_fake(n,0); //not used for anything
    for(int i=0;i<n;++i){
   	 solve_colors(0,-1,adj,col,col_count[i],i,0,vis_fake);
    }
    int max_val = 0;
    int max_sw = 0;
    vi vis(n);
    for(int i = 0;i<n;++i){
	if(vis[i]) continue;
   	//cerr << "Vertex " << i << " depth " << v_level[i]<< " parent " << parents[i]<<'\n';
	vi v_col(n,0);
	vi v_lev(n+1,0);
	solve_colors(i,parents[i],adj,col,v_col,col[i],v_level[i],vis);
	solve_levels(i,parents[i],adj,v_lev,v_level[i]);
	
	int val = 0;
	int swaps=0;
	int d = v_level[i];
	while(v_lev[d]>0){
		int add = min(v_lev[d],col_count[col[i]][d]);
		val += add;
		swaps += add-v_col[d];	
	//cerr << i << ' ' << d << ' ' << v_lev[d] << ' ' <<col_count[col[i]][d] << ' '<<v_col[d] <<'\n';
		++d;
	}
	if(val>max_val){
		max_val=val;
		max_sw = swaps;
	} 
	if(val==max_val) 
		max_sw = min(max_sw,swaps);
		
	
    }

    cout << max_val << ' ' << max_sw<< '\n';
    


}
