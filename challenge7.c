#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

size_t arcs[][2] = {{1, 2}, {2, 5}, {5, 9}, {5, 10}, {2, 6}, {1, 3},
                    {1, 4}, {4, 8}, {4, 7}, {7, 12}, {7, 11}};

void adjacency_matrix(size_t arcs[][2], size_t n_arcs, size_t n_nodes,
                      bool adj_matrix[n_nodes][n_nodes]) {
  for (size_t i = 0; i < n_nodes; ++i) {
    for (size_t j = 0; j < n_nodes; ++j) {
      adj_matrix[i][j] = 0;
    }
  }
  for (size_t i = 0; i < n_arcs; ++i) {
    size_t x = arcs[i][0];
    size_t y = arcs[i][1];
    adj_matrix[x][y] = true;
    adj_matrix[y][x] = true;
  }
}

void print_matrix(size_t n_nodes, bool adj_matrix[n_nodes][n_nodes]) {
  for (size_t i = 0; i < n_nodes; ++i) {
    for (size_t j = 0; j < n_nodes; ++j) {
      printf("%d ", adj_matrix[i][j]);
    }
    printf("\n");
  }
}

int main(void) {
  bool adj_matrix[13][13];
  adjacency_matrix(arcs, 11, 13, adj_matrix);
  print_matrix(13, adj_matrix);
}
