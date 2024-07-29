#include <bits/stdc++.h>
using namespace std;

int n ,m ,q;
vector <bool> road;
vector <int> prv;
vector <int> nxt;

int dist(int x ,int y){
    return min(abs(x-y), n+n - abs(x-y));
}

int dist(int x ,int k ,int y){
    return dist(x ,k) + 1 + dist(k < n? k+n : k-n ,y);
}

void process(){
    prv.resize(n+n);
    nxt.resize(n+n);
    nxt[0] = n+n;
    for(int i = 0; i < n+n; i++) if(road[i]){
        prv[0] = max(prv[0], i);
        nxt[0] = min(nxt[0], i);
    }
    int z = n+n-1;
    prv[0] = (road[0]? 0 : prv[0]);
    nxt[z] = (road[z]? z : nxt[0]);
    for(int i = 1; i <= z; i++)
        prv[i] = (road[i]? i : prv[i-1]);
    for(int i = z-1; i >= 0; i--)
        nxt[i] = (road[i]? i : nxt[i+1]);
}

int solve(int x ,int y){
    if(m == 0)
        return dist(x ,y);
    return min({dist(x ,y)
               ,dist(x ,prv[x] ,y)
               ,dist(x ,nxt[x] ,y)});
}

int main()
{
    scanf("%d%d%d",&n,&m,&q);
    road.resize(n+n);
    for(int a, i = 0; i < m; i++){
        scanf("%d",&a);
        road[a] = true;
        road[a+n] = true;
    }

    process();

    while(q--){
        int x ,y;
        scanf("%d%d",&x,&y);
        printf("%d\n",solve(x ,y));
    }
}
