#include <iostream>
#include <vector>
#include <stdint.h>
#include <iterator>

using namespace std;
/*variable r is time of rotation matrix*/

// void rotation_array(vector<int> *array, int r)
// {
//   vector<int> array_temp (array->size(), 1);
//   int length_array;
//   int data, pos;
//
//   data = 0;
//   length_array = array_temp.size();
//
//   for (int i = 0; i < length_array; i++)
//   {
//     data = array->at(i);
//     if( length_array > i + r)
//     {
//       pos = i + r;
//     }
//     else
//     {
//       pos = i + r - length_array;
//     }
//     array_temp[pos] = data;
//   }
//   array_temp.swap(*array);
// }
//
// void return_matrix(vector<vector<int>> *matrix, vector<int> array, int pos, int length_row, int length_collum)
// {
//   int i, j, k, z;
//   k = z = pos;
//   for(i = z; i <= length_collum, i++)
//   {
//
//   }
// }

void rotation_matrix(vector<vector<int>> matrix, int r)
{
  vector<vector<int>> matrix_temp;
  int length_row;
  int length_collum;
  int row_count, collum_count;
  int row_index, collum_index;
  int data;

  row_count = collum_count = 0;

  length_row = matrix.size();
  length_collum = matrix[0].size();

  matrix_temp.resize(length_row);
  matrix_temp[0].resize(length_collum);
  
  while((row_count < length_row) && (collum_count < length_collum))
  {
    for()
  }

}
