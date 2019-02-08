#include <iostream>
#include <vector>
#include <iterator>
#include <math.h>
#include <stdint.h>

using namespace std;

int formingMagicSquare(vector<vector<int>> s)
{
  vector<vector<int>> square_matrix = {
    {8, 1, 6, 3, 5, 7, 4, 9, 2},
    {6, 1, 8, 7, 5, 3, 2, 9, 4},
    {4, 9, 2, 3, 5, 7, 8, 1, 6},
    {2, 9, 4, 7, 5, 3, 6, 1, 8},
    {8, 3, 4, 1, 5, 9, 6, 7, 2},
    {4, 3, 8, 9, 5, 1, 2, 7, 6},
    {6, 7, 2, 1, 5, 9, 8, 3, 4},
    {2, 7, 6, 9, 5, 1, 4, 3, 8}
  };

  vector<int> array_matrix;
  int minimun_cost, temp_cost;

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      array_matrix.push_back(s[i][j]);
    }
  }
  minimun_cost = 0;
  for (int i = 0; i < 8; i++) {
    temp_cost = 0;
    for (int j = 0; j < 9; j++) {
      temp_cost += abs(array_matrix[j] - square_matrix[i][j]);
    }
    if(i == 0)
    {
      minimun_cost = temp_cost;
      std::cout << " at zero point" << minimun_cost << '\n';
    }
    else
    {
      if(minimun_cost > temp_cost)
      {
        minimun_cost = temp_cost;
        std::cout << "get minimun cost transfer" << minimun_cost << '\n';
      }
    }
    std::cout << "get cost transfer" << temp_cost << '\n';
  }

  return minimun_cost;

}

int main(int argc, char const *argv[]) {
  vector<vector<int>> matrix;
  int result;

  matrix.resize(3);

  cout << "Input data for matrix" << endl;

  for (int i = 0; i < 3; i++) {
    matrix[i].resize(3);
    for (int j = 0; j < 3; j++) {
      cin >> matrix[i][j];
    }
  }

  result = formingMagicSquare(matrix);

  cout << result << endl;

  return 0;
}
