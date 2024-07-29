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

bool find_corner_direction(int n){
    vector<vector<bool>> turn_on(n, vector<bool>(n, false));
    turn_on[0][1] = true;
    turn_on[0][2] = true;

    int before = count_lit_squares(turn_on);
    turn_on[0][0] = true;
    int after = count_lit_squares(turn_on);

    if(before == after){
        // horizontal
        return true;
    }
    if(after - before >= n - 1){
        // vertical
        return false;
    }
    // after - before == n - 2
    // horizontal
    return true;
}

int helper(int n, vector<pair<int, int>> squares){
    vector<vector<bool>> turn_on(n, vector<bool>(n, false));
    for(auto [x, y]: squares){
        turn_on[x][y] = true;
    }
    return count_lit_squares(turn_on);
}

vector<vector<bool>> solve(int n){
    vector<vector<bool>> turn_on(n, vector<bool>(n, false));
    vector<vector<bool>> answer(n, vector<bool>(n, false));

    for(int i = 0; i < n; ++i){
        int l = 0, r = n;
        while(l != r){
            int mid = (l + r) >> 1;

            if(mid == 0){
                if(helper(n, vector{pair{i, 0}, pair{i, 1}}) == n){
                    r = 0;
                    break;
                }
                // => 2 * n - 1
                if(helper(n, vector{pair{i, 0}, pair{i, 1}, pair{i, 2}}) == 2 * n - 1){
                    // (i, 2) is horizontal
                    if(helper(n, vector{pair{i, 0}, pair{i, 2}}) == n){
                        // horizontal
                        r = 0;
                        break;
                    }
                    // vertical
                    l = r = 1;
                    break;
                }
                // (i, 2) is vertical
                if(helper(n, vector{pair{i, 0}, pair{i, 2}}) == 2 * n){
                    // vertical
                    l = r = 1;
                    break;
                }
                r = 0;
                break;
            }

            for(int j = 0; j <= mid; ++j){
                turn_on[i][j] = true;
            }
            for(int j = mid + 1; j < n; ++j){
                turn_on[i][j] = false;
            }

            int cnt = count_lit_squares(turn_on);
            if(cnt == n * n){
                return turn_on;
            }

            if(cnt % n == 0 && cnt != n){
                l = mid + 1;
            }
            else{
                r = mid;
            }
        }
        if(r == n){
            for(int j = 0; j < n; ++j){
                turn_on[i][j] = true;
            }
            return turn_on;
        }

        answer[i][r] = true;
        for(int j = 0; j < n; ++j){
            turn_on[i][j] = false;
        }
    }

    return answer;
}
