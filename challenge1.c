// Creator: Borja Castillo
// Date: 18/08/2023
// Description:
//  This program compares the performance of QuickSort and MergeSort
//  algorithms. The user can specify the length of the array and the number of
//  iterations to be performed. The program will print the mean time and the
//  standard deviation of the execution time of each algorithm.
//  Usage:
//  ./challenge1 [--verbose] [--array_length N] [--n_iterations N]

#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**********************/
/***** Quick Sort *****/
/**********************/

void QuickSort(double arr[], size_t l, size_t r) {
  if (r - l <= 1) return;

  double pivot = arr[r - 1];
  double working_arr[r - l - 1];
  size_t start = 0;
  size_t end = r - l - 2;

  for (size_t i = l; i < r - 1; ++i) {
    if (arr[i] <= pivot) {
      working_arr[start++] = arr[i];
    } else {
      working_arr[end--] = arr[i];
    }
  }

  for (size_t i = 0; i < start; ++i) {
    arr[l + i] = working_arr[i];
  }
  arr[l + start] = pivot;
  for (size_t i = start; i < r - l - 1; ++i) {
    arr[l + i + 1] = working_arr[i];
  }

  QuickSort(arr, l, l + start);
  QuickSort(arr, l + start + 1, r);
}

/**********************/
/***** Merge Sort *****/
/**********************/

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
  for (size_t i = 0; i < r - l; ++i) {
    arr[l + i] = working_arr[i];
  }
}

void MergeSort(double arr[], size_t l, size_t r) {
  if (r - l <= 1) return;

  size_t m = (l + r) / 2;
  MergeSort(arr, l, m);
  MergeSort(arr, m, r);

  merge(arr, l, m, r);
}

/*****************************/
/***** Testing functions *****/
/*****************************/

bool is_sorted(double arr[], size_t n) {
  for (size_t i = 0; i < n - 1; ++i) {
    if (arr[i] > arr[i + 1]) return false;
  }
  return true;
}

void print_array(double arr[], size_t n) {
  printf("[");
  for (size_t i = 0; i < n - 1; ++i) {
    printf("%.2e, ", arr[i]);
  }
  printf("%.2e]", arr[n - 1]);
  printf("\n");
}

/****************/
/***** Main *****/
/****************/

int main(int argc, char *argv[]) {
  // Default values
  bool verbose = false;
  size_t N = 1000;
  int iterations = 100;

  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "--verbose") == 0) {
      verbose = true;
    } else if (strcmp(argv[i], "--array_length") == 0 && i + 1 < argc) {
      N = atoi(argv[++i]);

    } else if (strcmp(argv[i], "--n_iterations") == 0 && i + 1 < argc) {
      iterations = atoi(argv[++i]);
    }
  }

  double arr1[N];
  double arr2[N];
  double total_time_qs = 0, total_time_ms = 0;
  double times_qs[iterations], times_ms[iterations];

  for (int i = 0; i < iterations; ++i) {
    for (size_t j = 0; j < N; ++j) {
      double val = rand();
      arr1[j] = val;
      arr2[j] = val;
    }

    if (verbose) {
      printf("\n--- Iteration %d ---\n", i + 1);
      printf("\nInitial array: ");
      print_array(arr1, N);
    }

    clock_t start, end;

    start = clock();
    QuickSort(arr1, 0, N);
    end = clock();
    times_qs[i] =
        (double)(end - start) / CLOCKS_PER_SEC;  // Store individual time
    total_time_qs += times_qs[i];

    start = clock();
    MergeSort(arr2, 0, N);
    end = clock();
    times_ms[i] =
        (double)(end - start) / CLOCKS_PER_SEC;  // Store individual time
    total_time_ms += times_ms[i];

    if (!is_sorted(arr1, N) || !is_sorted(arr2, N)) {
      printf("Error: array is not sorted\n");
      return EXIT_FAILURE;
    } else if (verbose) {
      printf("\nQuickSort: ");
      print_array(arr1, N);
      printf("\nMergeSort: ");
      print_array(arr2, N);
    }
  }

  double mean_qs = total_time_qs / iterations;
  double mean_ms = total_time_ms / iterations;

  double variance_qs = 0, variance_ms = 0;
  for (int i = 0; i < iterations; ++i) {
    variance_qs += (times_qs[i] - mean_qs) * (times_qs[i] - mean_qs);
    variance_ms += (times_ms[i] - mean_ms) * (times_ms[i] - mean_ms);
  }
  double std_dev_qs = sqrt(variance_qs / iterations);
  double std_dev_ms = sqrt(variance_ms / iterations);

  puts("\n--- QuickSort ---");
  printf("Mean Time: %.2e seconds\nStandard Deviation: %.2e\n", mean_qs,
         std_dev_qs);

  puts("\n--- MergeSort ---");
  printf("Mean Time: %.2e seconds\nStandard Deviation: %.2e\n", mean_ms,
         std_dev_ms);

  return EXIT_SUCCESS;
}
