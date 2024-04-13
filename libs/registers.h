#ifndef REGISTERS_H
#define REGISTERS_H

#include <stdint.h>

typedef struct Registers{
  
    uint8_t  A;
    uint8_t  B;
    uint8_t  C;
    uint8_t  D;
    uint8_t  E;
    uint8_t  H;
    uint8_t  L;

} Registers;

typedef struct Flags{
    uint8_t sign:1;
    uint8_t zero:1;
    uint8_t parity:1;
    uint8_t carry:1;
    uint8_t auxiliary_carry:3;
} Flags;

typedef struct State8080{
    Registers reg;
    Flags flag;
    uint8_t stackpointer;
    uint8_t programpointer;
    uint8_t *memory;
} State8080;


void emulate8080(State8080* state, int pc);
#endif

