#ifndef YM2612_H
#define YM2612_H

#include "Arduino.h"
#include <stdint.h>

typedef uint8_t reg_pair[2];

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

void writeYM(uint8_t data);
void set_reg(uint8_t reg, uint8_t data);
void setReg(const reg_pair& reg, uint8_t data);

enum Note { NOTE_C, NOTE_C_SHARP, NOTE_D, NOTE_D_SHARP, NOTE_E, NOTE_F, NOTE_F_SHARP, NOTE_G, NOTE_G_SHARP, NOTE_A, NOTE_A_SHARP, NOTE_B };

// These defines are for 10-bit frequency values which should be split into 2 and 8 bit portions and written to the appropriate registers
#define FREQ_C 617
#define FREQ_C_SHARP 653
#define FREQ_D 692
#define FREQ_D_SHARP 733
#define FREQ_E 777
#define FREQ_F 823
#define FREQ_F_SHARP 872
#define FREQ_G 924
#define FREQ_G_SHARP 979
#define FREQ_A 1037
#define FREQ_A_SHARP 1099
#define FREQ_B 1164



#define MEM_PART_I 0x00
#define MEM_PART_II 0x01

// Register defines. There are a lot of them.

// LFO enable and frequency register.
#define REG_LFO {0x22, MEM_PART_I}
// Timer A MSB and LSB registers.
#define REG_TIMER_A_MSB {0x24, MEM_PART_I}
#define REG_TIMER_A_LSB {0x25, MEM_PART_I}
// Timer B 8-bit register.
#define REG_TIMER_B {0x26, MEM_PART_I}
// Timer enable and channel 3/6 mode register.
#define REG_TIMER_TIMER_CH_3_6_MODE {0x27, MEM_PART_I}
// Key on/off register.
#define REG_KEY_ON_OFF {0x28, MEM_PART_I}
// DAC data and DAC enable registers.
#define REG_DAC_DATA {0x2A, MEM_PART_I}
#define REG_DAC_EN {0x2B, MEM_PART_I}

// DT1 (detune) and MUL (multiple) registers.
#define REG_CH_1_OP_1_DT1_MUL {0x30, MEM_PART_I}
#define REG_CH_2_OP_1_DT1_MUL {0x31, MEM_PART_I}
#define REG_CH_3_OP_1_DT1_MUL {0x32, MEM_PART_I}
#define REG_CH_4_OP_1_DT1_MUL {0x30, MEM_PART_II}
#define REG_CH_5_OP_1_DT1_MUL {0x31, MEM_PART_II}
#define REG_CH_6_OP_1_DT1_MUL {0x32, MEM_PART_II}

#define REG_CH_1_OP_2_DT1_MUL {0x34, MEM_PART_I}
#define REG_CH_2_OP_2_DT1_MUL {0x35, MEM_PART_I}
#define REG_CH_3_OP_2_DT1_MUL {0x36, MEM_PART_I}
#define REG_CH_4_OP_2_DT1_MUL {0x34, MEM_PART_II}
#define REG_CH_5_OP_2_DT1_MUL {0x35, MEM_PART_II}
#define REG_CH_6_OP_2_DT1_MUL {0x36, MEM_PART_II}

#define REG_CH_1_OP_3_DT1_MUL {0x38, MEM_PART_I}
#define REG_CH_2_OP_3_DT1_MUL {0x39, MEM_PART_I}
#define REG_CH_3_OP_3_DT1_MUL {0x3A, MEM_PART_I}
#define REG_CH_4_OP_3_DT1_MUL {0x38, MEM_PART_II}
#define REG_CH_5_OP_3_DT1_MUL {0x39, MEM_PART_II}
#define REG_CH_6_OP_3_DT1_MUL {0x3A, MEM_PART_II}

#define REG_CH_1_OP_4_DT1_MUL {0x3C, MEM_PART_I}
#define REG_CH_2_OP_4_DT1_MUL {0x3D, MEM_PART_I}
#define REG_CH_3_OP_4_DT1_MUL {0x3E, MEM_PART_I}
#define REG_CH_4_OP_4_DT1_MUL {0x3C, MEM_PART_II}
#define REG_CH_5_OP_4_DT1_MUL {0x3D, MEM_PART_II}
#define REG_CH_6_OP_4_DT1_MUL {0x3E, MEM_PART_II}

