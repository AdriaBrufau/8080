#include <stdio.h>
#include <errno.h>
#include <stdlib.h>


int dissasembler8080(unsigned char *buff, int stackpointer){
  unsigned char *code = &buff[stackpointer];
  int opbytes = 1;
  switch(*code)
  {
    case 0x00: printf("NOP\n"); break;
    //case 0x01: printf("LXI    B,#$%02x%02x\n", code[2], code[1]); opbytes=3; break;
    case 0x02: printf("STAX   B, #%x %x\n", code[2], code[1]); opbytes=2; break;
    case 0x03: printf("INX    B\n"); break;
    case 0x04: printf("INR    B\n"); break;
    case 0x05: printf("DCR    B\n"); break;
    case 0x31: printf("LXI    SP,#$%02x %02x\n", code[2], code[1]); opbytes=3; break;
    case 0x34: printf("INR    M, #%x %x\n", code[2], code[1]); opbytes=3; break;
  }
  return 1;
}

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
