#include <stdio.h>
#include <stdint.h>
#include "registers.h"

void LXI_B(State8080* state, uint8_t addr_src, uint8_t addr_dest){
    state->reg.B = addr_src;
    state->reg.C = addr_dest;
    state->programpointer += 2; 
}

void LXI_D(State8080* state, uint8_t addr_src, uint8_t addr_dest){
    state->reg.D = addr_src;
    state->reg.E = addr_dest;
    state->programpointer += 2; 
}

void LXI_H(State8080* state, uint8_t addr_src, uint8_t addr_dest){
    state->reg.H = addr_src;
    state->reg.L = addr_dest;
    state->programpointer += 2; 
}

void LXI_SP(State8080* state, uint8_t addr_src, uint8_t addr_dest){
    state->reg.B = addr_src;
    state->reg.C = addr_dest;
    state->programpointer += 2; 
}