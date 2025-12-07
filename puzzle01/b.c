#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main() {

  FILE *fp = fopen("input.txt", "r");
  if (!fp) {
    perror("Unable to open file!");
    return 1;
  }

  char buffer[32];
  int position = 50;
  long password = 0;

  while (fgets(buffer, sizeof(buffer), fp)) {

    char dir = buffer[0];
    char *endptr;
    int distance = strtol(buffer + 1, &endptr, 10);
    int new_position;

    int zero_at;
    long crosses = 0;
    assert(position >= 0 && position < 100);
    assert(distance > 0);

    if (dir == 'R') {
      int dist_to_0 = 100 - position;
      if (distance >= dist_to_0) {
        crosses = 1 + (distance - dist_to_0) / 100;
      }
      position = (position + distance) % 100;

    } else if (dir == 'L') {
      int dist_to_0 = position;
      if (position == 0) {
        dist_to_0 = 100;
      }
      if (distance >= dist_to_0) {
        crosses = 1 + (distance - dist_to_0) / 100;
      }
      position = position - distance % 100;
      if (position < 0) {
        position += 100;
      }

    } else {
      printf("Invalid direction\n");
      return 1;
    }
    printf("%ld\n", crosses);
    password += crosses;
  }

  printf("%ld\n", password);
  return 0;
}
