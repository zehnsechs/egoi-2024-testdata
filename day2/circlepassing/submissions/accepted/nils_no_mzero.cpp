#include <bits/stdc++.h>
using namespace std;
 
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;

ll n,m,q;
set<ll> S;

ll dist(ll a, ll b){
    ll d = abs((a+2*n)%(2*n) - (b+2*n)%(2*n));
    return min(d, 2*n-d);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m >> q;
    rep(c1,0,m){
        ll a;
        cin >> a;
        S.insert(a-n);
        S.insert(a);
        S.insert(a+n);
        S.insert(a+2*n);
    }
    rep(c1,0,q){
        ll a,b;
        cin >> a >> b;
        ll ans = dist(a,b);
        auto it = S.lower_bound(a);
        ans = min(ans, dist(a,(*it)) + dist((*it)+n,b) + 1);
        it--;
        ans = min(ans, dist(a,(*it)) + dist((*it)+n,b) + 1);
        cout << ans << "\n";
    }

    return 0;
}
