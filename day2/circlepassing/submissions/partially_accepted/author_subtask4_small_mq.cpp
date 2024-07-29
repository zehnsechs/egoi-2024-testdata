#include <bits/stdc++.h>
using namespace std;

int n ,m ,q;
vector <int> a;

int dist(int x ,int y){
    return min(abs(x-y), n+n - abs(x-y));
}

int dist(int x ,int k ,int y){
    return dist(x ,k) + 1 + dist(k+n ,y);
}

int solve(int x ,int y){
    int ans = dist(x ,y);
    for(int&w : a){
        ans = min(ans ,dist(x ,w ,y));
        ans = min(ans ,dist(y ,w ,x));
    }
    return ans;
}

int main()
{
    scanf("%d%d%d",&n,&m,&q);
    a.resize(m);
    for(int&i : a)
        scanf("%d",&i);
    while(q--){
        int x ,y;
        scanf("%d%d",&x,&y);
        printf("%d\n",solve(x ,y));
    }
}
