#include<bits/stdc++.h>

using namespace std;
typedef vector<int> vi;


void dfs(int v, int p,vector<vi>& adj, vi& level,vi& order){
  if(v!= 0)
  	level[v]=level[p]+1;
  for(int w:adj[v]){
    dfs(w,v,adj,level,order);
  }
  order.push_back(v);
}
void col_tree(int v, int p, vector<vi>& adj, vi& col, vector<vi>& col_adj, vi& cur_p,vector<queue<int>>& col_root) {
	if(cur_p[col[v]] == -1) {
		col_root[col[v]].push(v);
	} else {
		col_adj[cur_p[col[v]]].push_back(v);
	}
	int old = cur_p[col[v]];
	cur_p[col[v]] = v;
	for(int w:adj[v]){
		if(w==p) continue;
		col_tree(w,v,adj,col,col_adj,cur_p,col_root);
	}
	cur_p[col[v]] = old;

}



signed main(){
	cin.tie(0)-> sync_with_stdio(false);
	int n,k;
	cin >> n >> k;

	vi col(n);
	vector<vi> col_v(k);
	for(int i=0;i<n;++i){
		cin >> col[i];
		col_v[col[i]].push_back(i);
	}
	
        vector<vi> adj(n);
	for(int i=0;i<n-1;++i){
		int u,v;
		u = i+1;
		cin >> v;
		adj[v].push_back(u);
	}
        vi order;
	vi v_level(n,0);
        dfs(0,-1,adj,v_level,order);        


	vector<vi> col_adj(n);
	vector<queue<int>> col_root(k);
	vi col_p(k,-1);

	col_tree(0,-1,adj,col,col_adj, col_p, col_root);
	cerr << "coltree solved" <<'\n';


	vector<unordered_map<int,int>> col_count(k);
	for(int i=0;i<n;++i){
		auto  search = col_count[col[i]].find(v_level[i]);
		if(search == col_count[col[i]].end()) col_count[col[i]][v_level[i]]=1;
		else search->second++;
	}

	int val = 0;
	int swaps = 0;
	
	cerr << " starting" << '\n';
        vector<deque<int>>  counts(n);        
        for(int v: order){
            //cout << "vertex " << v << '\n';
            for(int w:adj[v]){
	       	if(counts[w].size() > counts[v].size()) swap(counts[w],counts[v]);
		for(int i=0;i<counts[w].size();++i){
			counts[v][i]+=counts[w][i];
		}
	    }
	    counts[v].push_front(1);
        
            //if v is not color root, skip it
            if(v != col_root[col[v]].front()) continue;
            //cout << v << '\n';
            col_root[col[v]].pop();
        
            
            
            int v_val = 0;
            int v_swaps = 0;
            vi col_lev(n,0);
            vi vis(n,0);
            queue<int> q;
            q.push(v);

            while(!q.empty()){
                    int u = q.front();
                    q.pop();
                    if(v_level[u]<v_level[v]){
                            //cerr << u << ' ' << v_level[u] << '\n';
                            assert(false);
                    }
                    col_lev[v_level[u]]++;
                    for(int w:col_adj[u]) q.push(w);
            }

            for(int u : col_v[col[v]]){
                    //cout << "clv" << u << '\n';
                    int d = v_level[u];
                    if(vis[d]) continue;
                    vis[d]=1;
                    if(d<v_level[v] || d > v_level[v]+counts[v].size()-1) continue;
                    //cout << "root " << v << " level " << d << " col count " << col_count[col[v]][d]<< " level count " << counts[v][d-v_level[v]]<<'\n';
                    int d_val= min(counts[v][d-v_level[v]],col_count[col[v]][d]);
                    v_val += d_val;
                    v_swaps += d_val-col_lev[d];
            }
            if(v_val>val){
                    val=v_val;
                    swaps=v_swaps;
            }
            if(val==v_val)
                    swaps = min(v_swaps,swaps);


    }
            
        

    cout << val << ' ' << swaps<<'\n';

}
