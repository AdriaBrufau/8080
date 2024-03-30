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
    state->stackpointer = (addr_src << 8) | addr_dest;
    state->programpointer += 2;
}

void STAX_B(State8080* state, uint8_t memoryB, uint8_t memoryC){
    uint16_t offset = (memoryB<<8) | memoryC;
    state->memory[offset] = state->reg.A;
}

void STAX_D(State8080* state, uint8_t memoryD, uint8_t memoryE){
    uint16_t offset = (memoryD<<8) | memoryE;
    state->memory[offset] = state->reg.A;
}

void INX_B(State8080* state){
    state->reg.B++;
    state->reg.C++;
}
void INX_D(State8080* state){
    state->reg.D++;
    state->reg.E++;
}
void INX_H(State8080* state){
    state->reg.H++;
    state->reg.L++;
}
void INX_SP(State8080* state){
    state->stackpointer++;
}