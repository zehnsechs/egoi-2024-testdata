#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int N = 2e5 + 10;
int a[N];

void modif(int l, int r, int val) {
    for(int i = l; i <= r; ++i) {
        a[i] = max(a[i], val);
    }
}
int query(int l, int r) {
    int res = 0;
    for(int i = l; i <= r; ++i) {
        res = max(res, a[i]);
    }
    return res;
}

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n; cin >> n;
    vector<int> dp(n, 0);
    vector<vector<int>> add(n + 1);
    for(int i = 0; i < n; ++i) {
        int l, r; cin >> l >> r;
        if(i - l - 1 >= 0)
            dp[i] = query(0, i - l - 1) + 1;
        dp[i] = max(dp[i], 1);
        if(i + r < n)
            add[i + r].push_back(i);
        for(int j: add[i]) {
                modif(j, j, dp[j]);
        }
    }
    cout << *max_element(dp.begin(), dp.end()) << "\n";
}
