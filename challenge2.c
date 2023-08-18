#include <math.h>
#include <stdio.h>

double Dsin(double x) {
  double eps = 0.00001;
  return (sin(x + eps) - sin(x)) / eps;
}
int main(void) {
  printf("sin'(0) = %f\n", Dsin(0));
  printf("sin'(1) = %f\n", Dsin(1));
  printf("sin'(3.14) = %f\n", Dsin(3.14));
  printf("sin'(6.28) = %f\n", Dsin(6.28));
}
