#include "synth.h"

 Synth::Synth() : midiData() {
 	// Set default parameters for the YM2612 pins
 	YM_CTRL_DDR |= _BV(YM_IC) | _BV(YM_CS) | _BV(YM_WR) | _BV(YM_RD) | _BV(YM_A0) | _BV(YM_A1);
 	YM_DATA_DDR = 0xFF;
  	YM_CTRL_PORT |= _BV(YM_IC) | _BV(YM_CS) | _BV(YM_WR) | _BV(YM_RD); /* IC, CS, WR and RD HIGH by default */
  	YM_CTRL_PORT &= ~(_BV(YM_A0) | _BV(YM_A1)); /* A0 and A1 LOW by default */

 	// Reset the YM2612
  	YM_CTRL_PORT &= ~_BV(YM_IC);
  	delay(10);
  	YM_CTRL_PORT |= _BV(YM_IC);
 	delay(10);

 	// Set up the class
 	for (int i = 0; i < MAX_NOTES_ON; i++) {
 		notesOn[i] = 0;
 	}

 	midiChannel = MIDI_CHANNEL;

 	lfoFreq = 0;
 	lfoEnable = false;

 	Serial1.begin(MIDI_BAUD);

 	/* YM2612 Test code */ 
  set_reg(0x22, 0x00); // LFO off
  	// disableLFO();
  set_reg(0x27, 0x00); // Note off (channel 0)
  	// setKeyOff(0);
  set_reg(0x28, 0x01); // Note off (channel 1)
	// setKeyOff(1);
  set_reg(0x28, 0x02); // Note off (channel 2)
  	// setKeyOff(2);
  set_reg(0x28, 0x04); // Note off (channel 3)
  	// setKeyOff(3);
  set_reg(0x28, 0x05); // Note off (channel 4)
  	// setKeyOff(4);
  set_reg(0x28, 0x06); // Note off (channel 5)
  	// setKeyOff(5);
  set_reg(0x2B, 0x00); // DAC off
  	// disableDAC();
  set_reg(0x30, 0x71); //
  	// setDetuneAll(0x7, 0);
  	// setMultipleAll(0x1, 0);
  set_reg(0x34, 0x0D); //
  	// setDetuneAll(0x0, 1);
  	// setMultipleAll(0xD, 1);
  set_reg(0x38, 0x33); //
    // setDetuneAll(0x3, 2);
  	// setMultipleAll(0x3, 2);
  set_reg(0x3C, 0x01); // DT1/MUL
    // setDetuneAll(0x0, 3);
  	// setMultipleAll(0x1, 3);
  set_reg(0x40, 0x23); //
  set_reg(0x44, 0x2D); //
  set_reg(0x48, 0x26); //
  set_reg(0x4C, 0x00); // Total level
  set_reg(0x50, 0x5F); //
  set_reg(0x54, 0x99); //
  set_reg(0x58, 0x5F); //
  set_reg(0x5C, 0x94); // RS/AR 
  set_reg(0x60, 0x05); //
  set_reg(0x64, 0x05); //
  set_reg(0x68, 0x05); //
  set_reg(0x6C, 0x07); // AM/D1R
  set_reg(0x70, 0x02); //
  set_reg(0x74, 0x02); //
  set_reg(0x78, 0x02); //
  set_reg(0x7C, 0x02); // D2R
  set_reg(0x80, 0x11); //
  set_reg(0x84, 0x11); //
  set_reg(0x88, 0x11); //
  set_reg(0x8C, 0xA6); // D1L/RR
  set_reg(0x90, 0x00); //
  set_reg(0x94, 0x00); //
  set_reg(0x98, 0x00); //
  set_reg(0x9C, 0x00); // Proprietary
  set_reg(0xB0, 0x32); // Feedback/algorithm
  set_reg(0xB4, 0xC0); // Both speakers on
  set_reg(0x28, 0x00); // Key off
  set_reg(0xA4, 0x22); // 
  set_reg(0xA0, 0x69); // Set frequency
 }

int Synth::turnMidiNoteOn(uint8_t note, uint8_t vel) {
	note -= 11;
	uint8_t octave = midiData.midiToOctave(note);
	uint16_t frequency = noteToFreqVal(midiData.midiToNote(note));
	uint8_t hi_reg = (octave << 3) | (uint8_t)(frequency >> 8);
	uint8_t low_reg = (uint8_t)frequency;
	set_reg(0x28, 0x00); // Key off
	set_reg(0xA4, hi_reg); // 
  	set_reg(0xA0, low_reg); // Set frequency
  	set_reg(0x28, 0xF0); // Key on

}

