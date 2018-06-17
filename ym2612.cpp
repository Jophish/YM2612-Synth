#include "ym2612.h"

// Writes a byte to the YM2612 
void writeYM(uint8_t data) {
  YM_CTRL_PORT &= ~_BV(YM_CS); // CS LOW
  YM_DATA_PORT = data;
  delayMicroseconds(1);
  YM_CTRL_PORT &= ~_BV(YM_WR); // Write data
  delayMicroseconds(5);
  YM_CTRL_PORT |= _BV(YM_WR);
  delayMicroseconds(5);
  YM_CTRL_PORT |= _BV(YM_CS); // CS HIGH
}

// Writes a byte to the appropriate register in the YM2612
void set_reg(uint8_t reg, uint8_t data) {
  YM_CTRL_PORT &= ~_BV(YM_A0); // A0 low (select register)
  writeYM(reg);
  YM_CTRL_PORT |= _BV(YM_A0);  // A0 high (write register)
  writeYM(data);
}

// Writes a byte to the appropriate register in the YM2612
void setReg(const reg_pair& reg, uint8_t data) {
  uint8_t addr = reg[0];
  switch (reg[1]) {
    case (MEM_PART_I):
      YM_CTRL_PORT &= ~_BV(YM_A0); // A0 low 
      YM_CTRL_PORT &= ~_BV(YM_A1); // A1 low (select part I register)
      writeYM(addr);
      YM_CTRL_PORT |= _BV(YM_A0);  // A0 high (write part I register)
      writeYM(data);    
    break;
    case (MEM_PART_II):
      YM_CTRL_PORT &= ~_BV(YM_A0); // A0 low 
      YM_CTRL_PORT |= _BV(YM_A1);  // A1 high (select part II register)
      writeYM(addr);
      YM_CTRL_PORT |= _BV(YM_A0);  // A0 high (write part II register)
      writeYM(data);
      break;
    default:
      break;
  }
  return;
}
