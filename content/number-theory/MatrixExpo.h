/**
 * Author: Anonymous
 * Description: MatrixExpo
 */
int **matrixmul(int **matrix1, int **matrix2) {
  int **matrix3 = new int *[2];
  for (int i = 0; i < 2; i++)
    matrix3[i] = new int[2];

  matrix3[0][0] =
      (matrix1[0][0] * matrix2[0][0]) + (matrix1[0][1] * matrix2[1][0]);
  matrix3[0][1] =
      (matrix1[0][0] * matrix2[0][1]) + (matrix1[0][1] * matrix2[1][1]);
  matrix3[1][0] =
      (matrix1[1][0] * matrix2[0][0]) + (matrix1[1][1] * matrix2[1][0]);
  matrix3[1][1] =
      (matrix1[1][0] * matrix2[0][1]) + (matrix1[1][1] * matrix2[1][1]);
  matrix3[0][0] %= M;
  matrix3[1][0] %= M;
  matrix3[0][1] %= M;
  matrix3[1][1] %= M;

  return matrix3;
}

int **matrixexpo(int **matrix, int n, int **ans) {
  while (n > 0) {
    if (n % 2 == 1)
      ans = matrixmul(ans, matrix);
    matrix = matrixmul(matrix, matrix);
    n /= 2;
  }
  return ans;
}
