#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n;
    cin >> n;
    int x[n], y[n];
    for(int i = 0; i < n; ++i) cin >> x[i];
    for(int i = 0; i < n; ++i) cin >> y[i];

    int64_t ans = 0;
    int lst = n - 1;
    for (int i = n - 2; i >= 0; --i) {
        while (!y[lst]) --lst;
        for (int j = i + 1; x[i] && j <= lst; ++j) {
            int var = min(y[j], x[i]);
            y[j] -= var, x[i] -= var, ans += var;
        }
    }
    for(int i = 0; i < n; ++i)
        ans -= max(0, y[i] - x[i]);
    cout << ans << endl;
}
