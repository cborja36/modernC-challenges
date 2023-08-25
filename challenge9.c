#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define RESET "\033[0m"
#define RED "\033[31m"

bool Factor(size_t n, bool first) {
  size_t left = SIZE_MAX;
  for (size_t i = 2; i <= n / 2; ++i) {
    if (n % i == 0) {
      printf("%zu ", i);
      left = n / i;
      break;
    }
  }
  if (left == SIZE_MAX) {
    if (first) {
      printf("%zu ", n);
      return true;
    } else {
      printf("%zu", n);
      return false;
    }
  } else {
    Factor(left, false);
  }
  return false;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: %s <number>\n", argv[0]);
    return 1;
  }
  size_t n = atoi(argv[1]);

  bool is_prime;
  for (size_t i = 2; i <= n; ++i) {
    printf("%zu: ", i);
    is_prime = Factor(i, true);
    if (is_prime) {
      printf(RED " <- prime!" RESET);
    }
    printf("\n");
  }

  return EXIT_SUCCESS;
}
