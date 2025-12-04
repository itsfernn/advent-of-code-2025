#include <stdio.h>
#include <stdlib.h>

int main(){
  FILE *fp = fopen("input.txt", "r");

  if (fp == NULL){
    perror("file not found");
    return 1;
  }

  char buffer[256];
  while(fgets(buffer, sizeof(buffer), fp) != NULL){
    printf("%s\n", buffer);
  }

  fclose(fp);

  return 0;
}
