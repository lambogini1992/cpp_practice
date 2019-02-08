#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

void print_matrix(vector<vector<int>> matrix)
{
   vector<int> array;
   int num_row, num_collum;
   int k, z;
   int i, j;
   int data;
   int count_index;

   data = 0;
   num_row = matrix.size() - 1;
   num_collum = matrix[0].size() - 1;
   k = z = 0;

   while((k < num_row) && (z < num_collum))
   {
     for (i = z; i <= num_collum; i++)
     {
       data = matrix[0][i];
       array.push_back(data);
     }
     i--;
     k++;
     for (j = k; j <= num_row; j++)
     {
       /* code */
       data = matrix[j][i];
       array.push_back(data);
     }
     j--;
     num_collum--;

     for (i = num_collum; i >= z; i--)
     {
       /* code */
       data = matrix[j][i];
       array.push_back(data);
     }
     i++;
     num_row--;

     for (j = num_row; j >= k; j--)
     {
       /* code */
       data = matrix[j][i];
       array.push_back(data);
     }
     j++;
     z++;
   }

   count_index = array.size() - 1;

   for ( i = 0; i < count_index; i++)
   {
     /* code */
     std::cout << array[i] << " ";
   }
   cout << endl;

}

int main(int argc, char const *argv[]) {
  vector<std::vector<int>> matrix;

  int i, j, k;
  int data;
  matrix.resize(10);
  k = 0;

  while(1)
  {

    for ( i = 0; i < 10; i++)
    {
      // matrix[i].resize(10);
      for ( j = 0; j < 100; j++)
      {
        /* code */
        matrix[i].push_back(k);
        k++;
      }
    }
    break;
  }

  for ( i = 0; i < 10; i++)
  {
    for ( j = 0; j < 100; j++)
    {
      /* code */
      data = matrix[i][j];
      std::cout << data << " ";
    }
    cout << endl;
  }


  print_matrix(matrix);

  return 0;
}
