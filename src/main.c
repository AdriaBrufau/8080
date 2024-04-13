#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include "disassembler.h"

int main(int argc, char *argv[]){

  FILE *f = fopen(argv[1], "rb");
  if (f==NULL)
  {
      printf("Could not open file %s\n", argv[1]);
  }

  fseek(f, 0L, SEEK_END);
  int fsize = ftell(f);
  fseek(f, 0L, SEEK_SET);

  unsigned char *buffer = malloc(fsize);
  fread(buffer, fsize, 1, f);
  fclose(f);

  
  int pc = 0;

  while (pc < fsize){
      pc += dissasembler8080(buffer, pc);
  }
  return 0;
}