static reg_pair registers_DT1_MUL[4][6] = {	{REG_CH_1_OP_1_DT1_MUL, REG_CH_2_OP_1_DT1_MUL, REG_CH_3_OP_1_DT1_MUL, REG_CH_4_OP_1_DT1_MUL, REG_CH_5_OP_1_DT1_MUL, REG_CH_6_OP_1_DT1_MUL},
											{REG_CH_1_OP_2_DT1_MUL, REG_CH_2_OP_2_DT1_MUL, REG_CH_3_OP_2_DT1_MUL, REG_CH_4_OP_2_DT1_MUL, REG_CH_5_OP_2_DT1_MUL, REG_CH_6_OP_2_DT1_MUL},
											{REG_CH_1_OP_3_DT1_MUL, REG_CH_2_OP_3_DT1_MUL, REG_CH_3_OP_3_DT1_MUL, REG_CH_4_OP_3_DT1_MUL, REG_CH_5_OP_3_DT1_MUL, REG_CH_6_OP_3_DT1_MUL},
											{REG_CH_1_OP_4_DT1_MUL, REG_CH_2_OP_4_DT1_MUL, REG_CH_3_OP_4_DT1_MUL, REG_CH_4_OP_4_DT1_MUL, REG_CH_5_OP_4_DT1_MUL, REG_CH_6_OP_4_DT1_MUL}};
// TL (total level) registers.
#define REG_CH_1_OP_1_TL {0x40, MEM_PART_I}
#define REG_CH_2_OP_1_TL {0x41, MEM_PART_I}
#define REG_CH_3_OP_1_TL {0x42, MEM_PART_I}
#define REG_CH_4_OP_1_TL {0x40, MEM_PART_II}
#define REG_CH_5_OP_1_TL {0x41, MEM_PART_II}
#define REG_CH_6_OP_1_TL {0x42, MEM_PART_II}

#define REG_CH_1_OP_2_TL {0x44, MEM_PART_I}
#define REG_CH_2_OP_2_TL {0x45, MEM_PART_I}
#define REG_CH_3_OP_2_TL {0x46, MEM_PART_I}
#define REG_CH_4_OP_2_TL {0x44, MEM_PART_II}
#define REG_CH_5_OP_2_TL {0x45, MEM_PART_II}
#define REG_CH_6_OP_2_TL {0x46, MEM_PART_II}

#define REG_CH_1_OP_3_TL {0x48, MEM_PART_I}
#define REG_CH_2_OP_3_TL {0x49, MEM_PART_I}
#define REG_CH_3_OP_3_TL {0x4A, MEM_PART_I}
#define REG_CH_4_OP_3_TL {0x48, MEM_PART_II}
#define REG_CH_5_OP_3_TL {0x49, MEM_PART_II}
#define REG_CH_6_OP_3_TL {0x4A, MEM_PART_II}

#define REG_CH_1_OP_4_TL {0x4C, MEM_PART_I}
#define REG_CH_2_OP_4_TL {0x4D, MEM_PART_I}
#define REG_CH_3_OP_4_TL {0x4E, MEM_PART_I}
#define REG_CH_4_OP_4_TL {0x4C, MEM_PART_II}
#define REG_CH_5_OP_4_TL {0x4D, MEM_PART_II}
#define REG_CH_6_OP_4_TL {0x4E, MEM_PART_II}

static reg_pair registers_TL[4][6] = {		{REG_CH_1_OP_1_TL, REG_CH_2_OP_1_TL, REG_CH_3_OP_1_TL, REG_CH_4_OP_1_TL, REG_CH_5_OP_1_TL, REG_CH_6_OP_1_TL},
											{REG_CH_1_OP_2_TL, REG_CH_2_OP_2_TL, REG_CH_3_OP_2_TL, REG_CH_4_OP_2_TL, REG_CH_5_OP_2_TL, REG_CH_6_OP_2_TL},
											{REG_CH_1_OP_3_TL, REG_CH_2_OP_3_TL, REG_CH_3_OP_3_TL, REG_CH_4_OP_3_TL, REG_CH_5_OP_3_TL, REG_CH_6_OP_3_TL},
											{REG_CH_1_OP_4_TL, REG_CH_2_OP_4_TL, REG_CH_3_OP_4_TL, REG_CH_4_OP_4_TL, REG_CH_5_OP_4_TL, REG_CH_6_OP_4_TL}};
