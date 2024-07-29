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

#define all(x) begin(x), end(x)

ll n; 
void colorMatching(vector<vl> &matching) {
    cout << 2 * matching.size() << endl; 
    for0(i, matching.size()) {
        for0(j, n) {
            if (matching[i][j] == -1) cout << j << " "; 
            else cout << min((ll) j, matching[i][j]) << " ";  
        }
        cout << endl; 
        for0(j, n) {
            if (matching[i][j] == -1) cout << j << " "; 
            else cout << min((ll) j, matching[i][j]) << " ";  
        }
        cout << endl; 
    }
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
    ll m, a, b; 
    cin >> n >> m; 
    set<pl> edges;
    for0(i, m) {
        cin >> a >> b; 
        edges.insert({a, b}); 
    }
    vector<vl> matching; 

    while (!edges.empty()) {
        matching.pb(vl(n, -1)); 
        matching.back()[edges.begin()->first] = edges.begin()->second; 
        matching.back()[edges.begin()->second] = edges.begin()->first; 
        edges.erase(edges.begin());  
        for(auto it = edges.begin(); it != edges.end();) {
            if (matching.back()[it->first] == -1 && matching.back()[it->second] == -1) {
                matching.back()[it->first] = it->second; 
                matching.back()[it->second] = it->first; 
                it = edges.erase(it); 
            } else it++; 
        }
    }
    colorMatching(matching); 
}