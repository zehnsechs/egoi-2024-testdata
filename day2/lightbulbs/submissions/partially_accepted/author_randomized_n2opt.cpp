#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
#include <numeric>
#include <cassert>
#include <iostream>

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
    if(n == 1){
        direction[0][0] = true;
        return direction;
    }

    mt19937 mt(chrono::steady_clock::now().time_since_epoch().count());
    vector<int> o1(n), o2(n);
    iota(o1.begin(), o1.end(), 0);
    iota(o2.begin(), o2.end(), 0);
    shuffle(o1.begin(), o1.end(), mt);
    shuffle(o2.begin(), o2.end(), mt);

    for(int i = 0; i < n; ++i){
        int after;
        {
            vector<vector<bool>> grid(n, vector<bool>(n, false));
            for(int j2 = 0; j2 < n; ++j2){
                grid[o1[i]][o2[j2]] = true;
            }
            after = count_lit_squares(grid);
        }

        bool early_break = false;

        for(int j = 0; j < n; ++j){
            vector<vector<bool>> grid(n, vector<bool>(n, false));
            for(int j2 = 0; j2 < n; ++j2){
                if(j2 == j) continue;
                grid[o1[i]][o2[j2]] = true;
            }

            int before = count_lit_squares(grid);
            grid[o1[i]][o2[j]] = true;
            
            if(before == after){
                direction[o1[i]][o2[j]] = false;
                early_break = true;
                break;
            }
            else if(before == n){
                direction[o1[i]][o2[j]] = true;
            }
            else if(after % n != 0 && before % n == 0){
                direction[o1[i]][o2[j]] = false;
                early_break = true;
                break;
            }
            else{
                direction[o1[i]][o2[j]] = true;
            }
        }
        if(!early_break){
            break;
        }
    }

    vector<vector<bool>> answer(n, vector<bool>(n, false));

    for(int i = 0; i < n; ++i){
        bool all_vertical = true;
        for(int j = 0; j < n; ++j){
            if(!direction[o1[i]][o2[j]]){
                all_vertical = false;
                answer[o1[i]][o2[j]] = true;
                break;
            }
        }

        if(all_vertical){
            for(int i2 = 0; i2 < n; ++i2){
                for(int j2 = 0; j2 < n; ++j2){
                    answer[o1[i2]][o2[j2]] = i2 == i;
                }
            }
            return answer;
        }
    }
    return answer;
}
