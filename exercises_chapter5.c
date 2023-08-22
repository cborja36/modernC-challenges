#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void printBits(unsigned x) {
  for (int i = sizeof(x) * 8 - 1; i >= 0; i--) {
    if ((i + 1) % 4 == 0 && (i+1) != sizeof(x) * 8) printf(" ");
    printf("%d", (x & (1 << i)) != 0);
  }
  printf("\n");
}

int main(void) {
  printf("INT_MAX: %d\n", INT_MAX);
  printf("INT_MIN: %d\n", INT_MIN);
  printf("\n");

  printf("LONG_MAX: %ld\n", LONG_MAX);
  printf("LONG_MIN: %ld\n", LONG_MIN);
  printf("\n");

  printf("LLONG_MAX: %lld\n", LLONG_MAX);
  printf("LLONG_MIN: %lld\n", LLONG_MIN);
  printf("\n");

  printf("UINT_MAX: %u\n", UINT_MAX);
  printf("\n");

  printf("ULONG_MAX: %lu\n", ULONG_MAX);
  printf("\n");

  printf("ULLONG_MAX: %llu\n", ULLONG_MAX);

  // Exercice 1: This line shows that the type of -2147483648 is long (8 bytes)
  // although -2147483648 fits in an int.
  puts("\nExercice 1:");
  printf("sizeof(3): %zu\n", sizeof(-2147483648));

  // Exercice 2:
  puts("\nExercice 2:");
  printf("%u\n", -0x80000000);

  // Exercice 3:
  puts("\nExercice 3:");
  printf("%u\n", -1U);
  printf("%lu\n", -1UL);
  printf("%llu\n", -1ULL);

  unsigned A = 240;
  unsigned B = 287;
  unsigned V = UINT_MAX;

  printf("\nA = %u -> ", A);
  printBits(A);
  printf("B = %u -> ", B);
  printBits(B);
  printf("V = %u -> ", V);
  printBits(V);

  // Exercise 5
  printf("\nA\\B = A - (A&B) = %u -> ", A - (A & B));
  printBits(A - (A & B));

  // Exercise 6
  printf("\nV + 1 = %u -> ", V + 1);
  printBits(V + 1);

  // Exercise 7
  printf("\nA^B = %u -> ", A ^ B);
  printBits(A ^ B);
  printf("(A - (A&B)) + (B - (A&B)) = %u -> ", (A - (A & B)) + (B - (A & B)));
  printBits((A - (A & B)) + (B - (A & B)));
  printf("A + B - 2*(A&B) = %u -> ", A + B - 2 * (A & B));
  printBits(A + B - 2 * (A & B));

  // Exercise 8
  printf("\nA|B = %u -> ", A | B);
  printBits(A | B);
  printf("A + B - (A&B) = %u -> ", A + B - (A & B));
  printBits(A + B - (A & B));

  // Exercise 9
  printf("\n~B = %u -> ", ~B);
  printBits(~B);
  printf("V - B = %u -> ", V - B);
  printBits(V - B);

  // Exercise 10
  printf("\n-B = %u -> ", -B);
  printBits(-B);
  printf("~B + 1 = %u -> ", ~B + 1);
  printBits(~B + 1);
}
