#ifndef EMULATE_H_
#define EMULATE_H_

#include <stdlib.h>
#include <stdint.h>
#include "registers.h"

void LXI_B(State8080* state, uint8_t addr_src, uint8_t addr_dest);
void LXI_D(State8080* state, uint8_t addr_src, uint8_t addr_dest);
void LXI_H(State8080* state, uint8_t addr_src, uint8_t addr_dest);
void LXI_SP(State8080* state, uint8_t addr_src, uint8_t addr_dest);
void STAX_B(State8080* state, uint8_t memoryB, uint8_t memoryC);
void STAX_D(State8080* state, uint8_t memoryD, uint8_t memoryE);
void INX_B(State8080* state);
void INX_D(State8080* state);
void INX_H(State8080* state);
void INX_SP(State8080* state);
void INR(State8080* state, uint8_t *reg);
void DCR(State8080* state, uint8_t *reg);
void DCX(State8080* state, uint8_t* reg_1, uint8_t* reg_2);
void RLC(State8080* state);
void RAL(State8080* state);
void RAR(State8080* state);
void PUSH(State8080* state, uint8_t reg_data_1, uint8_t reg_data_2);
void PUSH_PSW(State8080* state);
void POP(State8080* state, uint8_t reg_data_1, uint8_t reg_data_2);
void POP_PSW(State8080* state);
void DAD(State8080* state, uint16_t reg_data_1);
void XCHG(State8080* state);
void XTHL(State8080* state);
void ADI(State8080* state, uint8_t reg_data_1);
void ACI(State8080* state, uint8_t reg);
void SBI(State8080* state, uint8_t reg);
void ANI(State8080* state, uint8_t reg);
void XRI(State8080* state, uint8_t reg);

#endif