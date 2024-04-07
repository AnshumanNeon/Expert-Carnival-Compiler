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

Token string(int current_index, char* source) {
  int index = current_index;
  int line = 1;
  Token token;
  
  while(source[index] != '"' && source[index] != '\0') {
    if(source[index] == '\n') line++;
    index++;
  }

  if(source[index] == '\0') {
    token.type = ERROR_TOKEN;
    return token;
  }

  index++;

  strncpy(token.token, source + (current_index - 1), index - 1);
  token.type = STR_TOKEN;

  return token;
}

int add_current_token(char* source, int current_index_arg, Tokens tokens) {
  int current_index = current_index_arg;
  
  switch(source[current_index]) {
  case '+': add_token(tokens, ADD_TOKEN); break;
  case '-': add_token(tokens, SUB_TOKEN); break;
  case '*': add_token(tokens, MUL_TOKEN); break;
  case '/':
    if(source[current_index + 1] != '/') {
      add_token(tokens, DIV_TOKEN);
      break;
    }
    else {
      current_index += 2;

      while(source[current_index] != '\n' && source[current_index] != '\0') current_index++;
    }
  case '%': add_token(tokens, MOD_TOKEN); break;
  case '^': add_token(tokens, EXP_TOKEN); break;
  case '(': add_token(tokens, LEFT_PAREN_TOKEN); break;
  case ')': add_token(tokens, RIGHT_PAREN_TOKEN); break;
  case '[': add_token(tokens, LEFT_SQR_PAREN_TOKEN); break;
  case ']': add_token(tokens, RIGHT_SQR_PAREN_TOKEN); break;
  case '{': add_token(tokens, LEFT_BRACE_TOKEN); break;
  case '}': add_token(tokens, RIGHT_BRACE_TOKEN); break;
  case '.': add_token(tokens, DOT_TOKEN); break;
  case '<':
    if(source[current_index + 1] == '=') {add_token(tokens, LESSER_OR_EQUAL_TOKEN); break;}
    else {add_token(tokens, LESSER_THAN_TOKEN); break;}
  case '>': 
    if(source[current_index + 1] == '=') {add_token(tokens, GREATER_OR_EQUAL_TOKEN); break;}
    else {add_token(tokens, GREATER_THAN_TOKEN); break;}
  case '=': 
    if(source[current_index + 1] == '=') {add_token(tokens, EQUAL_EQUAL_TOKEN); break;}
    else {add_token(tokens, EQUAL_TOKEN); break;}
  case '!': 
    if(source[current_index + 1] == '=') {add_token(tokens, NOT_EQUAL_TOKEN); break;}
    else {add_token(tokens, NOT_TOKEN); break;}
  case '&': 
    if(source[current_index + 1] == '&') {add_token(tokens, AND_TOKEN); break;}
    else {add_token(tokens, ERROR_TOKEN); break;}
  case '|': 
    if(source[current_index + 1] == '|') {add_token(tokens, OR_TOKEN); break;}
    if(source[current_index + 1] == '=') {add_token(tokens, AND_OR_TOKEN); break;}
    else {add_token(tokens, ERROR_TOKEN); break;}
  case 'i': 
    if(source[current_index + 1] == 'f') {add_token(tokens, IF_TOKEN); break;}
  case '"': {
    // because the current index is where string starts. it must end at least 1 pos later.
    current_index++;
    Token str = string(current_index, source);
    add_token_t(tokens, str);
    break;
  }
  default: add_token(tokens, ERROR_TOKEN); break;
  };

  return current_index;
}

void lexer_tokenize(const char* filename)
{
  char* contents = get_contents(filename);

  // initialize token list
  Tokens token_list = init_token();

  // loop through the token list
  int current_index = 0;
  int prev_index = 0;
  while(contents[current_index] != '\0') {
    prev_index = current_index;
    current_index = add_current_token(contents, current_index, token_list);

    if(prev_index == current_index) {
      current_index++;
    }
  }
  
  printf("Contents:\n%s\n", contents);
  printf("-------------");
  printf("Token list:\n");

  for(unsigned int i = 0; i < token_list.length; i++) {
    printf("\t Token Num: %d\t Token: %s", token_list.tokens[i].type, token_list.tokens[i].token);
  }

  printf("Done!");
}
