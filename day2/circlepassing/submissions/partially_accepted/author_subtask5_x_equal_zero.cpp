#include <bits/stdc++.h>
using namespace std;

int n ,m ,q;
int min_road = 1e9;
int max_road = -1;

int dist(int x ,int y){
    return min(abs(x-y), n+n - abs(x-y));
}

int dist(int x ,int k ,int y){
    return dist(x ,k) + 1 + dist(k < n? k+n : k-n ,y);
}

int solve(int x ,int y){
    if(m == 0)
        return dist(x ,y);
    return min({dist(x ,y)
               ,dist(x ,min_road ,y)
               ,dist(x ,max_road ,y)});
}

int main()
{
    scanf("%d%d%d",&n,&m,&q);
    for(int a ,i = 0; i < m; i++){
        scanf("%d",&a);
        min_road = min(min_road ,a);
        max_road = max(max_road ,a+n);
    }
    while(q--){
        int x ,y;
        scanf("%d%d",&x,&y);
        printf("%d\n",solve(x ,y));
    }
}
