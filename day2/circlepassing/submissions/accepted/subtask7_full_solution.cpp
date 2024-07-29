#include <bits/stdc++.h>
using namespace std;

int n ,m ,q;
vector <int> a;

int dist(int x ,int y){
    return min(abs(x-y), n+n - abs(x-y));
}

int dist(int x ,int k ,int y){
    return dist(x ,k) + 1 + dist(k < n? k+n : k-n ,y);
}

int solve(int x ,int y){
    if(m == 0)
        return dist(x ,y);

    auto nxt = upper_bound(a.begin() ,a.end() ,x);
    if(nxt == a.end())
        nxt = a.begin();
    auto prv = nxt;
    if(prv == a.begin())
        prv = a.end();
    prv--;

    return min({dist(x ,y)
               ,dist(x ,*prv ,y)
               ,dist(x ,*nxt ,y)});
}

int main()
{
    scanf("%d%d%d",&n,&m,&q);
    a.resize(m + m);
    for(int i = 0; i < m; i++){
        scanf("%d",&a[i]);
        a[i + m] = a[i] + n;
    }
    while(q--){
        int x ,y;
        scanf("%d%d",&x,&y);
        printf("%d\n",solve(x ,y));
    }
}
