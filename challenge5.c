#include <stdio.h>
#include <stdlib.h>
#include <tgmath.h>

double const eps = 1.0e-7;

typedef double complex dcomplex;

dcomplex D(dcomplex F(dcomplex), dcomplex x) {
  return (F(x + eps) - F(x)) / eps;
}

int main(void) {
  dcomplex x = 1 + I;
  dcomplex d = D(csin, x);
  printf("cos(1 + i) = %f + %fi\n", creal(cos(x)), cimag(cos(x)));
  printf("d = %f + %fi\n", creal(d), cimag(d));
}