// RS (rate scaling) and AR (attack rate) registers.
#define REG_CH_1_OP_1_RS_AR {0x50, MEM_PART_I}
#define REG_CH_2_OP_1_RS_AR {0x51, MEM_PART_I}
#define REG_CH_3_OP_1_RS_AR {0x52, MEM_PART_I}
#define REG_CH_4_OP_1_RS_AR {0x50, MEM_PART_II}
#define REG_CH_5_OP_1_RS_AR {0x51, MEM_PART_II}
#define REG_CH_6_OP_1_RS_AR {0x52, MEM_PART_II}

#define REG_CH_1_OP_2_RS_AR {0x54, MEM_PART_I}
#define REG_CH_2_OP_2_RS_AR {0x55, MEM_PART_I}
#define REG_CH_3_OP_2_RS_AR {0x56, MEM_PART_I}
#define REG_CH_4_OP_2_RS_AR {0x54, MEM_PART_II}
#define REG_CH_5_OP_2_RS_AR {0x55, MEM_PART_II}
#define REG_CH_6_OP_2_RS_AR {0x56, MEM_PART_II}

#define REG_CH_1_OP_3_RS_AR {0x58, MEM_PART_I}
#define REG_CH_2_OP_3_RS_AR {0x59, MEM_PART_I}
#define REG_CH_3_OP_3_RS_AR {0x5A, MEM_PART_I}
#define REG_CH_4_OP_3_RS_AR {0x58, MEM_PART_II}
#define REG_CH_5_OP_3_RS_AR {0x59, MEM_PART_II}
#define REG_CH_6_OP_3_RS_AR {0x5A, MEM_PART_II}

#define REG_CH_1_OP_4_RS_AR {0x5C, MEM_PART_I}
#define REG_CH_2_OP_4_RS_AR {0x5D, MEM_PART_I}
#define REG_CH_3_OP_4_RS_AR {0x5E, MEM_PART_I}
#define REG_CH_4_OP_4_RS_AR {0x5C, MEM_PART_II}
#define REG_CH_5_OP_4_RS_AR {0x5D, MEM_PART_II}
#define REG_CH_6_OP_4_RS_AR {0x5E, MEM_PART_II}

static reg_pair registers_RS_AR[4][6] = {	{REG_CH_1_OP_1_RS_AR, REG_CH_2_OP_1_RS_AR, REG_CH_3_OP_1_RS_AR, REG_CH_4_OP_1_RS_AR, REG_CH_5_OP_1_RS_AR, REG_CH_6_OP_1_RS_AR},
											{REG_CH_1_OP_2_RS_AR, REG_CH_2_OP_2_RS_AR, REG_CH_3_OP_2_RS_AR, REG_CH_4_OP_2_RS_AR, REG_CH_5_OP_2_RS_AR, REG_CH_6_OP_2_RS_AR},
											{REG_CH_1_OP_3_RS_AR, REG_CH_2_OP_3_RS_AR, REG_CH_3_OP_3_RS_AR, REG_CH_4_OP_3_RS_AR, REG_CH_5_OP_3_RS_AR, REG_CH_6_OP_3_RS_AR},
											{REG_CH_1_OP_4_RS_AR, REG_CH_2_OP_4_RS_AR, REG_CH_3_OP_4_RS_AR, REG_CH_4_OP_4_RS_AR, REG_CH_5_OP_4_RS_AR, REG_CH_6_OP_4_RS_AR}};
// D1R (first decay rate) and AM (amplitude modulation) enable registers.
#define REG_CH_1_OP_1_AM_D1R {0x60, MEM_PART_I}
#define REG_CH_2_OP_1_AM_D1R {0x61, MEM_PART_I}
#define REG_CH_3_OP_1_AM_D1R {0x62, MEM_PART_I}
#define REG_CH_4_OP_1_AM_D1R {0x60, MEM_PART_II}
#define REG_CH_5_OP_1_AM_D1R {0x61, MEM_PART_II}
#define REG_CH_6_OP_1_AM_D1R {0x62, MEM_PART_II}

#define REG_CH_1_OP_2_AM_D1R {0x64, MEM_PART_I}
#define REG_CH_2_OP_2_AM_D1R {0x65, MEM_PART_I}
#define REG_CH_3_OP_2_AM_D1R {0x66, MEM_PART_I}
#define REG_CH_4_OP_2_AM_D1R {0x64, MEM_PART_II}
#define REG_CH_5_OP_2_AM_D1R {0x65, MEM_PART_II}
#define REG_CH_6_OP_2_AM_D1R {0x66, MEM_PART_II}

