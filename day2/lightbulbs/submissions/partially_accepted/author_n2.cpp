#include <cassert>
#include <iostream>
#include <vector>

using namespace std;
/******* convert to new input/output format *******/

void print_grid(const auto &v, char ch) {
  cout << ch << endl;
  for(auto &a : v) {
    for(auto b : a) cout << b;
    cout << endl;
  }
}

int count_lit_squares(const auto &g) {
  print_grid(g, '?');
  int k;
  cin >> k;
  return k;
}

vector<vector<bool>> solve(int n);

int main() {
  int n;
  cin >> n;
  auto g = solve(n);
  print_grid(g, '!');
}
/******* begin author solution *******/

vector<vector<bool>> solve(int n){
    vector<vector<bool>> direction(n, vector<bool>(n, false));
    // assume n > 2

    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            vector<vector<bool>> grid(n, vector<bool>(n, false));
            for(int j2 = 0; j2 < n; ++j2){
                if(j2 == j) continue;
                grid[i][j2] = true;
            }

            int before = count_lit_squares(grid);
            grid[i][j] = true;
            int after = count_lit_squares(grid);

            if(before == after){
                direction[i][j] = false;
            }
            else if(before == n){
                direction[i][j] = true;
            }
            else if(after % n != 0 && before % n == 0){
                direction[i][j] = false;
            }
            else{
                direction[i][j] = true;
            }
        }
    }

    vector<vector<bool>> answer(n, vector<bool>(n, false));

    for(int i = 0; i < n; ++i){
        bool all_vertical = true;
        for(int j = 0; j < n; ++j){
            if(!direction[i][j]){
                all_vertical = false;
                answer[i][j] = true;
                break;
            }
        }

        if(all_vertical){
            for(int i2 = 0; i2 < n; ++i2){
                for(int j2 = 0; j2 < n; ++j2){
                    answer[i2][j2] = i2 == i;
                }
            }
            return answer;
        }
    }
    return answer;
}
