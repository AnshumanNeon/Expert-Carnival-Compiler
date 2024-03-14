#include "./scanner.h"
#include "./tokens.h"

void lexer_tokenize(const char* filename)
{
  FILE* file = open_file(filename);
  char word[100];
  
  while(fscanf(file, "%s", word) != EOF)
    {
      printf("%s\n", word);
    }

  fclose(file);
}