#define REG_CH_1_OP_3_AM_D1R {0x68, MEM_PART_I}
#define REG_CH_2_OP_3_AM_D1R {0x69, MEM_PART_I}
#define REG_CH_3_OP_3_AM_D1R {0x6A, MEM_PART_I}
#define REG_CH_4_OP_3_AM_D1R {0x68, MEM_PART_II}
#define REG_CH_5_OP_3_AM_D1R {0x69, MEM_PART_II}
#define REG_CH_6_OP_3_AM_D1R {0x6A, MEM_PART_II}

#define REG_CH_1_OP_4_AM_D1R {0x6C, MEM_PART_I}
#define REG_CH_2_OP_4_AM_D1R {0x6D, MEM_PART_I}
#define REG_CH_3_OP_4_AM_D1R {0x6E, MEM_PART_I}
#define REG_CH_4_OP_4_AM_D1R {0x6C, MEM_PART_II}
#define REG_CH_5_OP_4_AM_D1R {0x6D, MEM_PART_II}
#define REG_CH_6_OP_4_AM_D1R {0x6E, MEM_PART_II}

static reg_pair registers_AM_D1R[4][6] = {	{REG_CH_1_OP_1_AM_D1R, REG_CH_2_OP_1_AM_D1R, REG_CH_3_OP_1_AM_D1R, REG_CH_4_OP_1_AM_D1R, REG_CH_5_OP_1_AM_D1R, REG_CH_6_OP_1_AM_D1R},
											{REG_CH_1_OP_2_AM_D1R, REG_CH_2_OP_2_AM_D1R, REG_CH_3_OP_2_AM_D1R, REG_CH_4_OP_2_AM_D1R, REG_CH_5_OP_2_AM_D1R, REG_CH_6_OP_2_AM_D1R},
											{REG_CH_1_OP_3_AM_D1R, REG_CH_2_OP_3_AM_D1R, REG_CH_3_OP_3_AM_D1R, REG_CH_4_OP_3_AM_D1R, REG_CH_5_OP_3_AM_D1R, REG_CH_6_OP_3_AM_D1R},
											{REG_CH_1_OP_4_AM_D1R, REG_CH_2_OP_4_AM_D1R, REG_CH_3_OP_4_AM_D1R, REG_CH_4_OP_4_AM_D1R, REG_CH_5_OP_4_AM_D1R, REG_CH_6_OP_4_AM_D1R}};
// D2R (second decay rate) registers.
#define REG_CH_1_OP_1_D2R {0x70, MEM_PART_I}
#define REG_CH_2_OP_1_D2R {0x71, MEM_PART_I}
#define REG_CH_3_OP_1_D2R {0x72, MEM_PART_I}
#define REG_CH_4_OP_1_D2R {0x70, MEM_PART_II}
#define REG_CH_5_OP_1_D2R {0x71, MEM_PART_II}
#define REG_CH_6_OP_1_D2R {0x72, MEM_PART_II}

#define REG_CH_1_OP_2_D2R {0x74, MEM_PART_I}
#define REG_CH_2_OP_2_D2R {0x75, MEM_PART_I}
#define REG_CH_3_OP_2_D2R {0x76, MEM_PART_I}
#define REG_CH_4_OP_2_D2R {0x74, MEM_PART_II}
#define REG_CH_5_OP_2_D2R {0x75, MEM_PART_II}
#define REG_CH_6_OP_2_D2R {0x76, MEM_PART_II}

#define REG_CH_1_OP_3_D2R {0x78, MEM_PART_I}
#define REG_CH_2_OP_3_D2R {0x79, MEM_PART_I}
#define REG_CH_3_OP_3_D2R {0x7A, MEM_PART_I}
#define REG_CH_4_OP_3_D2R {0x78, MEM_PART_II}
#define REG_CH_5_OP_3_D2R {0x79, MEM_PART_II}
#define REG_CH_6_OP_3_D2R {0x7A, MEM_PART_II}

#define REG_CH_1_OP_4_D2R {0x7C, MEM_PART_I}
#define REG_CH_2_OP_4_D2R {0x7D, MEM_PART_I}
#define REG_CH_3_OP_4_D2R {0x7E, MEM_PART_I}
#define REG_CH_4_OP_4_D2R {0x7C, MEM_PART_II}
#define REG_CH_5_OP_4_D2R {0x7D, MEM_PART_II}
#define REG_CH_6_OP_4_D2R {0x7E, MEM_PART_II}