uint16_t Synth::noteToFreqVal(Note note) {
	switch (note) {
		case (NOTE_C) :
			return FREQ_C;
		case (NOTE_C_SHARP):
			return FREQ_C_SHARP;
		case (NOTE_D):
			return FREQ_D;
		case (NOTE_D_SHARP):
			return FREQ_D_SHARP;
		case (NOTE_E):
			return FREQ_E;
		case (NOTE_F):
			return FREQ_F;
		case (NOTE_F_SHARP):
			return FREQ_F_SHARP;
		case (NOTE_G):
			return FREQ_G;
		case (NOTE_G_SHARP):
			return FREQ_G_SHARP;
		case (NOTE_A):
			return FREQ_A;
		case (NOTE_A_SHARP):
			return FREQ_A_SHARP;
		case (NOTE_B):
			return FREQ_B;
	}
	return 0;
}

bool Synth::checkChannel(uint8_t midiByte) {
	return (midiByte & 0x0f) == midiChannel;
}

int Synth::processMidi() {
	if (!midiData.msgIsReady())
		return -1;
	//char buffer[100];
	//sprintf(buffer, "Got MIDI message: 0x%02x 0x%02x 0x%02x\n", midiData.getByte(0), midiData.getByte(1), midiData.getByte(2));
	//Serial.print(buffer);
	uint8_t commandByte = midiData.getByte(0);
	switch (commandByte >> 4) {
		case (MIDI_NOTE_ON):
			if (checkChannel(commandByte))
				turnMidiNoteOn(midiData.getByte(1), midiData.getByte(2));
			break;
		default:
			break;
	}
	return 0;
}

int Synth::addMidiByte(uint8_t byte) {
	if (midiData.addByte(byte)) {
		processMidi();
	}
	return 0;
}

int Synth::enableLFO() {
	lfoEnable = true;
	setReg(REG_LFO, 0x08 | (lfoFreq));
	return 0;
}

int Synth::disableLFO() {
	lfoEnable = false;
	setReg(REG_LFO, lfoFreq);
	return 0;
}

int Synth::setLFOFreq(uint8_t freq) {
	lfoFreq = freq & 0x7;
	uint8_t val = (lfoEnable) ? (0x08 | lfoFreq) : lfoFreq;
	setReg(REG_LFO, val);
	return 0;
}

int Synth::setTimerA(uint16_t val) {
	val = val & 0x3FF;
	timerAFreq = val;
	setReg(REG_TIMER_A_MSB, val >> 2);
	setReg(REG_TIMER_A_LSB, val & 0x3);
	return 0;
}

int Synth::setTimerB(uint8_t val) {
	timerBFreq = val;
	setReg(REG_TIMER_B, val);
	return 0;
}

// Given a channel number, returns the code to select this channel in the key on/off register.
// channel should be an integer 0-5.
uint8_t Synth::channelToKeyOnCode(uint8_t channel) {
	switch (channel) {
		case (0):
			return KEY_ON_CH_1;
		case (1):
			return KEY_ON_CH_2;
		case (2):
			return KEY_ON_CH_3;
		case (3):
			return KEY_ON_CH_4;
		case (4):
			return KEY_ON_CH_5;
		case (5):
			return KEY_ON_CH_6;
		default:
			break;
	}
	return 0;
}

int Synth::setOperatorsOnOff(uint8_t operators, uint8_t channel) {
	uint8_t channelCode = channelToKeyOnCode(channel);
	setReg(REG_KEY_ON_OFF, (operators << 4) | channelCode);
	return 0;
}

int Synth::setKeyOn(uint8_t channel) {
	return setOperatorsOnOff(OP_ALL_SEL, channel);
}

int Synth::setKeyOff(uint8_t channel) {
	return setOperatorsOnOff(OP_NONE_SEL, channel);
}

int Synth::enableDAC() {
	setReg(REG_DAC_EN, 0x80);
	return 0;
}

int Synth::disableDAC() {
	setReg(REG_DAC_EN, 0x00);
	return 0;
}

int Synth::setDetune(uint8_t val, uint8_t op, uint8_t channel) {
	val = val & 0x7;
	vals_DT1[channel][op] = val;
	setReg(registers_DT1_MUL[op][channel], (val << 4) | vals_MUL[channel][op]);
	return 0;
}

int Synth::setDetuneAll(uint8_t val, uint8_t op) {
	for (int i = 0; i < NUM_CHANNELS; i++) {
		setDetune(val, op, i);
	}
	return 0;
}

int Synth::setMultiple(uint8_t val, uint8_t op, uint8_t channel) {
	val = val & 0xF;
	vals_MUL[channel][op] = val;
	setReg(registers_DT1_MUL[op][channel], (vals_DT1[channel][op] << 4) | val);
	return 0;
}

int Synth::setMultipleAll(uint8_t val, uint8_t op) {
	for (int i = 0; i < NUM_CHANNELS; i++) {
		setMultiple(val, op, i);
	}
	return 0;
}