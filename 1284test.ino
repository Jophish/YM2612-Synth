#include <stdint.h>

#define YM_IC (0) // PB0 (Pin 0 on Atmega1284P)
#define YM_CS (1) // PB1 (Pin 1 on Atmega1284P)
#define YM_WR (2) // PB2 (Pin 2 on Atmega1284P)
#define YM_RD (3) // PB3 (Pin 3 on Atmega1284P)
#define YM_A0 (4) // PB4 (Pin 4 on Atmega1284P)
#define YM_A1 (5) // PB5 (Pin 5 on Atmega1284P)

#define YM_CTRL_DDR DDRB
#define YM_CTRL_PORT PORTB

#define YM_DATA_DDR DDRA
#define YM_DATA_PORT PORTA

static void write_ym(uint8_t data) {
  YM_CTRL_PORT &= ~_BV(YM_CS); // CS LOW
  YM_DATA_PORT = data;
  delayMicroseconds(1);
  YM_CTRL_PORT &= ~_BV(YM_WR); // Write data
  delayMicroseconds(5);
  YM_CTRL_PORT |= _BV(YM_WR);
  delayMicroseconds(5);
  YM_CTRL_PORT |= _BV(YM_CS); // CS HIGH
}

static void setreg(uint8_t reg, uint8_t data) {
  YM_CTRL_PORT &= ~_BV(YM_A0); // A0 low (select register)
  write_ym(reg);
  YM_CTRL_PORT |= _BV(YM_A0);  // A0 high (write register)
  write_ym(data);
}

void setup() {
  YM_CTRL_DDR |= _BV(YM_IC) | _BV(YM_CS) | _BV(YM_WR) | _BV(YM_RD) | _BV(YM_A0) | _BV(YM_A1);
  YM_DATA_DDR = 0xFF;

  YM_CTRL_PORT |= _BV(YM_IC) | _BV(YM_CS) | _BV(YM_WR) | _BV(YM_RD); /* IC, CS, WR and RD HIGH by default */
  YM_CTRL_PORT &= ~(_BV(YM_A0) | _BV(YM_A1)); /* A0 and A1 LOW by default */
}

void loop() {
  YM_CTRL_PORT &= ~_BV(YM_IC);
  delay(10);
  YM_CTRL_PORT |= _BV(YM_IC);
  delay(10);

  /* YM2612 Test code */ 
  setreg(0x22, 0x00); // LFO off
  setreg(0x27, 0x00); // Note off (channel 0)
  setreg(0x28, 0x01); // Note off (channel 1)
  setreg(0x28, 0x02); // Note off (channel 2)
  setreg(0x28, 0x04); // Note off (channel 3)
  setreg(0x28, 0x05); // Note off (channel 4)
  setreg(0x28, 0x06); // Note off (channel 5)
  setreg(0x2B, 0x00); // DAC off
  setreg(0x30, 0x71); //
  setreg(0x34, 0x0D); //
  setreg(0x38, 0x33); //
  setreg(0x3C, 0x01); // DT1/MUL
  setreg(0x40, 0x23); //
  setreg(0x44, 0x2D); //
  setreg(0x48, 0x26); //
  setreg(0x4C, 0x00); // Total level
  setreg(0x50, 0x5F); //
  setreg(0x54, 0x99); //
  setreg(0x58, 0x5F); //
  setreg(0x5C, 0x94); // RS/AR 
  setreg(0x60, 0x05); //
  setreg(0x64, 0x05); //
  setreg(0x68, 0x05); //
  setreg(0x6C, 0x07); // AM/D1R
  setreg(0x70, 0x02); //
  setreg(0x74, 0x02); //
  setreg(0x78, 0x02); //
  setreg(0x7C, 0x02); // D2R
  setreg(0x80, 0x11); //
  setreg(0x84, 0x11); //
  setreg(0x88, 0x11); //
  setreg(0x8C, 0xA6); // D1L/RR
  setreg(0x90, 0x00); //
  setreg(0x94, 0x00); //
  setreg(0x98, 0x00); //
  setreg(0x9C, 0x00); // Proprietary
  setreg(0xB0, 0x32); // Feedback/algorithm
  setreg(0xB4, 0xC0); // Both speakers on
  setreg(0x28, 0x00); // Key off
  setreg(0xA4, 0x22); // 
  setreg(0xA0, 0x69); // Set frequency

  /* Program loop */
  int count = 0x0;
  for(;;) {
    delay(100);
    setreg(0x28, 0xF0); // Key on
    delay(100);
    setreg(0x28, 0x00); // Key off
    setreg(0xA4, count); // 
    setreg(0xA0, 0x69); // Set frequency
    count = ((count + 1) % 0xFF) & 0x7;
  }

}


