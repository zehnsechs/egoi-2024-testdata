#include<bits/stdc++.h>

using namespace std;
typedef vector<int> vi;

#define sz(x) (int)x.size()

  
void solve(int v, vector<vi>& adj,vi& col,vi& col_count,int c, vi& levels,int d, vi& vis){
      vis[v]=1;
      if(d==sz(col_count)) col_count.push_back(0);
      if(col[v]==c) col_count[d]++;
      if(d==sz(levels)) levels.push_back(0);
      levels[d]++;  
      for(int w:adj[v]){
          solve(w,adj,col,col_count,c,levels,d+1,vis);
      }
}


void dfs(int v, int p,vector<vi>& adj, vi& level,vi& order){
    if(v!= 0)
        level[v]=level[p]+1;
    for(int w:adj[v]){
        dfs(w,v,adj,level,order);
    }
    order.push_back(v);
}

void col_tree(int v, int p, vector<vi>& adj, vi& col, vector<vi>& col_adj, vi& cur_p,vector<deque<int>>& col_root) {
    if(cur_p[col[v]] == -1) {
        col_root[col[v]].push_back(v);
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
    int split = 300;
    vi col(n);
    vector<vi> col_v(k);
    vi col_size(k,0);
    for(int i=0;i<n;++i){
        cin >> col[i];
        col_v[col[i]].push_back(i);
        col_size[col[i]]++;
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
    vector<deque<int>> col_root(k);
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
        for(int w:adj[v]){
            if(counts[w].size() > counts[v].size()) swap(counts[w],counts[v]);
            for(int i=0;i<sz(counts[w]);++i){
                counts[v][i]+=counts[w][i];
            }
        }
        counts[v].push_front(1);
        if (col_size[col[v]] < split) {
            //if v is not color root, skip it
            if(v != col_root[col[v]].front()) continue;
            col_root[col[v]].pop_front();
        
            int v_val = 0;
            int v_swaps = 0;
            unordered_map<int,int> col_lev;
            unordered_set<int> vis;
            queue<int> q;
            q.push(v);

            while(!q.empty()){
                int u = q.front();
                q.pop();
                if(v_level[u]<v_level[v]){
                    assert(false);
                }
                auto  search = col_lev.find(v_level[u]);
                if(search == col_lev.end()) col_lev[v_level[u]]=1;
                else search->second++;
                for(int w:col_adj[u]) q.push(w);
            }
            for(int u : col_v[col[v]]){
                int d = v_level[u];
                if(vis.find(d)!=vis.end()) continue;
                vis.insert(d);
                if(d<v_level[v] || d > v_level[v]+sz(counts[v])-1) continue;
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
    }
    cerr<< "starting heavy" <<'\n';           
    for(int i=0;i<k;++i){
        if(col_size[i]< split) continue;
        vi vis(n,0);
        for(int j=0;j< sz(col_root[i]);++j){
            int v = col_root[i][j];
            vi v_col;
            vi v_lev;
            solve(v,adj,col,v_col,col[v],v_lev,0,vis);
            v_lev.push_back(0);
            int v_val = 0;
            int v_swaps=0;
            int d = 0;
            while(v_lev[d]>0){
                 int add = min(v_lev[d],col_count[col[v]][d+v_level[v]]);
                 v_val += add;
                 v_swaps += add-v_col[d];
                 ++d;
            }
            if(v_val>val){
                val=v_val;
                swaps=v_swaps;
            }
            if(val==v_val)
                    swaps = min(v_swaps,swaps);
        }
    } 
    cout << val << ' ' << swaps<<'\n';
}
