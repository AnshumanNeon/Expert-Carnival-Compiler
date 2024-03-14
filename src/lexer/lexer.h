#include "./scanner.h"
#include "./token_functions.h"
#include <string.h>

int myAtoi(char* str)
{
  int isDigit = 0;
  unsigned long j = 0;
  while(j < strlen(str) && isDigit == 0){
    if(str[j] >= 48 && str[j] <= 57)
      isDigit = 0;
    else
      isDigit = 1;
    j++;
  }

  return isDigit;
}

Token tokens[100];
int token_length = 0;

Token check_for_token(char string[])
{
  if(myAtoi(string) > 0)
    {
      return convert_to_symbol_token();
    }

  else
    {
      Token error_token;
      error_token.token_type = -1;
      return error_token;
    }
}

void lexer_tokenize(const char* filename)
{
  FILE* file = open_file(filename);
  char word[100];
  
  while(fscanf(file, "%s", word) != EOF)
    {
      printf("%s\n", word);

      tokens[token_length] = check_for_token(word);
      token_length++;
    }

  for(int i = 0; i < token_length; i++)
    {
      printf("%d", tokens[token_length].token_type);
    }

  fclose(file);
}
