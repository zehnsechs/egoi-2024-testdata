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

    ll n, m, q, k, x, y; 
    cin >> n >> m >> q; 
    vector<vl> adj(2 * n); 
    for0(i, 2 * n) {
        adj[i].pb((i + 1) % (2 * n));
        adj[(i + 1) % (2 * n)].pb(i);
        adj[i].pb((i + 2 * n - 1) % (2 * n));
        adj[(i + 2 * n - 1) % (2 * n)].pb(i); 
    }
    for0(i, m) {
        cin >> k; 
        adj[k].pb(k + n); 
        adj[k + n].pb(k); 
    } 

    vector<vl> dist(2 * n, vl(2 * n, -1)); 
    for0(i, 2 * n) {
        queue<ll> q; 
        q.push(i); 
        dist[i][i] = 0; 
        while(!q.empty()) {
            ll cur = q.front(); 
            q.pop(); 
            for (auto v : adj[cur]) {
                if (dist[i][v] == -1) {
                    q.push(v);
                    dist[i][v] = dist[i][cur] + 1; 
                }
            }
        }
    }

    for0(i, q) {
        cin >> x >> y; 
        cout << dist[x][y] << endl; 
    }
}