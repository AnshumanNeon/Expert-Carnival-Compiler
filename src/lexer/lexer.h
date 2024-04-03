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

  char ch = fgetc(file);

  int line_n = 1, col_n = 1, i = 0;

  while(!feof(file)) {
    ch = fgetc(file);

    // line numbers
    if(ch == '\n') {
      line_n++;
      col_n = 1;
    }

    tokens[i].line = line_n;

    // col number
    if(ch == tokens[i].token[0]) {
      tokens[i].col = col_n;

      // go to next token only after assigning both line and column
      i++;
    }

    col_n++;
  }

  for(int i = 0; i < tokens_length; i++) {
    printf("%s : line = %d, col = %d\n", tokens[i].token, tokens[i].line, tokens[i].col);
  }

  fclose(file);
}
