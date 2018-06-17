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
		midiMessages[nextIndex] = byte;
		msgReady = false;
	} else {
		midiMessages[nextIndex] = byte;
	}
	nextIndex = (nextIndex + 1) % NUM_MIDI_MESSAGES;
	if (nextIndex == 0)
		msgReady = true;
	return msgReady;
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

