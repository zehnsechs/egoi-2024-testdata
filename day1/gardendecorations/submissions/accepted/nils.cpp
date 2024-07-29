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

const int MAXN = 1001;

int w,n;
vi A;
vi AI;
vector<vi> xor_sets;

vector<pii> edges;

vector<vector<vi>> ops(3, vector<vi>(MAXN, vi(MAXN, 0))); 

vector<vi> C(MAXN, vi());
vector<vi> CI(MAXN, vi());

bool ok(int i, int j){
    if(j == -1)return 1;
    return (j == A[i] || AI[j] < i);
}

int cc = 0;
int mark[MAXN] = {0};
vi edge_path;

int dfs(int i, int goal){
    if(mark[i] == cc)return -1;
    if(goal >= n){
        int j = goal-n;
        if(ok(j,i))return i;
    }
    else{
        if(i == edges[goal].first)return 1;
        if(i == edges[goal].second)return 2;
    }
    mark[i] = cc;
    rep(c1,0,sz(C[i])){
        int e = CI[i][c1];
        int j = C[i][c1];
        edge_path.push_back(e);
        int hej = dfs(j, goal);
        if(hej != -1)return hej;
        edge_path.pop_back();
    }
    return -1;
}


void simulate(){
    rep(c1,0,n){
        ops[0][c1][c1] = 1;
        int i = A[c1];
        while(i > c1){
            i = A[i];
        }
        if(i == c1)i = -1;
        edges.push_back({c1,i});
        if(i != -1)ops[0][c1][i] = 1;
    }

    for(int c1 = n-1; c1 >= 0; c1--){
        ops[1][c1][c1] = 1;
        if(edges[c1].first != -1 && edges[c1].second != -1){
            C[edges[c1].first].push_back(edges[c1].second);
            C[edges[c1].second].push_back(edges[c1].first);
            CI[edges[c1].first].push_back(c1);
            CI[edges[c1].second].push_back(c1);
        }

        if(edges[c1].first != A[c1] && edges[c1].second != A[c1]){
            cc++;
            int ny = dfs(A[c1], c1);
            assert(ny != -1);
            if(ny == 1){
                edges[c1].first = A[c1];
            }
            else{
                edges[c1].second = A[c1];
            }
            trav(e, edge_path){
                ops[1][c1][e] ^= 1;
            }
            edge_path.clear();
        }
        
        if(!ok(c1, edges[c1].first)){
            cc++;
            int ny = dfs(edges[c1].first, c1+n);
            assert(ny != -1);
            edges[c1].first = ny;
            trav(e, edge_path){
                ops[1][c1][e] ^= 1;
            }
            edge_path.clear();
        }
        
        if(!ok(c1, edges[c1].second)){
            cc++;
            int ny = dfs(edges[c1].second, c1+n);
            assert(ny != -1);
            edges[c1].second = ny;
            trav(e, edge_path){
                ops[1][c1][e] ^= 1;
            }
            edge_path.clear();
        }
        
    }

    rep(c1,0,n){
        ops[2][c1][c1] = 1;
        int other = -1;
        if(edges[c1].first != A[c1] && edges[c1].first != -1)other = edges[c1].first;
        if(edges[c1].second != A[c1] && edges[c1].second != -1)other = edges[c1].second;
        if(other != -1){
            int j = AI[other];
            rep(c2,0,n){
                ops[2][c1][c2] ^= ops[2][j][c2];
            }
        }
    }

}

int main() {
    cin >> w >> n;
    rep(c1,0,n){
        AI.push_back(0);
    }
    rep(c1,0,n){
        int a;
        cin >> a;
        A.push_back(a);
        AI[a] = c1;
    }

    if(w == 0){
        cout << "3\n";
        return 0;
    }
  
    simulate();

    vi B(n, 0);

    rep(c1,0,n){
        int i = c1;
        if(w%2 == 0)i = n-i-1;
        int b;
        cin >> b;
        B[i] = b;
        int x = 0;
        rep(c2,0,n){
            if(ops[w-1][i][c2] == 1)x ^= B[c2];
        }
        cout << x << "\n";
        fflush(stdout);
    }

    if(w == 1)return 0;

    return 0;
}
