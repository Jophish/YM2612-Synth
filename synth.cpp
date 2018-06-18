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
 	//Serial.begin(9600);`
 	/* YM2612 Test code */ 
  //set_reg(0x22, 0x00); // LFO off
  	disableLFO();
  //set_reg(0x27, 0x00); // Note off (channel 0)
  	setKeyOff(0);
  //set_reg(0x28, 0x01); // Note off (channel 1)
	setKeyOff(1);
 // set_reg(0x28, 0x02); // Note off (channel 2)
  	setKeyOff(2);
 // set_reg(0x28, 0x04); // Note off (channel 3)
  	setKeyOff(3);
 // set_reg(0x28, 0x05); // Note off (channel 4)
  	setKeyOff(4);
//  set_reg(0x28, 0x06); // Note off (channel 5)
  	setKeyOff(5);
//  set_reg(0x2B, 0x00); // DAC off
  	disableDAC();
  //set_reg(0x30, 0x71); //
  	 setDetuneAll(0x7, 0);
  	 setMultipleAll(0x1, 0);
  //set_reg(0x34, 0x0D); //
  	 setDetuneAll(0x0, 1);
  	 setMultipleAll(0xD, 1);
  //set_reg(0x38, 0x33); //
     setDetuneAll(0x3, 2);
  	 setMultipleAll(0x3, 2);
  //set_reg(0x3C, 0x01); // DT1/MUL
     setDetuneAll(0x0, 3);
  	 setMultipleAll(0x1, 3);
  //set_reg(0x40, 0x23); //
  	setTotalLevelAll(0x23, 0);
  //set_reg(0x44, 0x2D); //
  	setTotalLevelAll(0x2D, 1);
  //set_reg(0x48, 0x26); //
  	setTotalLevelAll(0x26, 2);
  //set_reg(0x4C, 0x00); // Total level
  	setTotalLevelAll(0x0, 3);
  //set_reg(0x50, 0x5F); //
  	setAttackRateAll(0x1F, 0);
  	setRateScalingAll(0x1, 0);
  //set_reg(0x54, 0x99); //
  	setAttackRateAll(0x19, 1);
    setRateScalingAll(0x2, 1);
  //set_reg(0x58, 0x5F); //
  	setAttackRateAll(0x1F, 2);
  	setRateScalingAll(0x1, 2);
  //set_reg(0x5C, 0x94); // RS/AR 
  	setAttackRateAll(0x14, 3);
  	setRateScalingAll(0x2, 3);
  //set_reg(0x60, 0x05); //
  	disableAmpModAll(0);
  	setDecayRate1All(0x5, 0);
  //set_reg(0x64, 0x05); //
  	disableAmpModAll(1);
  	setDecayRate1All(0x5, 1);
  //set_reg(0x68, 0x05); //
  	disableAmpModAll(2);
    setDecayRate1All(0x5, 2);
  //set_reg(0x6C, 0x07); // AM/D1R
  	disableAmpModAll(3);
    setDecayRate1All(0x7, 3);
  //set_reg(0x70, 0x02); //
  	setDecayRate2All(0x2, 0);
  //set_reg(0x74, 0x02); //
  	setDecayRate2All(0x2, 1);
  //set_reg(0x78, 0x02); //
  	setDecayRate2All(0x2, 2);
  //set_reg(0x7C, 0x02); // D2R
  	setDecayRate2All(0x2, 3);
  //set_reg(0x80, 0x11); //
  	setAmp2All(0x1, 0);
  	setReleaseRateAll(0x1, 0);
  //set_reg(0x84, 0x11); //
  	setAmp2All(0x1, 1);
  	setReleaseRateAll(0x1, 1);
  //set_reg(0x88, 0x11); //
  	setAmp2All(0x1, 2);
  	setReleaseRateAll(0x1, 2);
  //set_reg(0x8C, 0xA6); // D1L/RR
  	setAmp2All(0xA, 3);
  	setReleaseRateAll(0x6, 3);
  //set_reg(0x90, 0x00); //
  	setSSGEGAll(0, 0);
  //set_reg(0x94, 0x00); //
    setSSGEGAll(0, 1);
  //set_reg(0x98, 0x00); //
  	setSSGEGAll(0, 2);
 // set_reg(0x9C, 0x00); // Proprietary
  	setSSGEGAll(0, 3);
  //set_reg(0xB0, 0x32); // Feedback/algorithm
  	setFeedbackAll(0x6);
  	setAlgorithmAll(0x2);
  //set_reg(0xB4, 0xC0); // Both speakers on
  	enableLeftAll();
  	enableRightAll();
  	setFreqModSensAll(0);
  	setAmpModSensAll(0);
  //set_reg(0x28, 0x00); // Key off
  //set_reg(0xA4, 0x22); // 
  //set_reg(0xA0, 0x69); // Set frequency
 }

