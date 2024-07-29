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

int helper(int n, vector<pair<int, int>> cells) {
  vector<vector<bool>> turn_on(n, vector<bool>(n, false));
  for (auto [x, y] : cells) {
    turn_on[x][y] = true;
  }
  return count_lit_squares(turn_on);
}

vector<vector<bool>> solve(int n) {
  vector<vector<bool>> answer(n, vector<bool>(n, false));
  if (n == 1) {
    answer[0][0] = true;
    return answer;
  }

  int row = 0, col = 0;
  vector<pair<int, int>> marked[2];
  vector<vector<bool>> grid(n, vector<bool>(n, false));

  int current_lit_count = 0;
  while (row != n && col != n) {
    int row_cnt = n - row;
    int col_cnt = n - col;
    current_lit_count = n * n - row_cnt * col_cnt;

    if (row_cnt != col_cnt) {
      grid[row][col] = true;
      int new_lit_count = count_lit_squares(grid);
      int diff = new_lit_count - current_lit_count;

      if (diff == col_cnt) {
        // horizontal
        marked[0].push_back({row, col});
        ++row;
      } else {
        // vertical
        marked[1].push_back({row, col});
        ++col;
      }
      continue;
    }

    if (row_cnt > 2) {
      for (int j = col + 1; j < n; ++j) {
        grid[row][j] = true;
      }

      int before = count_lit_squares(grid);
      grid[row][col] = true;
      int after = count_lit_squares(grid);

      before -= current_lit_count;
      after -= current_lit_count;

      for (int j = col + 1; j < n; ++j) {
        grid[row][j] = false;
      }

      bool horizontal = false;
      if (before == after || (after % row_cnt != 0 && before % row_cnt == 0)) {
        horizontal = true;
      } else {
        horizontal = false;
      }

      grid[row][col] = true;
      if (horizontal) {
        marked[0].push_back({row, col});
        ++row;
      } else {
        marked[1].push_back({row, col});
        ++col;
      }
    } else if (row_cnt == 1) {
      marked[0].push_back({row, col});
      grid[row][col] = true;
      if (helper(n, marked[0]) != n * n) {
        marked[0].pop_back();
        marked[1].push_back({row, col});
        ++col;
      } else {
        ++row;
      }
    } else {
      // row_cnt = 2
      marked[0].push_back({row, col});
      grid[row][col] = true;
      if (helper(n, marked[0]) == n * (n - 1)) {
        ++row;
        continue;
      }
      marked[0].pop_back();
      marked[1].push_back({row, col});
      ++col;
    }
  }

  for (int dir = 0; dir < 2; ++dir) {
    if (marked[dir].size() == n) {
      for (auto [x, y] : marked[dir]) {
        answer[x][y] = true;
      }
      return answer;
    }
  }

  assert(false);
  return {};
}
