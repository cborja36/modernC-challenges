#include <stdio.h>

double vector_prod(size_t N, double x[N], double y[N]) {
  double result = 0;
  for (size_t i = 0; i < N; ++i) {
    result += x[i] * y[i];
  }
  return result;
}

void matrix_vector_prod(size_t N, size_t M, double A[N][M], double x[M],
                        double b[N]) {
  for (size_t i = 0; i < N; ++i) {
    b[i] = vector_prod(M, A[i], x);
  }
}

void print_matrix(size_t N, size_t M, double A[N][M]) {
  for (size_t i = 0; i < N; ++i) {
    printf("[");
    for (size_t j = 0; j < M; ++j) {
      printf("%f", A[i][j]);
      if (j < M - 1) {
        printf(", ");
      }
    }
    printf("]\n");
  }
}

void print_vector(size_t N, double x[N]) {
  printf("[");
  for (size_t i = 0; i < N; ++i) {
    printf("%f", x[i]);
    if (i < N - 1) {
      printf(", ");
    }
  }
  printf("]\n");
}

int main(void) {
  double A[][5] = {
    {1,2,3,4,5},
    {.1,.2,.3,.4,.5},
    {0,.8,0,0,0}
  };
  double x[] = {1,2,3,4,5};
  double b[3];
  matrix_vector_prod(3, 5, A, x, b);
  print_vector(3, b);
}
