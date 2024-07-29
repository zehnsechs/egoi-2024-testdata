#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n; cin >> n;
    vector<int> ls(n), rs(n);
    vector<int> dp(n);
    for(int i = 0; i < n; ++i) {
        cin >> ls[i] >> rs[i];
    }
    dp[0] = 1;
    for(int i = 1; i < n; ++i) {
        dp[i] = dp[i - 1];
        if(0 <= i - ls[i] - 1)
            dp[i] = max(dp[i], dp[i - ls[i] - 1] + 1);
    }
    cout << dp[n - 1];
}