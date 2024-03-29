#ifndef EMULATE_H_
#define EMULATE_H_

#include <stdlib.h>
#include <stdint.h>
#include "registers.h"

void LXI_B(State8080* state, uint8_t addr_src, uint8_t addr_dest);
void LXI_D(State8080* state, uint8_t addr_src, uint8_t addr_dest);
void LXI_H(State8080* state, uint8_t addr_src, uint8_t addr_dest);
void LXI_SP(State8080* state, uint8_t addr_src, uint8_t addr_dest);
void STAX_B(State8080* state, uint16_t reg, uint8_t src_addr);

#endif