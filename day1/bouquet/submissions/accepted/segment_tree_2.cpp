#include<iostream>
#include <vector>
using namespace std;
#define int long long

const int MAXN=2e5;
const int BIG=1e9+1;

//full solution
struct segtree{
    vector<int> tree;

    segtree(int n){
        tree.assign(n*4, 0);
    }

    int update(int l, int r, int v, int i, int val){
        if(i<l || r<=i) return tree[v];
        if(l+1==r){
            return tree[v]=val;
        }
        int m=l+(r-l)/2;
        return tree[v] = max(update(l, m, v*2+1, i, val), update(m, r, v*2+2, i, val));
    }

    int query(int l, int r, int v, int ql, int qr){
        if(qr<=l || r<=ql) return 0;
        if(ql<=l && r<=qr){
            return tree[v];
        }
        int m=l+(r-l)/2;
        return max(query(l, m, v*2+1, ql, qr), query(m, r, v*2+2, ql, qr));
    }
};
int solve(int n, vector<int>& l, vector<int>& r){

    segtree seg(n);

    vector<int> dp(n, 0);
    vector<vector<int> > update(n);
    for(int i=0; i<n; i++){

        dp[i] = seg.query(0, n, 0, 0, i-l[i])+1;
        dp[i] = max(dp[i], 1ll);

        if(i+r[i] < n){
            update[i + r[i]].push_back(i);
        }
        for(auto j: update[i]){

            seg.update(0, n, 0, j, dp[j]);
        }
    }

    int answer=0;
    for(int i=0; i<n; i++){
        answer = max(answer, dp[i]);
    }
    return answer;
}


signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n; cin >> n;
    vector<int> l(n), r(n);
    for(int i = 0; i < n; ++i) {
        cin >> l[i] >> r[i];
    }
    cout << solve(n, l, r);
}
