#include "./type_deduct.h"

Token tokens[100];
int token_length = 0;

void lexer_tokenize(const char* filename)
{
  FILE* file = open_file(filename);
  char word[100];
  
  while(fscanf(file, "%s", word) != EOF)
    {
      tokens[token_length] = check_for_token(word);
      token_length++;
    }

  for(int i = 0; i < token_length; i++)
    {
      printf("%d\n", tokens[i].token_type);
    }

  fclose(file);
}