int Synth::turnMidiNoteOff(uint8_t note) {
	note -= 11;
	int channel = -1;
	for (int i = 0; i < NUM_CHANNELS; i++) {
		if (notesOn[i] == note) {
			channel = i;
			break;
		}
	}

	if (channel != -1) {
		//Serial.print("Stopping note ");
		//Serial.print(note);
		//Serial.print(" on channel ");
		//Serial.println(channel);
		notesOn[channel] = 0;
		setKeyOff(channel);
	}

	return 0;
}

int Synth::turnMidiNoteOn(uint8_t note, uint8_t vel) {

	// If the velocity is 0, turn the key off.	
	if (vel == 0) {
		return turnMidiNoteOff(note);
	}

	uint8_t min_vel = 0x60;
	uint8_t max_vel = 0x7F;
	vel = map(vel, 0, 0x7F, min_vel, max_vel);

	note -= 11;	
	uint8_t octave = midiData.midiToOctave(note);
	uint16_t frequency = noteToFreqVal(midiData.midiToNote(note));
	int channel = -1;
	int firstEmpty = -1;

	// If the note is already playing on some channel, replay it on that channel with the new velocity. 
	// Otherwise, the note isn't playing anywhere, so play it on the first empty channel. If there are
	// no empty channels, don't do anything.
	for (int i = 0; i < NUM_CHANNELS; i++) {
		if (notesOn[i] == note) {
			channel = i;
			break;
		}
		if (firstEmpty == -1 && notesOn[i] == 0) {
			firstEmpty = i;
		}
	}

	if (channel != -1) {
		setFrequency(octave, frequency, channel);
		//setTotalLevel(0, 3, channel);
		setKeyOn(channel);
		return 0;
	}

	if (firstEmpty != -1) {
		//Serial.print("Playing new note ");
		//Serial.print(note);
		//Serial.print(" on channel ");
		//Serial.println(firstEmpty);
		setFrequency(octave, frequency, firstEmpty);
		setTotalLevel(0x7F - vel, 3, firstEmpty);
		setKeyOn(firstEmpty);
		notesOn[firstEmpty] = note;
		return 0;
	}
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

int Synth::setTotalLevel(uint8_t val, uint8_t op, uint8_t channel) {
	val = val & 0x7F;
	vals_TL[channel][op] = val;
	setReg(registers_TL[op][channel], val);
	return 0;
}

int Synth::setTotalLevelAll(uint8_t val, uint8_t op) {
	for (int i = 0; i < NUM_CHANNELS; i++) {
		setTotalLevel(val, op, i);
	}
	return 0;
}

int Synth::setRateScaling(uint8_t val, uint8_t op, uint8_t channel) {
	val = val & 0x3;
	vals_RS[channel][op] = val;
	setReg(registers_RS_AR[op][channel], (val << 6) | vals_AR[channel][op]);
	return 0;
}

int Synth::setRateScalingAll(uint8_t val, uint8_t op) {
	for (int i = 0; i < NUM_CHANNELS; i++) {
		setRateScaling(val, op, i);
	}
	return 0;
}

int Synth::setAttackRate(uint8_t val, uint8_t op, uint8_t channel) {
	val = val & 0x1F;
	vals_AR[channel][op] = val;
	setReg(registers_RS_AR[op][channel], (vals_RS[channel][op] << 6) | val);
	return 0;
}

int Synth::setAttackRateAll(uint8_t val, uint8_t op) {
	for (int i = 0; i < NUM_CHANNELS; i++) {
		setAttackRate(val, op, i);
	}
	return 0;
}

int Synth::enableAmpMod(uint8_t op, uint8_t channel) {
	vals_AM[channel][op] = true;
	setReg(registers_AM_D1R[op][channel], 0x80 | vals_D1R[channel][op]);
	return 0;
}

int Synth::disableAmpMod(uint8_t op, uint8_t channel) {
	vals_AM[channel][op] = false;
	setReg(registers_AM_D1R[op][channel], vals_D1R[channel][op]);
	return 0;
}

int Synth::enableAmpModAll(uint8_t op) {
	for (int i = 0; i < NUM_CHANNELS; i++) {
		enableAmpMod(op, i);
	}
	return 0;
}

int Synth::disableAmpModAll(uint8_t op) {
	for (int i = 0; i < NUM_CHANNELS; i++) {
		disableAmpMod(op, i);
	}
	return 0;
}

int Synth::setDecayRate1(uint8_t val, uint8_t op, uint8_t channel) {
	val = val & 0x1F;
	vals_D1R[channel][op] = val;
	uint8_t am_val = (vals_AM[channel][op]) ? 0x80 : 0x00;
	setReg(registers_AM_D1R[op][channel], am_val | val);
	return 0;
}

int Synth::setDecayRate1All(uint8_t val, uint8_t op) {
	for (int i = 0; i < NUM_CHANNELS; i++) {
		setDecayRate1(val, op, i);
	}
	return 0;
}

int Synth::setDecayRate2(uint8_t val, uint8_t op, uint8_t channel) {
	val = val & 0x1F;
	vals_D2R[channel][op] = val;
	setReg(registers_D2R[op][channel], val);
	return 0;
}

int Synth::setDecayRate2All(uint8_t val, uint8_t op) {
	for (int i = 0; i < NUM_CHANNELS; i++) {
		setDecayRate2(val, op, i);
	}
	return 0;
}

int Synth::setAmp2(uint8_t val, uint8_t op, uint8_t channel) {
	val = val & 0xF;
	vals_D1L[channel][op] = val;
	setReg(registers_D1L_RR[op][channel], (val << 4) | vals_RR[channel][op]);
	return 0;
}

int Synth::setAmp2All(uint8_t val, uint8_t op) {
	for (int i = 0; i < NUM_CHANNELS; i++) {
		setAmp2(val, op, i);
	}
	return 0;
}

int Synth::setReleaseRate(uint8_t val, uint8_t op, uint8_t channel) {
	val = val & 0xF;
	vals_RR[channel][op] = val;
	setReg(registers_D1L_RR[op][channel], (vals_D1L[channel][op] << 4) | val);
	return 0;
}

int Synth::setReleaseRateAll(uint8_t val, uint8_t op) {
	for (int i = 0; i < NUM_CHANNELS; i++) {
		setReleaseRate(val, op, i);
	}
	return 0;
}

int Synth::setSSGEG(uint8_t val, uint8_t op, uint8_t channel) {
	val = val & 0xF;
	vals_SSG_EG[channel][op] = val;
	setReg(registers_SSG_EG[op][channel], val);
	return 0;
}

int Synth::setSSGEGAll(uint8_t val, uint8_t op) {
	for (int i = 0; i < NUM_CHANNELS; i++) {
		setSSGEG(val, op, i);
	}
	return 0;
}

int Synth::setFrequency(uint8_t block, uint16_t frequency, uint8_t channel) {
	//frequency = frequency & 0x7F;
	//block = block & 0x7;
	vals_FREQ[channel] = frequency;
	vals_BLOCK[channel] = block;
	setReg(registers_FREQ_HI[channel], (block << 3) | (uint8_t)(frequency >> 8));
	setReg(registers_FREQ_LO[channel], (uint8_t)frequency);
	return 0;
}

int Synth::setFeedback(uint8_t val, uint8_t channel) {
	val = val & 0x7;
	vals_FDBCK[channel] = val;
	setReg(registers_FDBCK_ALG[channel], (val << 3) | vals_ALG[channel]);
	return 0;
}

int Synth::setFeedbackAll(uint8_t val) {
	for (int i = 0; i < NUM_CHANNELS; i++) {
		setFeedback(val, i);
	}
	return 0;
}

int Synth::setAlgorithm(uint8_t val, uint8_t channel) {
	val = val & 0x7;
	vals_ALG[channel] = val;
	setReg(registers_FDBCK_ALG[channel], (vals_FDBCK[channel] << 3) | val);
	return 0;
}

int Synth::setAlgorithmAll(uint8_t val) {
	for (int i = 0; i < NUM_CHANNELS; i++) {
		setAlgorithm(val, i);
	}
	return 0;
}

int Synth::enableLeft(uint8_t channel) {
	vals_L_OUT[channel] = true;
	uint8_t r_val = (vals_R_OUT[channel]) ? 0x40 : 0x00;
	setReg(registers_STEREO_LFO[channel], 0x80 | r_val | (vals_AMS[channel] << 3) | vals_FMS[channel]);
	return 0;
}

int Synth::disableLeft(uint8_t channel) {
	vals_L_OUT[channel] = false;
	uint8_t r_val = (vals_R_OUT[channel]) ? 0x40 : 0x00;
	setReg(registers_STEREO_LFO[channel], r_val | (vals_AMS[channel] << 3) | vals_FMS[channel]);
	return 0;
}

int Synth::enableRight(uint8_t channel) {
	vals_R_OUT[channel] = true;
	uint8_t l_val = (vals_L_OUT[channel]) ? 0x80 : 0x00;
	setReg(registers_STEREO_LFO[channel], l_val | 0x40 | (vals_AMS[channel] << 3) | vals_FMS[channel]);
	return 0;
}

int Synth::disableRight(uint8_t channel) {
	vals_R_OUT[channel] = false;
	uint8_t l_val = (vals_L_OUT[channel]) ? 0x80 : 0x00;
	setReg(registers_STEREO_LFO[channel], l_val | (vals_AMS[channel] << 3) | vals_FMS[channel]);
	return 0;
}

int Synth::enableLeftAll() {
	for (int i = 0; i < NUM_CHANNELS; i++) {
		enableLeft(i);
	}
	return 0;
}

int Synth::disableLeftAll() {
	for (int i = 0; i < NUM_CHANNELS; i++) {
		disableLeft(i);
	}
	return 0;
}

int Synth::enableRightAll() {
	for (int i = 0; i < NUM_CHANNELS; i++) {
		enableRight(i);
	}
	return 0;
}

int Synth::disableRightAll() {
	for (int i = 0; i < NUM_CHANNELS; i++) {
		disableRight(i);
	}
	return 0;
}

int Synth::setAmpModSens(uint8_t val, uint8_t channel) {
	val = val & 0x7;
	vals_AMS[channel] = val;
	uint8_t l_val = (vals_L_OUT[channel]) ? 0x80 : 0x00;
	uint8_t r_val = (vals_R_OUT[channel]) ? 0x40 : 0x00;
	setReg(registers_STEREO_LFO[channel], l_val | r_val | (val << 3) | vals_FMS[channel]);
	return 0;
}

int Synth::setFreqModSens(uint8_t val, uint8_t channel) {
	val = val & 0x3;
	vals_FMS[channel] = val;
	uint8_t l_val = (vals_L_OUT[channel]) ? 0x80 : 0x00;
	uint8_t r_val = (vals_R_OUT[channel]) ? 0x40 : 0x00;
	setReg(registers_STEREO_LFO[channel], l_val | r_val | (vals_AMS[channel] << 3) | val);
	return 0;
}

int Synth::setAmpModSensAll(uint8_t val) {
	for (int i = 0; i < NUM_CHANNELS; i++) {
		setAmpModSens(val, i);
	}
	return 0;
}

int Synth::setFreqModSensAll(uint8_t val) {
	for (int i = 0; i < NUM_CHANNELS; i++) {
		setFreqModSens(val, i);
	}
	return 0;
}