static reg_pair registers_D2R[4][6] = {	{REG_CH_1_OP_1_D2R, REG_CH_2_OP_1_D2R, REG_CH_3_OP_1_D2R, REG_CH_4_OP_1_D2R, REG_CH_5_OP_1_D2R, REG_CH_6_OP_1_D2R},
										{REG_CH_1_OP_2_D2R, REG_CH_2_OP_2_D2R, REG_CH_3_OP_2_D2R, REG_CH_4_OP_2_D2R, REG_CH_5_OP_2_D2R, REG_CH_6_OP_2_D2R},
										{REG_CH_1_OP_3_D2R, REG_CH_2_OP_3_D2R, REG_CH_3_OP_3_D2R, REG_CH_4_OP_3_D2R, REG_CH_5_OP_3_D2R, REG_CH_6_OP_3_D2R},
										{REG_CH_1_OP_4_D2R, REG_CH_2_OP_4_D2R, REG_CH_3_OP_4_D2R, REG_CH_4_OP_4_D2R, REG_CH_5_OP_4_D2R, REG_CH_6_OP_4_D2R}};
// D1L (secondary amplitude) and RR (release rate) registers
#define REG_CH_1_OP_1_D1L_RR {0x80, MEM_PART_I}
#define REG_CH_2_OP_1_D1L_RR {0x81, MEM_PART_I}
#define REG_CH_3_OP_1_D1L_RR {0x82, MEM_PART_I}
#define REG_CH_4_OP_1_D1L_RR {0x80, MEM_PART_II}
#define REG_CH_5_OP_1_D1L_RR {0x81, MEM_PART_II}
#define REG_CH_6_OP_1_D1L_RR {0x82, MEM_PART_II}

#define REG_CH_1_OP_2_D1L_RR {0x84, MEM_PART_I}
#define REG_CH_2_OP_2_D1L_RR {0x85, MEM_PART_I}
#define REG_CH_3_OP_2_D1L_RR {0x86, MEM_PART_I}
#define REG_CH_4_OP_2_D1L_RR {0x84, MEM_PART_II}
#define REG_CH_5_OP_2_D1L_RR {0x85, MEM_PART_II}
#define REG_CH_6_OP_2_D1L_RR {0x86, MEM_PART_II}

#define REG_CH_1_OP_3_D1L_RR {0x88, MEM_PART_I}
#define REG_CH_2_OP_3_D1L_RR {0x89, MEM_PART_I}
#define REG_CH_3_OP_3_D1L_RR {0x8A, MEM_PART_I}
#define REG_CH_4_OP_3_D1L_RR {0x88, MEM_PART_II}
#define REG_CH_5_OP_3_D1L_RR {0x89, MEM_PART_II}
#define REG_CH_6_OP_3_D1L_RR {0x8A, MEM_PART_II}

#define REG_CH_1_OP_4_D1L_RR {0x8C, MEM_PART_I}
#define REG_CH_2_OP_4_D1L_RR {0x8D, MEM_PART_I}
#define REG_CH_3_OP_4_D1L_RR {0x8E, MEM_PART_I}
#define REG_CH_4_OP_4_D1L_RR {0x8C, MEM_PART_II}
#define REG_CH_5_OP_4_D1L_RR {0x8D, MEM_PART_II}
#define REG_CH_6_OP_4_D1L_RR {0x8E, MEM_PART_II}

static reg_pair registers_D1L_RR[4][6] = {	{REG_CH_1_OP_1_D1L_RR, REG_CH_2_OP_1_D1L_RR, REG_CH_3_OP_1_D1L_RR, REG_CH_4_OP_1_D1L_RR, REG_CH_5_OP_1_D1L_RR, REG_CH_6_OP_1_D1L_RR},
											{REG_CH_1_OP_2_D1L_RR, REG_CH_2_OP_2_D1L_RR, REG_CH_3_OP_2_D1L_RR, REG_CH_4_OP_2_D1L_RR, REG_CH_5_OP_2_D1L_RR, REG_CH_6_OP_2_D1L_RR},
											{REG_CH_1_OP_3_D1L_RR, REG_CH_2_OP_3_D1L_RR, REG_CH_3_OP_3_D1L_RR, REG_CH_4_OP_3_D1L_RR, REG_CH_5_OP_3_D1L_RR, REG_CH_6_OP_3_D1L_RR},
											{REG_CH_1_OP_4_D1L_RR, REG_CH_2_OP_4_D1L_RR, REG_CH_3_OP_4_D1L_RR, REG_CH_4_OP_4_D1L_RR, REG_CH_5_OP_4_D1L_RR, REG_CH_6_OP_4_D1L_RR}};
