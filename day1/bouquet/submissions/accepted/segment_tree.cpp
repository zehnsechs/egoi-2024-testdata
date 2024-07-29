#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int N = 2e5 + 10;
int t[4 * N], lazy[4 * N], a[N];
void modif(int i, int l, int r, int pos, int val) {
    if(l > pos || r < pos) return;
    if(l >= pos && r <= pos) {
        t[i] = max(t[i], val);
        return;
    }
    int mid = l + r >> 1;
    modif(2 * i, l, mid, pos, val);
    modif(2 * i + 1, mid + 1, r, pos, val);
    t[i] = max(t[2 * i], t[2 * i + 1]);
}
int query(int i, int l, int r, int tl, int tr) {
    if(l > tr || r < tl) return 0;
    if(l >= tl && r <= tr) return t[i];
    int mid = l + r >> 1;
    return max(query(2 * i, l, mid, tl, tr), query(2 * i + 1, mid + 1, r, tl, tr));
}
int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n; cin >> n;
    vector<int> dp(n, 0);
    vector<vector<int>> add(n + 1);
    for(int i = 0; i < n; ++i) {
        int l, r; cin >> l >> r;
        if(i - l - 1 >= 0)
            dp[i] = max(1, query(1, 0, n - 1, 0, i - l - 1) + 1);
        dp[i] = max(dp[i], 1);
        if(i + r < n)
            add[i + r].push_back(i);
        for(int j: add[i]) {
                modif(1, 0, n - 1, j, dp[j]);
        }
    }
    cout << *max_element(dp.begin(), dp.end()) << "\n";
}
