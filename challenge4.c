#include <stdio.h>
#include <stdlib.h>

void printArray(size_t arr[], size_t n) {
  printf("[");
  for (size_t i = 0; i < n; i++) {
    if (arr[i] != SIZE_MAX) {
      printf("{%zu: %zu}", i, arr[i]);
    } else {
      printf("{%zu: #}", i);
    }
    if (i != n - 1) printf(", ");
  }
  printf("]\n");
}

void fillParent(size_t parent[], size_t n) {
  for (size_t i = 0; i < n; i++) {
    parent[i] = i + 1;
  }
  parent[50] = SIZE_MAX;
  parent[n - 1] = SIZE_MAX;
}

size_t Find(size_t parent[], size_t i) {
  if (parent[i] == SIZE_MAX) return i;
  return Find(parent, parent[i]);
}

void FindReplace(size_t parent[], size_t i, size_t new_value) {
  size_t next = parent[i];
  if (i == new_value) {
    parent[i] = SIZE_MAX;
  } else {
    parent[i] = new_value;
  }
  if (next != SIZE_MAX) {
    FindReplace(parent, next, new_value);
  }
}

void FindCompress(size_t parent[], size_t i) {
  size_t p = Find(parent, i);
  FindReplace(parent, i, p);
}

void Union(size_t parent[], size_t i, size_t j) {
  FindCompress(parent, i);
  size_t pi = Find(parent, i);
  FindReplace(parent, j, pi);
}

int main(void) {
  size_t const SIZE = 8;

  size_t parent[SIZE] = {1, 2, 4, SIZE_MAX, SIZE_MAX, 4, 0, 3};
  Union(parent, 1, 7);

  printArray(parent, SIZE);
}
