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
    cout << (n + rs[0]) / (rs[0] + 1);
}