#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./tokens.h"

Token tokens[100];
int tokens_length = 0;

void lexer_tokenize(const char* filename)
{
  FILE* file = fopen(filename, "r");
  if(!file) {
    printf("error\n");
    return;
  }

  char word[50];
  
  while(!feof(file)) {
    fscanf(file, "%s", word);

    strcpy(tokens[tokens_length].token, word);
    tokens_length++;
  }

  for(int i = 0; i < tokens_length; i++) {
    printf("%s\n", tokens[i].token);
  }

  fclose(file);
}
