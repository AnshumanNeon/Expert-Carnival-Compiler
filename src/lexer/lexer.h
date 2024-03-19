#include "./scanner.h"
#include "./token_functions.h"
#include <string.h>
#include <ctype.h>

int is_int(char str[])
{
  int is = 0;
  for (int i = 0; i < (int)strlen(str); i++) {
    if(isdigit(str[i]) == 0)
      {
	is = -1;
	return is;
      }
  }

  return is;
}

int is_operator(char* str)
{
  int is_operator = -1;

  if(strcmp(str, "+") == 0) is_operator = 0;
  if(strcmp(str, "-") == 0) is_operator = 1;
  if(strcmp(str, "*") == 0) is_operator = 2;
  if(strcmp(str, "/") == 0) is_operator = 3;
  if(strcmp(str, "%") == 0) is_operator = 4;
  if(strcmp(str, "=") == 0) is_operator = 5;
  if(strcmp(str, "&") == 0) is_operator = 6;
  if(strcmp(str, "|") == 0) is_operator = 7;
  if(strcmp(str, "=") == 0) is_operator = 8;
  if(strcmp(str, "<") == 0) is_operator = 9;
  if(strcmp(str, ">") == 0) is_operator = 10;
  
  return is_operator;
}

Token tokens[100];
int token_length = 0;

Token check_for_token(char string[])
{
  if(is_int(string) != -1)
    {
      return convert_to_symbol_token();
    }

  if(is_operator(string) > -1) return convert_to_operator_token();
  
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
      tokens[token_length] = check_for_token(word);
      token_length++;
    }

  for(int i = 0; i < token_length; i++)
    {
      printf("%d\n", tokens[i].token_type);
    }

  fclose(file);
}
