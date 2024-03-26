#include <stdlib.h>
#include <stdio.h>



// int dissasembler8080(unsigned char *buff, int stackpointer){
//   unsigned char *code = &buff[stackpointer];
//   int opbytes = 1;
//   switch(*code)
//   {
//     case 0x00: printf("NOP\n"); break;
//     case 0x01: printf("LXI    B,#$%02x%02x\n", code[2], code[1]); opbytes=3; break;
//     case 0x02: printf("STAX   B"); break;
//     case 0x03: printf("INX    B"); break;
//     case 0x04: printf("INR    B"); break;
//     case 0x05: printf("DCR    B"); break;
//     case 0x31: printf("LXI    SP,#$%02x%02x\n", code[2], code[1]); opbytes=3; break;
//   }
//   return 1;
// }