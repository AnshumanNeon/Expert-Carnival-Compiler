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

void string(int current_index, char* source) {
  int index = current_index;
  int line;
  Token token;
  
  while(source[index] != '"' && source[index] != '\0') {
    if(source[index] == '\n') line++;
    index++;
  }

  if(source[index] == '\0') {
    token.type = ERROR_TOKEN;
    return;
  }

  index++;

  strncpy(token.token, source + (current_index - 1), index - 1);
  token.type = STR_TOKEN;
}

// a structure for response type of the get_type_function
struct get_type_response
{
  token_type type;
  int current_index;
} get_type_response;

struct get_type_response get_type(char* source, int current_index) {
  struct get_type_response res;

  res.current_index = current_index;
  
  switch(source[res.current_index]) {
  case '+': res.type = ADDITION_TOKEN; break;
  case '-': res.type = SUB_TOKEN; break;
  case '*': res.type = MUL_TOKEN; break;
  case '/':
    if(source[res.current_index + 1] != '/') {
      res.type = DIV_TOKEN;
      break;
    }
    else {
      current_index += 2;

      while(source[res.current_index] != '\n' && source[res.current_index] != '\0') res.current_index++;
    }
  case '%': res.type = MOD_TOKEN; break;
  case '^': res.type = EXP_TOKEN; break;
  case '(': res.type = LEFT_PAREN_TOKEN; break;
  case ')': res.type = RIGHT_PAREN_TOKEN; break;
  case '[': res.type = LEFT_SQR_PAREN_TOKEN; break;
  case ']': res.type = RIGHT_SQR_PAREN_TOKEN; break;
  case '{': res.type = LEFT_BRACE_TOKEN; break;
  case '}': res.type = RIGHT_BRACE_TOKEN; break;
  case '.': res.type = DOT_TOKEN; break;
  case '<':
    if(source[res.current_index + 1] == '=') {res.type = LESSER_OR_EQUAL_TOKEN; break;}
    else {res.type = LESSER_THAN_TOKEN; break;}
  case '>': 
    if(source[res.current_index + 1] == '='){ res.type = GREATER_OR_EQUAL_TOKEN; break;}
    else {res.type = GREATER_THAN_TOKEN; break;}
  case '=': 
    if(source[res.current_index + 1] == '=') {res.type = EQUAL_EQUAL_TOKEN; break;}
    else {res.type = EQUAL_TOKEN; break;}
  case '!': 
    if(source[res.current_index + 1] == '=') {res.type = NOT_EQUAL_TOKEN; break;}
    else {res.type = NOT_TOKEN; break;}
  case '&': 
    if(source[res.current_index + 1] == '&') {res.type = AND_TOKEN; break;}
    else {res.type = ERROR_TOKEN; break;}
  case '|': 
    if(source[res.current_index + 1] == '|') {res.type = OR_TOKEN; break;}
    if(source[res.current_index + 1] == '=') {res.type = AND_OR_TOKEN; break;}
    else {res.type = ERROR_TOKEN; break;}
  case 'i': 
    if(source[res.current_index + 1] == 'f') {res.type = IF_TOKEN; break;}
  case '"':
    res.current_index++; // because the current index is where string starts. it must end at least 1 pos later.
    string(res.current_index, source);
  default: res.type = ERROR_TOKEN; break;
  };

  return res;
}

void lexer_tokenize(const char* filename)
{
  char* contents = get_contents(filename);
  
  printf("%s\n", contents);
}
