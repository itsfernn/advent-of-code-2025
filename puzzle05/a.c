#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct range {
  long start;
  long end;
};


int is_in_range(long value, struct range r) {
  if (value < r.start)
    return -1;
  else if( value > r.end)
    return 1;
  else 
    return 0;
}

//inplace quicksort
void sort_ranges(struct range* ranges, int num_ranges) {
  if (num_ranges <= 1)
    return;

  struct range pivot = ranges[num_ranges - 1];
  int i = -1;

  for (int j = 0; j < num_ranges - 1; j++) {
    if (ranges[j].start <= pivot.start) {
      i++;
      struct range temp = ranges[i];
      ranges[i] = ranges[j];
      ranges[j] = temp;
    }
  }

  struct range temp = ranges[i + 1];
  ranges[i + 1] = ranges[num_ranges - 1];
  ranges[num_ranges - 1] = temp;

  sort_ranges(ranges, i + 1);
  sort_ranges(ranges + i + 2, num_ranges - i - 2);
}

void merge_ranges(struct range* ranges, int* num_ranges) {
  if (*num_ranges <= 1)
    return;
  
  sort_ranges(ranges, *num_ranges);

  int index = 0;

  for (int i = 1; i < *num_ranges; i++) {
    if (ranges[index].end >= ranges[i].start) {
      if (ranges[index].end < ranges[i].end) {
        ranges[index].end = ranges[i].end;
      }
    } else {
      index++;
      ranges[index] = ranges[i];
    }
  }

  *num_ranges = index + 1;
}


int is_fresh(long value, struct range* ranges, int num_ranges){
  if (num_ranges <= 0)
    return 0;

  int mid = num_ranges / 2;

  int result = is_in_range(value, ranges[mid]);

  if (result == 0)
    return 1;
  else if (result < 0)
    return is_fresh(value, ranges, mid);
  else
    return is_fresh(value, ranges + (mid + 1), num_ranges - (mid + 1));
}


int main() {
  FILE *fp = fopen("puzzle05/input.txt", "r");

  if (fp == NULL) {
    fprintf(stderr, "Error opening file\n");
    return 1;
  }


  struct range ranges[256];
  int num_ranges = 0;

  char buffer[64];
  while(fgets(buffer, sizeof(buffer), fp)) {
    //printf("%s", buffer);

    if (buffer[0] == '\n') break;

    char *inner_ptr;

    char* start = strtok(buffer, "-");
    char* end = strtok(NULL, "-");
    struct range range;
    range.start = strtol(start, &inner_ptr, 10);
    range.end = strtol(end, &inner_ptr, 10);

    ranges[num_ranges] = range;
    num_ranges++;
  }


  merge_ranges(ranges, &num_ranges);

  int sum = 0;
  while(fgets(buffer, sizeof(buffer), fp)) {
    char *inner_ptr;
    long value = strtol(buffer, &inner_ptr, 10);
    if (is_fresh(value, ranges, num_ranges))
      sum++;
  }

  fclose(fp);

  printf("Number of fresh values: %d\n", sum);


  return 0;
}
