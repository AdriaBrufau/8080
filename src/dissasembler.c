#include <stdlib.h>
#include <stdio.h>


int dissasembler8080(unsigned char *buff, int stackpointer){
  unsigned char *code = &buff[stackpointer];
  int opbytes = 1;
  printf("%04x ", stackpointer);
  switch(*code)
  {
    case 0x00: printf("NOP\n"); break;
  }
  return 1;
}
