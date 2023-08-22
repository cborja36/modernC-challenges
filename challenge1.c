// Creator: Borja Castillo
// Date: 18/08/2023
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
/***** Slow Sort *****/
/**********************/

void SlowSort(double arr[], size_t l, size_t r) {
  size_t n = l + r;
  double working_arr[n];
  for (size_t i = 0; i < n; ++i) {
    size_t n_minor = 0;
    for (size_t j = 0; j < n; ++j) {
      if (arr[i] > arr[j]) {
        ++n_minor;
      }
    }
    working_arr[n_minor] = arr[i];
  }
  for (size_t i = 0; i < n; ++i) {
    arr[i] = working_arr[i];
  }
}

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

typedef void (*SortFunc)(double[], size_t, size_t);

void measureSort(SortFunc sort, const char *name, size_t N, int iterations,
                 bool verbose, double *mean, double *std_dev) {
  double arr[N];
  double total_time = 0;
  double times[iterations];

  for (int i = 0; i < iterations; ++i) {
    for (size_t j = 0; j < N; ++j) {
      arr[j] = rand();
    }

    if (verbose) {
      printf("\n--- Iteration %d ---\n", i + 1);
      printf("\nInitial array: ");
      print_array(arr, N);
    }

    clock_t start, end;

    start = clock();
    sort(arr, 0, N);
    end = clock();

    times[i] = (double)(end - start) / CLOCKS_PER_SEC;
    total_time += times[i];

    if (!is_sorted(arr, N)) {
      printf("Error: array is not sorted with %s\n", name);
      exit(EXIT_FAILURE);
    }
  }

  *mean = total_time / iterations;

  double variance = 0;
  for (int i = 0; i < iterations; ++i) {
    variance += (times[i] - *mean) * (times[i] - *mean);
  }
  *std_dev = sqrt(variance / iterations);
}

/****************/
/***** Main *****/
/****************/

typedef struct SortAlgorithm SortAlgorithm;
struct SortAlgorithm {
  SortFunc func;
  const char *name;
  double mean;
  double std_dev;
};

int main(int argc, char *argv[]) {
  /* Default values */
  bool verbose = false;
  size_t N = 1000;
  int iterations = 100;

  /* Parse command line arguments */
  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "--help") == 0) {
      puts(
          "Usage: ./program [--verbose] [--array_length <length>] "
          "[--n_iterations <iterations>]");
      puts("Options:");
      puts("  --verbose       : Display verbose output for each iteration.");
      puts(
          "  --array_length  : Set the length of the array for sorting. "
          "Default is 1000.");
      puts(
          "  --n_iterations  : Set the number of iterations to run. Default "
          "is 100.");
      return EXIT_SUCCESS;  // If --help is provided, display the help and exit
                            // the program.
    } else if (strcmp(argv[i], "--verbose") == 0) {
      verbose = true;
    } else if (strcmp(argv[i], "--array_length") == 0 && i + 1 < argc) {
      N = atoi(argv[++i]);
    } else if (strcmp(argv[i], "--n_iterations") == 0 && i + 1 < argc) {
      iterations = atoi(argv[++i]);
    }
  }

  SortAlgorithm algorithms[] = {
      {QuickSort, "QuickSort"},
      {MergeSort, "MergeSort"},
      {SlowSort, "SlowSort"},
  };

  size_t algo_count = sizeof(algorithms) / sizeof(algorithms[0]);

  for (size_t i = 0; i < algo_count; ++i) {
    measureSort(algorithms[i].func, algorithms[i].name, N, iterations, verbose,
                &algorithms[i].mean, &algorithms[i].std_dev);
    printf("\n--- %s ---\n", algorithms[i].name);
    printf("Mean Time: %.2e seconds\nStandard Deviation: %.2e\n",
           algorithms[i].mean, algorithms[i].std_dev);
  }

  return EXIT_SUCCESS;
}
