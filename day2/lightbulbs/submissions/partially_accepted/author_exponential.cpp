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

vector<vector<bool>> solve(int n) {
  vector<vector<bool>> turn_on(n, vector<bool>(n, false));
  int answer = -1, answer_count = n * n + 1;
  for (int state = 0; state < (1 << (n * n)); ++state) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (state >> (i * n + j) & 1) {
          turn_on[i][j] = true;
        } else {
          turn_on[i][j] = false;
        }
      }
    }

    if (count_lit_squares(turn_on) == n * n) {
      int curr_count = __builtin_popcount(state);
      if (curr_count < answer_count) {
        answer_count = curr_count;
        answer = state;
      }
    }
  }

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (answer >> (i * n + j) & 1) {
        turn_on[i][j] = true;
      } else {
        turn_on[i][j] = false;
      }
    }
  }
  return turn_on;
}
