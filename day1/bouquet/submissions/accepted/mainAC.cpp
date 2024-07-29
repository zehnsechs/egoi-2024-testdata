#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

const int inf = 1e9;
int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    std::cin >> n;
    std::vector<int> dp(n, 0);
    std::vector<std::vector<int>> add(n + 1);
    std::map<int, int> mx;
    mx[-inf] = 0;
    for(int i = 0; i < n; ++i) {
        int l, r;
        std::cin >> l >> r;
        for(int j: add[i]) {
            auto it = mx.lower_bound(j);
            if(prev(it)->second > dp[j]) continue;
            while(it != mx.end() && it->second <= dp[j]) {
                mx.erase(it++);
            }
            mx[j] = dp[j];
        }
        dp[i] = 1 + (--mx.lower_bound(i - l))->second;
        add[std::min(n, i + r + 1)].push_back(i);
    }
    std::cout << *max_element(dp.begin(), dp.end()) << "\n";
}
