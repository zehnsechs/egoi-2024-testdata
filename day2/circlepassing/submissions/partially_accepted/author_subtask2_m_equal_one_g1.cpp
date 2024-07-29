#include <bits/stdc++.h>
using namespace std;

int n ,m ,q;
int k;

int dist(int x ,int y){
    return min(abs(x-y), n+n - abs(x-y));
}

int dist(int x ,int k ,int y){
    return dist(x ,k) + 1 + dist(k < n? k+n : k-n ,y);
}

int solve(int x ,int y){
    return min({dist(x ,y)
               ,dist(x ,k ,y)});
}

int main()
{
    scanf("%d%d%d",&n,&m,&q);
    assert(m == 1);
    scanf("%d",&k);
    while(q--){
        int x ,y;
        scanf("%d%d",&x,&y);
        printf("%d\n",solve(x ,y));
    }
}
