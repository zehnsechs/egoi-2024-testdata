#include<bits/stdc++.h>
#define int long long

using namespace std;


int dist(int x,int y,int n){
    //cout << x << ' ' << y << ' ' << n << ' ' << abs(x-y) << ' ' << 2*n-max(y,x)+min(x,y) <<'\n';
    return(min(abs(x-y),2*n-max(y,x)+min(x,y)));
}

signed main(){
    cin.tie(0)->sync_with_stdio(false);

    int n,m,q;
    cin >> n >> m >> q;

    int k;
    cin >> k;

    for(int i=0;i<q;++i){
        int x,y;
        cin >> x >> y;

        int x2 = x+n;

        int d = min(dist(y,x,n),dist(y,x2,n)+1);
        cout << d << '\n';
    }
}
