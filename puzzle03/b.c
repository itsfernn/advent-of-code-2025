#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int find_max_idx(char* string, int length){
    int max_idx = 0;
    assert(isalnum(string[max_idx]));
    int max = string[max_idx] - '0'; // set max to first digit
    for(int i = 1; i < length; i++){
      assert(isalnum(string[i]));  
      int num = string[i] - '0';
      if (num > max){
        max = num;
        max_idx = i;
      }
    }
    return max_idx;
}


int main(){
  FILE *fp = fopen("puzzle03/input.txt", "r");

  if (fp == NULL){
    perror("Unable to open file");
    return 1;
  }

  long sum = 0;
  char buffer[256];
  while(fgets(buffer, sizeof(buffer), fp)){
    int len = strlen(buffer)-1; // remove newline form string length
    int indices[12];
    char numbers[12];
    long number;

    for (int i = 0; i < 12; i++){
      int start;
      if (i == 0){
        start = 0;
      }else{
        start = indices[i-1] + 1;
      }

      int remaining = 12 - (i+1);
      int current_len = len - start - remaining;

      indices[i] = find_max_idx(buffer+start, current_len) + start;
      numbers[i] = buffer[indices[i]];
    }

    char * endptr;
    number = strtol(numbers, &endptr, 10);
    sum += number;

    printf("%s", buffer);
    char str1[256];
    memset(str1, ' ', 255);
    str1[255] = '\0';
    for(int i = 0; i < 12; i++){
      str1[indices[i]] = numbers[i]; 
    }
    printf("%s\n", str1);
    printf("%ld\n\n", number);

  }
  printf("%ld\n", sum);

  return 0;
}
