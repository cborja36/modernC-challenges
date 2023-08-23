// Author: Borja Castillo
// Date: 22/08/2023
// Usage:
// ./challenge3 N
// Description:
// This program calculates the value of pi using the Leibniz formula
// and compares it with the real value of pi. The precision of the
// approximation is given by the number of decimals of pi that are
// correct.

/* Sea f(n) = sum_{i=0}^{n} (-1)^{i}/(2i+1) */
/* Sabemos que lim f(n) = pi/4 cuando n -> inf */

/* Ahora, como esto es una serie alternada podemos acotar el error mediante */
/* la siguiente fórmula
 * (https://en.wikipedia.org/wiki/Alternating_series#Approximating_sums): */
/* |4*f(N) - pi| <= 4|a_{N+1}| */

/* Entonces, para que el error sea menor que 10^{-n} tenemos que encontrar */
/* el menor N tal que 4|a_{N+1}| < 10^{-n} */

/* 4|a_{N+1}| = 4|(-1)^{N+1}/(2(N+1)+1)| = 4/(2N+3) < 10^{-n} */
/* con lo que concluimos que 2 * 10^{n} - 3/2 < N */

#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // For sleep function on Unix-like systems

void prettyu(size_t n) {
  if (n < 1000) {
    printf("%zu", n);
    return;
  }
  prettyu(n / 1000);
  printf(",%03zu", n % 1000);
}

void print_progress(size_t iteration, double estimation, bool return_to_top) {
  printf("\r>> Iteration (");
  prettyu(iteration);
  printf(") <<\n");
  printf("Real value: %.16f\n", M_PI);
  printf("Estimation: %.16f\n", 4 * estimation);
  printf("Error:      %.12e", fabs(4 * estimation - M_PI));
  if (return_to_top) {
    printf("\033[3A");
  }
}

double f(size_t n, bool verbose) {
  double result = 0;
  double current_term;
  bool first = true;
  for (size_t i = 0; i <= n; ++i) {
    current_term = 1. / (2 * i + 1);
    if (i % 2 == 1) current_term *= -1;
    result += current_term;

    if (verbose && i % 10000000 == 0) {
      if (!first) {
        print_progress(i, result, true);
      } else {
        print_progress(i, result, false);
        first = false;
      }
    }
  }
  return result;
}

size_t calculate_precision(size_t n_decimals) {
  double threshold = 2 * pow(10, n_decimals) - 3. / 2;
  return ceil(threshold);
}

int main() { f(SIZE_T_MAX, true); }
