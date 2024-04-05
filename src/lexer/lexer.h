#include <stdio.h>
#include <string.h>
#include "./tokens.h"

Token tokens[100];
int tokens_length = 0;

char* get_contents(const char* filename) {
  char* contents = NULL;

  // open file
  FILE* file = fopen(filename, "r");
  if(!file) {
    printf("error opening file\n");
    return contents;
  }

  // get size
  fseek(file, 0, SEEK_END);
  size_t file_size = ftell(file);
  rewind(file);

  // allocate to char*
  char* buffer = (char*)malloc(file_size + 1);
  if(buffer == NULL) {
    printf("error allocating\n");
    return contents;
  }

  // check for bytes read
  size_t bytes_read = fread(buffer, sizeof(char), file_size, file);
  if(bytes_read < file_size) {
    printf("error reading size\n");
    return contents;
  }

  // add an eof
  buffer[bytes_read] = '\0';

  // close
  fclose(file);

  // copy to contents
  contents = buffer;
  free(buffer);
  
  return contents;
}

token_type get_type(char token, char next_token) {
  switch(token) {
  case '+': return ADDITION_TOKEN; break;
  case '-': return SUB_TOKEN; break;
  case '*': return MUL_TOKEN; break;
  case '/': return DIV_TOKEN; break;
  case '%': return MOD_TOKEN; break;
  case '^': return EXP_TOKEN; break;
  case '<':
    if(next_token == '=') {return LESSER_OR_EQUAL_TOKEN; break;}
    else {return LESSER_THAN_TOKEN; break;}
  case '>': 
    if(next_token == '='){ return GREATER_OR_EQUAL_TOKEN; break;}
    else {return GREATER_THAN_TOKEN; break;}
  case '=': 
    if(next_token == '=') {return EQUAL_EQUAL_TOKEN; break;}
    else {return EQUAL_TOKEN; break;}
  case '!': 
    if(next_token == '=') {return NOT_EQUAL_TOKEN; break;}
    else {return NOT_TOKEN; break;}
  case '&': 
    if(next_token == '&') {return AND_TOKEN; break;}
    else {return ERROR_TOKEN; break;}
  case '|': 
    if(next_token == '|') {return OR_TOKEN; break;}
    if(next_token == '=') {return AND_OR_TOKEN; break;}
    else {return ERROR_TOKEN; break;}
  case 'i': 
    if(next_token == 'f') {return IF_TOKEN; break;}
  default: return ERROR_TOKEN; break;
  };
}

void lexer_tokenize(const char* filename)
{
  char* contents = get_contents(filename);
  
  printf("%s\n", contents);
}
