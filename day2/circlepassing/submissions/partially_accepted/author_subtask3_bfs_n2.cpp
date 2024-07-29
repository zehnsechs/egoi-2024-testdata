#include <bits/stdc++.h>
using namespace std;

int n ,m ,q;
vector <vector <int>> adj;

vector <int> bfs(int u){
    queue <int> q;
    q.push(u);
    vector <int> dist(n+n ,-1);
    dist[u] = 0;
    while(!q.empty()){
        auto w = q.front(); q.pop();
        for(int&o : adj[w]) if(dist[o] == -1){
            dist[o] = dist[w] + 1;
            q.push(o);
        }
    }
    return dist;
}

int main()
{
    scanf("%d%d%d",&n,&m,&q);
    adj.resize(n+n);
    for(int i = 0; i < n+n; i++){
        adj[i].push_back(i+1 < n+n? i+1 : 0);
        adj[i].push_back(i > 0? i-1 : n+n-1);
    }
    for(int a ,i = 0; i < m; i++){
        scanf("%d",&a);
        adj[a].push_back(a+n);
        adj[a+n].push_back(a);
    }

    vector <vector <int>> dist(n+n);
    for(int i = 0; i < n+n; i++)
        dist[i] = bfs(i);

    while(q--){
        int x ,y;
        scanf("%d%d",&x,&y);
        printf("%d\n",dist[x][y]);
    }
}
