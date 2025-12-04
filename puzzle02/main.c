#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isRepeatingPattern(const char *s) {
    int len = strlen(s);

    for(int i = 2; i <= len; i++){
      if (len % i != 0)
        continue;

      int part_len = len / i;

      int result = 1;
      for (int j = part_len; j < len; j += part_len) {
        if (strncmp(s, s + j, part_len) != 0) {
          result = 0;
          break;
        }
      }

      if (result){
        return 1;
      }
    }
    return 0;
}

int main(){
  FILE *fp = fopen("puzzle02/input.txt", "r");

  if (fp == NULL){
    perror("file not found");
    return 1;
  }

  char buffer[1024];
  char* result = fgets(buffer, sizeof(buffer), fp);
  fclose(fp);

  if (result == NULL){
    perror("Reading File Failed");
    return 1;
  }

  char *output_ptr, *inner_ptr;

  char* range_token = strtok_r(buffer, ",", &output_ptr);

  long long sum = 0;

  while(range_token != NULL){
    char* start_char = strtok_r(range_token, "-", &inner_ptr);
    char* end_char = strtok_r(NULL, "-", &inner_ptr);

    if (start_char == NULL || end_char == NULL)
      break;

    long start = strtol(start_char, NULL, 10);
    long end = strtol(end_char, NULL, 10);

    //printf("%ld-%ld,", start, end);
    range_token = strtok_r(NULL, ",", &output_ptr);

    char long_char[100];
    for (long i = start; i <=end; i++){
      sprintf(long_char, "%ld", i);
      int result = isRepeatingPattern(long_char);

      if (result){
        printf("%s\n", long_char);
        sum += i;
      }
    }

  }

  printf("RESULT: %lld\n", sum);




  return 0;
}
