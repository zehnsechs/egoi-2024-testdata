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
typedef vector<ll> vl;
typedef long double ld;

const int MAXN = 201;
int n,m;
vector<vi> C(MAXN, vi());
int ADJ[MAXN][MAXN] = {0};
vector<vi> ANS;

int root, n1, n2; // root and its neighbours

int PAR[MAXN] = {0};
int DEPTH[MAXN] = {0};
int MAX_SUBTREE_DEPTH[MAXN] = {0};
int mark[MAXN] = {0};
vector<vi> TREE(MAXN, vi());

void dfs1(int i, int par){
    if(mark[i] == 1)return;
    mark[i] = 1;
    PAR[i] = par;
    if(par != -1)DEPTH[i] = DEPTH[par]+1;
    MAX_SUBTREE_DEPTH[i] = DEPTH[i];
    trav(y, C[i]){
        if(mark[y] == 0){
            TREE[i].push_back(y);
            dfs1(y, i);
            MAX_SUBTREE_DEPTH[i] = max(MAX_SUBTREE_DEPTH[i], MAX_SUBTREE_DEPTH[y]);
        }
    }
}

int F[MAXN] = {0};
int B[MAXN] = {0};
int f = 0; // number of f:s

void make_move(vi col){

    vi new_f(n,0);
    ANS.push_back(col);

    rep(c1,0,n){
        bool OR = 0;
        bool alone = 1;
        trav(y, C[c1]){
            if(col[y] == col[c1]){
                alone = 0;
                OR |= F[y];
            }
        }

        if(alone){
            new_f[c1] = F[c1];
        }
        else{
            new_f[c1] = OR;
        }
    }

    f = 0;
    rep(c1,0,n){
        F[c1] = new_f[c1];
        f += F[c1];
    }
}

void move_group(vi v){
    // color v the same, color everything else in different colors
    vi in_group(n,0);
    vi col(n,0);
    trav(y, v){
        in_group[y] = 1;
    }
    int c = 2;
    rep(c1,0,n){
        if(in_group[c1]){
            col[c1] = 1;
        }
        else{
            col[c1] = c;
            c++;
        }
    }
    make_move(col);
}

int max_depth = 0;

bool comp_tree(int i, int j){
    return MAX_SUBTREE_DEPTH[i] < MAX_SUBTREE_DEPTH[j];
}

bool last_visited[MAXN] = {0};
int last_seen = 0;

void last_dfs(int i){
    if(!last_visited[i]){
        last_visited[i] = 1;
        last_seen++;
    }
    if(last_seen == n)return;
    sort(all(TREE[i]), comp_tree);
    trav(y, TREE[i]){
        move_group({i, y});
        last_dfs(y);
        if(last_seen == n)return;
        move_group({i, y});
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> n >> m;

    if(m == (n*n-n)/2){
        // Clique
        // Greedy matching seems to be linear
        // Can also be done with divide and conquer
        vector<vi> done(n, vi(n, 0));
        int matched = 0;
        while(matched < (n*n-n)/2){
            vi row(n,-1);
            int color = 1;
            rep(c1,0,n){
                if(row[c1] == -1){
                    row[c1] = color;
                    rep(c2,1,n){
                        int j = (c1+c2)%n;
                        if(row[j] == -1 && done[c1][j] == 0){
                            done[c1][j] = 1;
                            done[j][c1] = 1;
                            matched++;
                            row[j] = color;
                            break;
                        }
                    }
                    color++;
                }
            }
            ANS.push_back(row);
            ANS.push_back(row);
        }
        ANS.pop_back();
    }
    else{
        // Non-clique
        rep(c1,0,m){
            int a,b;
            cin >> a >> b;
            C[a].push_back(b);
            C[b].push_back(a);
            ADJ[a][b] = 1;
            ADJ[b][a] = 1;
        }

        // Find root. n^3 because why not.
        rep(c1,0,n){
            rep(c2,0,n){
                rep(c3,0,n){
                    if(c1 != c2 && c1 != c3 && c2 != c3){
                        if(ADJ[c2][c1] && ADJ[c1][c3] && !ADJ[c2][c3]){
                            root = c1;
                            n1 = c2;
                            n2 = c3;
                            goto root_done;
                        }
                    }
                }
            }
        }

        root_done:

        swap(n1, root); // better if n1 is the root

        dfs1(root, -1);

        rep(c1,0,n){
            max_depth = max(max_depth, DEPTH[c1]);
            if(c1 != root)F[c1] = 1;
            int min_depth = n+1;
            trav(y, C[c1]){
                if(DEPTH[y] < min_depth){
                    min_depth = DEPTH[y];
                    B[c1] = y;
                }
            }
        }
        f = n-1;

        // make F[x] = 0 where for max_depth-1
        rep(d,0,max_depth-1){
            vi v;
            rep(c1,0,n){
                if(DEPTH[c1] == d || DEPTH[c1] == d+1){
                    v.push_back(c1);
                }
            }
            move_group(v);
        }

        for(int d = max_depth-1; d >= 1; d--){
            rep(c1,0,n){
                if(DEPTH[B[c1]] == d){
                    move_group({c1, B[c1], PAR[B[c1]]});
                    move_group({B[c1], PAR[B[c1]]});
                }
            }

            vi v;
            rep(c1,0,n){
                if(DEPTH[c1] == d || DEPTH[c1] == d-1){
                    v.push_back(c1);
                }
            }
            move_group(v);
        }

        // remove any extra F from n1
        move_group({root, n1});
        move_group({root, n1, n2});
        move_group({n1, n2});

        rep(c1,0,n){
            if(F[c1] == 1 && c1 != n2){
                // This should be a neighbour of the root
                move_group({c1, root});
                move_group({root, n1, n2});
                move_group({n1, n2});
            }
        }

        // this is a bit unnecessary, but only 2 queries so who cares
        move_group({n1, n2});
        move_group({n1, root});

        // everyone now at root

        assert(f == 1);

        last_dfs(root);

    }

    ANS.pop_back();
    cout << sz(ANS) << "\n";
    trav(v, ANS){
        trav(c, v){
            cout << c << " ";
        }cout << "\n";
    }
	
 
    return 0;
}