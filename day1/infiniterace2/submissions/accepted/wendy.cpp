#include <bits/stdc++.h>
#define f(i, s, k, l) for (int i = s; i < k; i += l)
#define for0(i, k) f(i, 0, k, 1)

#define pl pair<long long, long long>
#define pb push_back

#define vl vector<long long>
#define vi vector<int>
#define sz(x) (ll)(x).size()

using namespace std;
using ll = long long;
using ld = long double;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

    ll n, q, x;
    ll laps = 0; 
    cin >> n >> q;
    set<ll> behind;  
    for0(i, q) {
        cin >> x; 
        if (x > 0 && behind.find(x) == behind.end()) behind.insert(x); 
        else if (x > 0 && behind.find(x) != behind.end()) {
            laps++; 
            behind.clear();
            behind.insert(x);
        } else if (x < 0 && behind.find(-1 * x) != behind.end()) behind.erase(-1 * x);  
    }
    cout << laps << endl; 
    
}