// SSG-EG (proprietary) registers.
#define REG_CH_1_OP_1_SSG_EG {0x90, MEM_PART_I}
#define REG_CH_2_OP_1_SSG_EG {0x91, MEM_PART_I}
#define REG_CH_3_OP_1_SSG_EG {0x92, MEM_PART_I}
#define REG_CH_4_OP_1_SSG_EG {0x90, MEM_PART_II}
#define REG_CH_5_OP_1_SSG_EG {0x91, MEM_PART_II}
#define REG_CH_6_OP_1_SSG_EG {0x92, MEM_PART_II}

#define REG_CH_1_OP_2_SSG_EG {0x94, MEM_PART_I}
#define REG_CH_2_OP_2_SSG_EG {0x95, MEM_PART_I}
#define REG_CH_3_OP_2_SSG_EG {0x96, MEM_PART_I}
#define REG_CH_4_OP_2_SSG_EG {0x94, MEM_PART_II}
#define REG_CH_5_OP_2_SSG_EG {0x95, MEM_PART_II}
#define REG_CH_6_OP_2_SSG_EG {0x96, MEM_PART_II}

#define REG_CH_1_OP_3_SSG_EG {0x98, MEM_PART_I}
#define REG_CH_2_OP_3_SSG_EG {0x99, MEM_PART_I}
#define REG_CH_3_OP_3_SSG_EG {0x9A, MEM_PART_I}
#define REG_CH_4_OP_3_SSG_EG {0x98, MEM_PART_II}
#define REG_CH_5_OP_3_SSG_EG {0x99, MEM_PART_II}
#define REG_CH_6_OP_3_SSG_EG {0x9A, MEM_PART_II}

#define REG_CH_1_OP_4_SSG_EG {0x9C, MEM_PART_I}
#define REG_CH_2_OP_4_SSG_EG {0x9D, MEM_PART_I}
#define REG_CH_3_OP_4_SSG_EG {0x9E, MEM_PART_I}
#define REG_CH_4_OP_4_SSG_EG {0x9C, MEM_PART_II}
#define REG_CH_5_OP_4_SSG_EG {0x9D, MEM_PART_II}
#define REG_CH_6_OP_4_SSG_EG {0x9E, MEM_PART_II}

static reg_pair registers_SSG_EG[4][6] = {	{REG_CH_1_OP_1_SSG_EG, REG_CH_2_OP_1_SSG_EG, REG_CH_3_OP_1_SSG_EG, REG_CH_4_OP_1_SSG_EG, REG_CH_5_OP_1_SSG_EG, REG_CH_6_OP_1_SSG_EG},
											{REG_CH_1_OP_2_SSG_EG, REG_CH_2_OP_2_SSG_EG, REG_CH_3_OP_2_SSG_EG, REG_CH_4_OP_2_SSG_EG, REG_CH_5_OP_2_SSG_EG, REG_CH_6_OP_2_SSG_EG},
											{REG_CH_1_OP_3_SSG_EG, REG_CH_2_OP_3_SSG_EG, REG_CH_3_OP_3_SSG_EG, REG_CH_4_OP_3_SSG_EG, REG_CH_5_OP_3_SSG_EG, REG_CH_6_OP_3_SSG_EG},
											{REG_CH_1_OP_4_SSG_EG, REG_CH_2_OP_4_SSG_EG, REG_CH_3_OP_4_SSG_EG, REG_CH_4_OP_4_SSG_EG, REG_CH_5_OP_4_SSG_EG, REG_CH_6_OP_4_SSG_EG}};
// Frequency LSB registers.
#define REG_CH_1_FREQ_LO {0xA0, MEM_PART_I}
#define REG_CH_2_FREQ_LO {0xA1, MEM_PART_I}
#define REG_CH_3_FREQ_LO {0xA2, MEM_PART_I}
#define REG_CH_4_FREQ_LO {0xA0, MEM_PART_II}
#define REG_CH_5_FREQ_LO {0xA1, MEM_PART_II}
#define REG_CH_6_FREQ_LO {0xA2, MEM_PART_II}

