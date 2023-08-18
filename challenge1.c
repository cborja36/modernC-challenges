#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**********************/
/***** Merge Sort *****/
/**********************/

void copy(double working_arr[], double arr[], size_t l, size_t r) {
  for (size_t i = 0; i < r - l; ++i) {
    arr[l + i] = working_arr[i];
  }
}

void merge(double arr[], size_t l, size_t m, size_t r) {
  double working_arr[r - l];
  size_t i = l, j = m;
  for (size_t k = 0; k < r - l; ++k) {
    if (i < m && (j >= r || arr[i] <= arr[j])) {
      working_arr[k] = arr[i++];
    } else {
      working_arr[k] = arr[j++];
    }
  }
  copy(working_arr, arr, l, r);
}

void MergeSort(double arr[], size_t l, size_t r) {
  if (r - l <= 1) return;

  size_t m = (l + r) / 2;
  MergeSort(arr, l, m);
  MergeSort(arr, m, r);

  merge(arr, l, m, r);
}

/******************************/
/***** Auxiliar functions *****/
/******************************/

bool is_sorted(double arr[], size_t n) {
  for (size_t i = 0; i < n - 1; ++i) {
    if (arr[i] > arr[i + 1]) return false;
  }
  return true;
}

void print_array(double arr[], size_t n) {
  for (size_t i = 0; i < n; ++i) {
    printf("%.2e ", arr[i]);
  }
  printf("\n");
}

int main(int argc, char *argv[]) {
  // Usage: ./pruebas [--silent] [N]
  bool silent = false;
  size_t N = 10;

  puts("Parsing command line arguments...");
  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "--silent") == 0) {
      silent = true;
    } else {
      N = atoi(argv[i]);
    }
  }

  puts("Initializing array...");
  double arr[N];

  for (int i = 0; i < 10; ++i) {
    puts("Filling array with random values...");
    srand(time(NULL));
    for (size_t i = 0; i < N; ++i) {
      arr[i] = rand();
    }
    if (!silent) {
      printf("Initial array: ");
      print_array(arr, N);
    }

    puts("Sorting array...");
    MergeSort(arr, 0, N);
    if (!is_sorted(arr, N)) {
      printf("Error: array is not sorted\n");
      return EXIT_FAILURE;
    } else if (!silent) {
      printf("\nSorted array: ");
      print_array(arr, N);
    }
  }

  return EXIT_SUCCESS;
}
