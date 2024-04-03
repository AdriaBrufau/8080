#include <stdio.h>
#include <stdint.h>
#include "registers.h"

static int op_cycle[] = {
    4, 10, 7, 5, 5, 5, 7, 4, 4, 10, 7, 5, 5, 5, 7, 4, //0x00..0x0f
	4, 10, 7, 5, 5, 5, 7, 4, 4, 10, 7, 5, 5, 5, 7, 4, //0x10..0x1f
	4, 10, 16, 5, 5, 5, 7, 4, 4, 10, 16, 5, 5, 5, 7, 4,
	4, 10, 13, 5, 10, 10, 10, 4, 4, 10, 13, 5, 5, 5, 7, 4,

	5, 5, 5, 5, 5, 5, 7, 5, 5, 5, 5, 5, 5, 5, 7, 5, //0x40..0x4f
	5, 5, 5, 5, 5, 5, 7, 5, 5, 5, 5, 5, 5, 5, 7, 5,
	5, 5, 5, 5, 5, 5, 7, 5, 5, 5, 5, 5, 5, 5, 7, 5,
	7, 7, 7, 7, 7, 7, 7, 7, 5, 5, 5, 5, 5, 5, 7, 5,

	4, 4, 4, 4, 4, 4, 7, 4, 4, 4, 4, 4, 4, 4, 7, 4, //0x80..8x4f
	4, 4, 4, 4, 4, 4, 7, 4, 4, 4, 4, 4, 4, 4, 7, 4,
	4, 4, 4, 4, 4, 4, 7, 4, 4, 4, 4, 4, 4, 4, 7, 4,
	4, 4, 4, 4, 4, 4, 7, 4, 4, 4, 4, 4, 4, 4, 7, 4,

	11, 10, 10, 10, 17, 11, 7, 11, 11, 10, 10, 10, 10, 17, 7, 11, //0xc0..0xcf
	11, 10, 10, 10, 17, 11, 7, 11, 11, 10, 10, 10, 10, 17, 7, 11,
	11, 10, 10, 18, 17, 11, 7, 11, 11, 5, 10, 5, 17, 17, 7, 11,
	11, 10, 10, 4, 17, 11, 7, 11, 11, 5, 10, 4, 17, 17, 7, 11,
}

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
void INR(State8080* state, uint8_t *reg){
    uint16_t result = (uint16_t)* reg + 1;
    state->flag.zero = (result == 0);
    state->flag.sign = (0x80 == (result & 0x80));    
    state->flag.parity = __builtin_parity(result);
    *reg = (result & 0x0ff);
}

void DCR(State8080* state, uint8_t *reg){
    uint16_t result = (uint16_t)* reg - 1;
    state->flag.zero = (result == 0);
    state->flag.sign = (0x80 == (result & 0x80));    
    state->flag.parity = __builtin_parity(result);
    *reg = (result & 0x0ff);

}

void RLC(State8080* state){
    state->flag.carry = ((state->reg.A & 0x80) == 0x80);
    state->reg.A = (state->reg.A >> 7) | (state->reg.A <<1);
}

void RAL(State8080* state){
    state->reg.A = (state->reg.A << 1) | state->flag.carry;
}

void DAA(State8080* state){}