static reg_pair registers_FREQ_LO[6] = { REG_CH_1_FREQ_LO, REG_CH_2_FREQ_LO, REG_CH_3_FREQ_LO, REG_CH_4_FREQ_LO, REG_CH_5_FREQ_LO, REG_CH_6_FREQ_LO};
// Frequency MSB and block registers.
#define REG_CH_1_FREQ_HI {0xA4, MEM_PART_I}
#define REG_CH_2_FREQ_HI {0xA5, MEM_PART_I}
#define REG_CH_3_FREQ_HI {0xA6, MEM_PART_I}
#define REG_CH_4_FREQ_HI {0xA4, MEM_PART_II}
#define REG_CH_5_FREQ_HI {0xA5, MEM_PART_II}
#define REG_CH_6_FREQ_HI {0xA6, MEM_PART_II}

static reg_pair registers_FREQ_HI[6] = { REG_CH_1_FREQ_HI, REG_CH_2_FREQ_HI, REG_CH_3_FREQ_HI, REG_CH_4_FREQ_HI, REG_CH_5_FREQ_HI, REG_CH_6_FREQ_HI};
// Channel 3 / 6 supplementary frequency LSB registers.
#define REG_CH_3_OP_2_SUPPL_FREQ_LO {0xA8, MEM_PART_I}
#define REG_CH_3_OP_3_SUPPL_FREQ_LO {0xA9, MEM_PART_I}
#define REG_CH_3_OP_4_SUPPL_FREQ_LO {0xAA, MEM_PART_I}
#define REG_CH_6_OP_2_SUPPL_FREQ_LO {0xA8, MEM_PART_II}
#define REG_CH_6_OP_3_SUPPL_FREQ_LO {0xA9, MEM_PART_II}
#define REG_CH_6_OP_4_SUPPL_FREQ_LO {0xAA, MEM_PART_II}

// Channel 3 / 6 supplementary frequency MSB and block registers.
#define REG_CH_3_OP_2_SUPPL_FREQ_HI {0xAC, MEM_PART_I}
#define REG_CH_3_OP_3_SUPPL_FREQ_HI {0xAD, MEM_PART_I}
#define REG_CH_3_OP_4_SUPPL_FREQ_HI {0xAE, MEM_PART_I}
#define REG_CH_6_OP_2_SUPPL_FREQ_HI {0xAC, MEM_PART_II}
#define REG_CH_6_OP_3_SUPPL_FREQ_HI {0xAD, MEM_PART_II}
#define REG_CH_6_OP_4_SUPPL_FREQ_HI {0xAE, MEM_PART_II}

// Feedback and algorithm registers.
#define REG_CH_1_FDBCK_ALG {0xB0, MEM_PART_I}
#define REG_CH_2_FDBCK_ALG {0xB1, MEM_PART_I}
#define REG_CH_3_FDBCK_ALG {0xB2, MEM_PART_I}
#define REG_CH_4_FDBCK_ALG {0xB0, MEM_PART_II}
#define REG_CH_5_FDBCK_ALG {0xB1, MEM_PART_II}
#define REG_CH_6_FDBCK_ALG {0xB2, MEM_PART_II}

static reg_pair registers_FDBCK_ALG[6] = { REG_CH_1_FDBCK_ALG, REG_CH_2_FDBCK_ALG, REG_CH_3_FDBCK_ALG, REG_CH_4_FDBCK_ALG, REG_CH_5_FDBCK_ALG, REG_CH_6_FDBCK_ALG};
// Stereo and LFO sensitivity (AMS and FMS) control registers.
#define REG_CH_1_STEREO_LFO {0xB4, MEM_PART_I}
#define REG_CH_2_STEREO_LFO {0xB5, MEM_PART_I}
#define REG_CH_3_STEREO_LFO {0xB6, MEM_PART_I}
#define REG_CH_4_STEREO_LFO {0xB4, MEM_PART_II}
#define REG_CH_5_STEREO_LFO {0xB5, MEM_PART_II}
#define REG_CH_6_STEREO_LFO {0xB6, MEM_PART_II}

static reg_pair registers_STEREO_LFO[6] = { REG_CH_1_FDBCK_ALG, REG_CH_2_FDBCK_ALG, REG_CH_3_FDBCK_ALG, REG_CH_4_FDBCK_ALG, REG_CH_5_FDBCK_ALG, REG_CH_6_FDBCK_ALG};
#endif /* YM2612_H */
