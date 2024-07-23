#include "validator.h"
#include<bits/stdc++.h>
using namespace std;

bool dfs(int v, int p, vector<vector<int>>& adj, vector<int>& vis){
    if(vis[v]) return true;
    vis[v]=1;
    bool res = false;
    for(int w: adj[v]){
        if(w==p) continue;
        res |= dfs(w,v,adj,vis);
    }
    return res;
}
void run() {
    int n = Int(1, Arg("maxn"));
    Space();
    int k = Int(1, Arg("maxk")); 
    assert(k <= n);
    Endl();


    vector<int> cols = SpacedInts(n, 0, k-1);
    vector<int> col_count(k);
    for(int i=0;i<n;++i){
        col_count[cols[i]]++;
    }   
    assert(*max_element(col_count.begin(),col_count.end())<=int(Arg("maxc")));
    vector<int> p(n-1);
    vector<vector<int>> adj(n);
    for(int i=0;i<n-1;++i){
        int a  = Int(0,n-1);
        Endl();
        int b = i+1;
        p[i] = a;
        adj[a].push_back(b);
        adj[b].push_back(a);	
    }

    vector<int> vis(n,0);
    assert(!dfs(0,-1,adj,vis));

    for(int i=0;i<n;++i){
        assert(vis[i]);
    }
    string graph =Arg("graph");	  
    if(graph =="path"){
        for(int i=0; i<n-1;++i){
            assert(p[i]==i);
        }
        for(int i=0;i<n;++i){
            assert(adj[i].size()<=2);
        }
        assert(adj[0].size()<=1);
    }
}                                                                                                        
