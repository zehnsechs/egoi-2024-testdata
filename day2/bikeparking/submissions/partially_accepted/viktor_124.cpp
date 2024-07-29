#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <array>
#include <iomanip>
#include <queue>
#include <stack>
#include <numeric>
#include <cassert>
#include <cmath>
#include <random>
#include <ctime>
#include <chrono>

using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define all(x) (x).begin(), (x).end()
#define sz(x) ((int)x.size())
#define rep(i, a, b) for(int i = a; i < b; ++i)

template <typename T> void chmin(T &a, T b){ a = (b < a) ? b : a; }
template <typename T> void chmax(T &a, T b){ a = (b > a) ? b : a; } 

const int N = 3e5 + 3;
const ll INF = 1e18;

ll n, x[N], y[N];

ll sgn(ll x){
    return (x > 0) - (x < 0);
}

ll calc(ll cnt_good){
    ll sv = cnt_good;
    vector<pair<ll, ll>> xv, yv;
    for(int i = 0; i < n; ++i){
        if(y[i] <= cnt_good){
            cnt_good -= y[i];
            yv.push_back({y[i], i});
        }
        else if(cnt_good){
            yv.push_back({cnt_good, i});
            cnt_good = 0;
        }
    }

    cnt_good = sv;
    for(int i = n - 1; i >= 0; --i){
        if(x[i] <= cnt_good){
            cnt_good -= x[i];
            xv.push_back({x[i], i});
        }
        else if(cnt_good){
            xv.push_back({cnt_good, i});
            cnt_good = 0;
        }
    }
    reverse(all(xv));

    int j = 0;
    ll ans = sv;
    for(int i = 0; i < n; ++i){
        ans -= y[i];
    }
    // cout << ans << " before" << endl;

    for(int i = 0; i < yv.size(); ++i){
        while(yv[i].first > 0){
            if(xv[j].first == 0){
                ++j;
                continue;
            }
            ll take = min(yv[i].first, xv[j].first);
            ans += sgn(-(yv[i].second - xv[j].second)) * take;
            // cout << yv[i].second << " " << xv[j].second << " cmp" << endl;
            yv[i].first -= take;
            xv[j].first -= take;
        }
    }
    return ans;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; ++i)
        cin >> x[i];
    reverse(x, x + n);

    ll sum = 0;
    for(int i = 0; i < n; ++i){
        cin >> y[i];
        sum += y[i];
    }
    reverse(y, y + n);

    // for(int i = 0; i <= sum; ++i){
        // cout << calc(i) << " calc" << endl;
    // }

    ll l = 0, r = sum;
    while((r - l) > 2){
        ll mid1 = (2 * l + r) / 3;
        ll mid2 = (l + 2 * r) / 3;
        if(calc(mid1) > calc(mid2)){
            r = mid2;
        }
        else{
            l = mid1;
        }
    }

    ll score = -INF;
    for(ll val = l; val <= r; ++val){
        chmax(score, calc(val));
    }

    cout << score << "\n";
}