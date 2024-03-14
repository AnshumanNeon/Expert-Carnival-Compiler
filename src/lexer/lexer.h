#include "./scanner.h"
#include "./token_functions.h"

int myAtoi(char* str)
{
    // Initialize result
    int res = -1;
 
     // subtract the code from '0' to get numerical
    // value and multiply res by 10 to shuffle
    // digits left to update running total
    for (int i = 0; str[i] != '\0'; ++i)
        res = res * 10 + str[i] - '0';
  
    return res;
}

Token tokens[100];
int token_length = 0;

Token check_for_token(char string[])
{
  if(myAtoi(string) > -1)
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
