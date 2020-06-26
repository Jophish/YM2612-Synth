#include "midi.h"

const Note midiMessage::noteArray[NOTES_PER_OCTAVE] = {NOTE_C, NOTE_C_SHARP, NOTE_D, NOTE_D_SHARP, NOTE_E, NOTE_F, NOTE_F_SHARP, NOTE_G, NOTE_G_SHARP, NOTE_A, NOTE_A_SHARP, NOTE_B};

midiMessage::midiMessage() {
	for (int i = 0; i < NUM_MIDI_MESSAGES; i++) {
		midiMessages[i] = 0;
	}
	nextIndex = 0;
	msgReady = false;
}

bool midiMessage::addByte(uint8_t byte) {
	if (msgReady) {
		numBytes = midiCommandToNumBytes(byte);
		msgReady = false;
		nextIndex = 0;
		midiMessages[nextIndex] = byte;
	} else {
		midiMessages[nextIndex] = byte;
	}
	nextIndex++;
	if (nextIndex == numBytes) {
		msgReady = true;
	}
	return msgReady;
}

int midiMessage::midiCommandToNumBytes(uint8_t cmd) {
	switch (cmd & 0xF0) {
		case (MIDI_NOTE_OFF):
			return 3;
		case (MIDI_NOTE_ON):
			return 3;
		case (MIDI_POLY_AFTERTOUCH):
			return 3;
		case (MIDI_CTRL_CHANGE):
			return 3;
		case (MIDI_PROG_CHANGE):
			return 2;
		case (MIDI_CHAN_AFTERTOUCH):
			return 2;
		case (MIDI_PITCH_BEND):
			return 3;
	}

	if ((cmd & 0xF0) != 0xF0)
		return 1;

	switch (cmd) {
		case (MIDI_SYS_EX):
			return 1;
		case (MIDI_TIME_CODE_QTR_FRAME):
			return 1;
		case (MIDI_SONG_POS_PTR):
			return 3;
		case (MIDI_SONG_SELECT):
			return 2;
		case (MIDI_TUNE_REQUEST):
			return 1;
		case (MIDI_EOX):
			return 1;
		case (MIDI_TIMING):
			return 1;
		case (MIDI_START):
			return 1;
		case (MIDI_CONTINUE):
			return 1;
		case (MIDI_STOP):
			return 1;
		case (MIDI_ACTIVE_SENS):
			return 1;
		case (MIDI_RESET):
			return 1;
	}

	return 1;
}

int midiMessage::getByte(int num) {
	if (num >= NUM_MIDI_MESSAGES)
		return -1;
	return midiMessages[num];
}

bool midiMessage::msgIsReady() {
	return msgReady;
}

uint8_t midiMessage::midiToOctave(uint8_t midiNote) {
	return (midiNote / NOTES_PER_OCTAVE);
}

Note midiMessage::midiToNote(uint8_t midiNote) {
	return noteArray[midiNote % NOTES_PER_OCTAVE];
}

