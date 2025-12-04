#include <stdio.h>
#include <string.h>

// check if surronding 8 cells contain @ char
int check_cell(int y, int x, int num_rows, int num_cols, char graph[][num_cols]) {
  // cast graph back to 2D array
  if (graph[y][x] != '@') {
    return 0;
  }

  int neighbor_count = 0;

  for (int i = -1; i <= 1; i++) {
    int new_x = x + i;
    if (new_x < 0 || new_x >= num_cols)
      continue;

    for (int j = -1; j <= 1; j++) {
      if (i == 0 && j == 0)
        continue;

      int new_y = y + j;
      if (new_y < 0 || new_y >= num_rows)
        continue;

      if (graph[new_y][new_x] == '@' || graph[new_x][new_y] == 'x')
        neighbor_count++;
    }
  }

  return neighbor_count < 4;
}

int main() {

  FILE *fp = fopen("puzzle04/input.txt", "r");

  if (fp == NULL) {
    printf("Error opening file\n");
    return 1;
  }

  int num_rows = 0;
  int num_cols= 0;

  char buffer[256];
  while (fgets(buffer, sizeof(buffer), fp)) {
    num_rows++;
    int len = strlen(buffer);
    if (len > num_cols)
      num_cols = len-1;
  }

  rewind(fp);

  char graph[num_rows][num_cols];
  int row_idx = 0;
  while (fgets(buffer, sizeof(buffer), fp)) {
    memcpy(graph[row_idx], buffer, num_cols);
    row_idx++;
  }


  fclose(fp);

  int sum = 0;
  char current_graph[num_rows][num_cols];
  memcpy(current_graph, graph, sizeof(graph));

  int current_sum = 1;
  while(current_sum > 0){
    current_sum = 0;
    for (int i = 0; i < num_rows; i++) {
      for (int j = 0; j < num_cols; j++) {
        int result = check_cell(i, j, num_rows, num_cols, current_graph);
        if (result) {
          current_sum += result;
          current_graph[i][j] = 'x';
          graph[i][j] = '.';
        }
      }
    }
    sum += current_sum;
    memcpy(current_graph, graph, sizeof(graph));
  }

  for (int i = 0; i < num_rows; i++) {
    for (int j = 0; j < num_cols; j++) {
      printf("%c", graph[i][j]);
    }
    printf("\n");
  }


  printf("%d\n", sum);
  return 0;
}
