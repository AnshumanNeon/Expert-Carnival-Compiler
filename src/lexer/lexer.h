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

token_type get_type(char token) {
  switch(token) {
  case '+': return ADDITION_TOKEN; break;
  default: return ERROR_TOKEN; break;
  };
}

void lexer_tokenize(const char* filename)
{
  char* contents = get_contents(filename);
  
  printf("%s\n", contents);
}
