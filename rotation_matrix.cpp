#include <iostream>
#include <vector>
#include <stdint.h>
#include <iterator>

using namespace std;

void matrixRotation(vector<vector<int>> &matrix, int r)
{
  int data_temp;
  int length_row;
  int length_collum;
  int length_row_bk, length_collum_bk;
  int row_count, collum_count;
  int row_index, collum_index;
  int data;
  int rotation;


  rotation = r;

  length_row_bk    = matrix.size() - 1;
  length_collum_bk = matrix[0].size() - 1;

  while (rotation > 0) {
    row_count = collum_count = 0;
    row_index = collum_index = 0;
    length_row = length_row_bk;
    length_collum = length_collum_bk;
    while((row_count <= length_row) && (collum_count <= length_collum))
    {
      for (collum_index = collum_count; collum_index < length_collum; collum_index++)
      {
        data_temp = matrix[row_index][collum_index];
        matrix[row_index][collum_index] = matrix[row_index][collum_index + 1];
        matrix[row_index][collum_index + 1] = data_temp;
      }

      collum_index = length_collum;

      for (row_index = row_count; row_index < length_row; row_index++)
      {
        data_temp = matrix[row_index][collum_index];
        matrix[row_index][collum_index] = matrix[row_index + 1][collum_index];
        matrix[row_index + 1][collum_index] = data_temp;
      }

      row_index = length_row;
      for (collum_index = length_collum; collum_index > collum_count; collum_index--)
      {
        data_temp = matrix[row_index][collum_index];
        matrix[row_index][collum_index] = matrix[row_index][collum_index - 1];
        matrix[row_index][collum_index - 1] = data_temp;
      }

      collum_index = collum_count;
      for (row_index = length_row; row_index > row_count + 1; row_index--)
      {
        data_temp = matrix[row_index][collum_index];
        matrix[row_index][collum_index] = matrix[row_index - 1][collum_index];
        matrix[row_index - 1][collum_index] = data_temp;
      }

      row_count ++;
      collum_count ++;
      length_row --;
      length_collum --;
    }
    rotation --;
  }

  cout << "The Matrix after rotation" << r << "time" << endl;
  for (int i = 0; i < matrix.size(); i++) {
    /* code */
    for (int j = 0; j < matrix[i].size(); j++) {
      /* code */
      cout << matrix[i][j] << " ";
    }
    cout << endl;
  }
}

int main(int argc, char const *argv[]) {
  std::vector<std::vector<int>> matrix;
  int data;
  matrix.resize(10);
  data = 1;
  // cout << "Input The Matrix:" << endl;
  for (int i = 0; i < 10; i++) {
    matrix[i].resize(10);
    for (int j = 0; j < 10; j++) {
      matrix[i][j] = data;
      data ++;
    }
  }

  cout << "The Matrix before roation:" << endl;
  for (int i = 0; i < matrix.size(); i++) {
    /* code */
    for (int j = 0; j < matrix[i].size(); j++) {
      /* code */
      cout << matrix[i][j] << " ";
    }
    cout << endl;
  }

  matrixRotation(matrix, 10);

  return 0;
}
