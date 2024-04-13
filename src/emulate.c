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
};

void LXI_B(State8080* state, uint8_t addr_src, uint8_t addr_dest){
    state->reg.B = addr_src;
    state->reg.C = addr_dest;
}

void LXI_D(State8080* state, uint8_t addr_src, uint8_t addr_dest){
    state->reg.D = addr_src;
    state->reg.E = addr_dest;
}

void LXI_H(State8080* state, uint8_t addr_src, uint8_t addr_dest){
    state->reg.H = addr_src;
    state->reg.L = addr_dest;
}

void LXI_SP(State8080* state, uint8_t addr_src, uint8_t addr_dest){
    state->stackpointer = (addr_src << 8) | addr_dest;
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

void DCX(State8080* state, uint8_t* reg_1, uint8_t* reg_2){
    *reg_1 -= 1;
    *reg_2 -= 1;
}

void RLC(State8080* state){
    state->flag.carry = ((state->reg.A & 0x80) == 0x80);
    state->reg.A = (state->reg.A >> 7) | (state->reg.A <<1);
}

void RAL(State8080* state){
    state->flag.carry = ((state->reg.A & 0x80) == 0x80);
    state->reg.A = (state->reg.A << 1) | state->flag.carry;
}

void RAR(State8080* state){
    state->flag.carry = ((state->reg.A & 0x80) == 0x80);
    state->reg.A = (state->reg.A >> 1) | state->flag.carry;
}

void PUSH(State8080* state, uint8_t reg_data_1, uint8_t reg_data_2){
    state->memory[state->stackpointer -2 ] = reg_data_2;
    state->memory[state->stackpointer -1 ] = reg_data_1;
    state->programpointer -= 2;
}

void PUSH_PSW(State8080* state){
    uint8_t psw = (state->flag.sign            << 7)  |
                  (state->flag.zero            << 6)  |
                  (state->flag.auxiliary_carry << 4)  |
                  (state->flag.parity          << 2)  |
                   state->flag.carry                  ;
    state->stackpointer -= 2;
    state->memory[state->stackpointer] = state->reg.A;
    state->memory[state->stackpointer++] = psw;
}

void POP(State8080* state, uint8_t reg_data_1, uint8_t reg_data_2){
    state->memory[state->stackpointer + 2 ] = reg_data_2;
    state->memory[state->stackpointer + 1 ] = reg_data_1;
}

void POP_PSW(State8080* state){
    uint8_t psw = (state->flag.sign            << 7)  |
                  (state->flag.zero            << 6)  |
                  (state->flag.auxiliary_carry << 4)  |
                  (state->flag.parity          << 2)  |
                   state->flag.carry                  ;
    state->stackpointer += 2;
    state->memory[state->stackpointer] = state->reg.A;
    state->memory[state->stackpointer -1] = psw;
}

void DAD(State8080* state, uint16_t reg_data_1){
    uint16_t reg_val = (uint16_t)((state->reg.H<<7) | state->reg.L);
    uint16_t total = reg_data_1 + reg_val;
    state->reg.H = (total >> 8) & 0xff;
    state->reg.L = total & 0xff;
    state->flag.carry = ((total & 0x80) == 0x80);
}

void XCHG(State8080* state){
    state->reg.H = state->reg.D;
    state->reg.L = state->reg.E;
}

void XTHL(State8080* state){
    state->reg.L = state->memory[state->stackpointer];
    state->reg.H = state->memory[state->stackpointer++];
}

void ADI(State8080* state, uint8_t reg_1){
    uint16_t result = (uint16_t)(state->reg.A + reg_1);
    state->flag.zero = (uint8_t)result == 0;
    state->flag.sign = (uint8_t)(result & 0x80);    
    state->flag.parity = __builtin_parity((uint8_t)result);
    state->flag.carry = result >> 0xff;
    state->reg.A = (uint8_t)result;
}
void ACI(State8080* state, uint8_t reg){
    uint16_t result = (uint16_t)(state->reg.A + reg + state->flag.carry);
    state->flag.zero = (uint8_t)result == 0;
    state->flag.sign = (uint8_t)(result & 0x80);    
    state->flag.pCarity = __builtin_parity((uint8_t)result);
    state->flag.carry = result >> 0xff;
    state->reg.A = (uint8_t)result;
}

void SBI(State8080* state, uint8_t reg_1){
    uint16_t result = (uint16_t)(state->reg.A - reg_1);
    state->flag.zero = (uint8_t)result == 0;
    state->flag.sign = (uint8_t)(result & 0x80);    
    state->flag.parity = __builtin_parity((uint8_t)result);
    state->flag.carry = result >> 0xff;
    state->reg.A = (uint8_t)result;
}

void ANI(State8080* state, uint8_t reg){
    uint16_t result = (uint16_t)(state->reg.A & reg);
    state->flag.zero = (uint8_t)result == 0;
    state->flag.sign = (uint8_t)(result & 0x80);    
    state->flag.parity = __builtin_parity((uint8_t)result);
    state->flag.carry = result >> 0xff;
    state->reg.A = (uint8_t)result;
}

void XRA(State8080* state, uint8_t reg){
    uint16_t result = (uint16_t)(reg ^ state->reg.A);
    state->flag.zero = (uint8_t)result == 0;
    state->flag.sign = (uint8_t)(result & 0x80);    
    state->flag.parity = __builtin_parity((uint8_t)result);
    state->flag.carry = result >> 0xff;
    state->reg.A = (uint8_t)result;
}


void ORI(State8080* state, uint8_t reg){
    uint16_t result = (uint16_t)(reg | state->reg.A);
    state->flag.zero = (uint8_t)result == 0;
    state->flag.sign = (uint8_t)(result & 0x80);    
    state->flag.parity = __builtin_parity((uint8_t)result);
    state->flag.carry = result >> 0xff;
    state->reg.A = (uint8_t)result;
}

void CPI(State8080* state, uint8_t reg){
    uint16_t result = (uint16_t)(state->reg.A - reg);
    state->flag.zero = (uint8_t)result == 0;
    state->flag.sign = (uint8_t)(result & 0x80);    
    state->flag.parity = __builtin_parity((uint8_t)result);
    state->flag.carry = result >> 0xff;
}

void STA(State8080* state, uint8_t pos, uint8_t reg){
    uint16_t position = (pos << 8) | reg;
    state->memory[position] = state->reg.A;
}

void LDA(State8080* state, uint8_t pos, uint8_t reg){
    uint16_t position = (pos << 8) | reg;
    state->reg.A = state->memory[position]; 
}

void SHLD(State8080* state, uint8_t low, uint8_t high){
    uint16_t position = (low << 8) | high;
    state->memory[position] =state->reg.L;
    state->memory(position++] = state->reg.H ;
}

void LHLD(State8080* state, uint8_t low, uint8_t high){
    uint16_t position = (low << 8 ) | high;
    state->reg.L = state->memory[position] ;
    state->reg.H = state->memory(position++]  ;
}