#ifndef REGISTERS_H
#define REGISTERS_H

#include <stdint.h>

typedef struct{
  
    uint8_t  A;
    uint8_t  B;
    uint8_t  C;
    uint8_t  D;
    uint8_t  E;
    uint8_t  H;
    uint8_t  L;

} Registers;

typedef struct{
    // bitmap looks something like this SSS or DDD equals to a binary number 111 means is A and so on....    
} bitmap
#endif

