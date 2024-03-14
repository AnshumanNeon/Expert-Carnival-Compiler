#include <stdlib.h>
#include <stdio.h>

/*
  1. Open the file
  2. Read the contents word by word
 */

FILE* open_file(const char* filename)
{
  FILE* file = fopen(filename, "r");

  if(file == NULL)
    {
      printf("error opening the file");
      return 0;
    }

  return file;
}
