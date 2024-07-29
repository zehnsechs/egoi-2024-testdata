#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n; cin >> n;
    vector<int> x(n), y(n);
    for(int i = 0; i < n; ++i) cin >> x[i];
    for(int i = 0; i < n; ++i) cin >> y[i];
    int64_t ans = -(int64_t)(1e16);
    //check how many of type 1 to put in 0 and how many of type 0 to put in 0
    for(int put1 = 0; put1 <= y[1]; ++put1) {
        for(int put0 = 0; put0 <= y[0]; ++put0) {
            if(put0 + put1 <= x[0] && y[1] - put1 + y[0] - put0 <= x[1]) {
                int64_t cur = put1 - (y[0] - put0);
                ans = max(ans, cur);
            }
        }
    }
    std::cout << ans << "\n";
}
