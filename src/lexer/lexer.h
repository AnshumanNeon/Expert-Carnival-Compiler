#include "./scanner.h"
#include "./token_functions.h"
#include <string.h>
#include <ctype.h>

int myAtoi(char str[])
{
  int is = 0;
  for (int i = 0; i < (int)strlen(str); i++) {
    if(!isdigit(str[i]))
      {
	is = -1;
	return is;
      }
  }

  return is;
}

Token tokens[100];
int token_length = 0;

Token check_for_token(char string[])
{
  if(myAtoi(string) != -1)
    {
      return convert_to_symbol_token();
    }
  
  else
    {
      return convert_to_keyword_token();
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
      printf("%d\n", tokens[i].token_type);
    }

  fclose(file);
}
